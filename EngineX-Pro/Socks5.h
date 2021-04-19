#pragma once
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include "lazy_importer.hpp"

typedef int (WINAPI* PCONNECT)(int socket, const struct sockaddr* address, int address_len); //You now have declared the function pointer type.
PCONNECT OrigConnect; //And you now have a declared global pointer.
int WINAPI __stdcall MyConnect(int socket, const struct sockaddr* address, int address_len)
{

    /*return OrigConnect(socket, address, address_len);*/

    //MessageBox(NULL,"","",NULL);
    char buf[255] = { 0 };
    struct sockaddr_in* to;
    to = (struct sockaddr_in*)address;

    fd_set sockset;
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    // socks proxy address & port
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("72.11.148.222");
    sa.sin_port = htons(56533);
    // connect to the socks proxy
    //int iRet = OrigConnect( socket, (sockaddr*)address, address_len );
    int iRet = OrigConnect(socket, (struct sockaddr*) & sa, sizeof(struct sockaddr));
    if (iRet == SOCKET_ERROR)
    {
        if (WSAGetLastError() != 10035)
        {
            //sprintf(buf, "%d", iRet);
            sprintf(buf, "%d", WSAGetLastError());
            //MessageBox(NULL,buf,buf,NULL);
            return SOCKET_ERROR;
        }
    }

    // send a version identifier/method selection message
    buf[0] = 0x5; // SOCKS Protocol Version 5.0
    buf[1] = 0x2; // number of methods is 2
    buf[2] = 0x0; // X'00' NO AUTHENTICATION REQUIRED
    buf[3] = 0x2; // X'02' USERNAME/PASSWORD

    FD_ZERO(&sockset);
    FD_SET(socket, &sockset);
    select(socket + 1, NULL, &sockset, NULL, &timeout);
    iRet = send(socket, buf, 4, 0);
    if (iRet == SOCKET_ERROR)
    {
        //MessageBox( NULL, "send", "sockscap", MB_OK );
        return SOCKET_ERROR;
    }

    FD_ZERO(&sockset);
    FD_SET(socket, &sockset);
    select(socket + 1, &sockset, NULL, NULL, &timeout);
    iRet = recv(socket, buf, 254, 0);
    if (iRet == SOCKET_ERROR)
    {
        //MessageBox( NULL, "Recv", "sockscap", MB_OK );
        return SOCKET_ERROR;
    }

    // define the username & password for socks authentication
    char username[64];// = "guest";
    DWORD tuserlen = sizeof(username);
    GetUserName(username, &tuserlen);
    int userlen = strlen(username);
    char password[64] = "guest";
    int passlen = strlen(password);

    /*char buf2[255];
    int i;
    for (i=0; i<strlen(buf); i++) sprintf(buf2, "%X", buf[i]);
    MessageBox(NULL, buf2, buf2,NULL);*/

    switch (buf[1])
    {
    case 0x2: // need username/password
        buf[0] = 0x1;
        buf[1] = userlen;
        memcpy(buf + 2, username, userlen);
        buf[userlen + 2] = passlen;
        memcpy(buf + userlen + 3, password, passlen);

        FD_ZERO(&sockset);
        FD_SET(socket, &sockset);
        select(socket + 1, NULL, &sockset, NULL, &timeout);
        iRet = send(socket, buf, 3 + userlen + passlen, 0);

        FD_ZERO(&sockset);
        FD_SET(socket, &sockset);
        select(socket + 1, &sockset, NULL, NULL, &timeout);
        iRet = recv(socket, buf, 254, 0);

        if (buf[1] == 0x0) // Authentication return vaule, 0x0 for success
            iRet = 0;
        else
        {
            iRet = SOCKET_ERROR; // Other for failure
            break;
        }
        //break;
    case 0x0: // No authentication require
        buf[0] = 0x5; // SOCKS Protocol Version 5.0
        buf[1] = 0x1; // CMD = connect
        buf[2] = 0x0; // Reserved 
        buf[3] = 0x1; // IP v4
        memcpy(buf + 4, &to->sin_addr.s_addr, sizeof(DWORD));
        memcpy(buf + 8, &to->sin_port, sizeof(WORD));

        FD_ZERO(&sockset);
        FD_SET(socket, &sockset);
        select(socket + 1, NULL, &sockset, NULL, &timeout);
        iRet = send(socket, buf, 10, 0);

        FD_ZERO(&sockset);
        FD_SET(socket, &sockset);
        select(socket + 1, &sockset, NULL, NULL, &timeout);
        iRet = recv(socket, buf, 254, 0);
        //MessageBox( NULL, "send", "sockscap", MB_OK );

        if (buf[1] == 0x0) // 0x0 for success
            iRet = 0;
        else
            iRet = SOCKET_ERROR;
        break;
    case 0xFF: // Can't accept your methods
        iRet = SOCKET_ERROR;
        break;
    default: // Unknown error
        iRet = SOCKET_ERROR;
        break;
    }
    FD_ZERO(&sockset);
    FD_SET(socket, &sockset);
    select(socket + 1, NULL, &sockset, NULL, &timeout);
    FD_ZERO(&sockset);
    //if (iRet == SOCKET_ERROR) MessageBox(NULL, "", "", NULL);
    return iRet;
}


void DLLAction()
{
    //while (GetModuleHandle("Ws2_32.dll") == 0)  {MessageBox(NULL, "Done", "Done", NULL);Sleep(5000);} 
    //while (GetProcAddress(GetModuleHandle("Ws2_32.dll"), "connect") == 0) {MessageBox(NULL, "Done", "Done", NULL);Sleep(5000);}
    /*Sleep(5000);*/
    WSADATA wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);

    OrigConnect = (PCONNECT)DetourFunction((PBYTE)(DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "connect"), (PBYTE)MyConnect);

    int WSAAPI connect(
        SOCKET         s,
        const sockaddr * name,
        int            namelen
    );



    
    MessageBox(NULL, "Done", "Done", NULL);
    return;
}

//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID lpvReserved)
//{
//    switch (reason)
//    {
//    case DLL_PROCESS_ATTACH:
//    {
//        CreateThread(NULL, 0, DLLAction, NULL, 0, NULL);
//
//        /*
//
//        *(PDWORD)&OrigConnect = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "connect"), (DWORD)MyConnect, (DWORD)OrigConnect);
//        WSADATA wsaData;
//        WSAStartup(MAKEWORD(1,1), &wsaData);
//
//        */
//        break;
//    }
//
//    case DLL_PROCESS_DETACH:
//        break;
//
//    case DLL_THREAD_ATTACH:
//        break;
//
//    case DLL_THREAD_DETACH:
//        break;
//    }
//
//    /* Returns TRUE on success, FALSE on failure */
//    return TRUE;
//}