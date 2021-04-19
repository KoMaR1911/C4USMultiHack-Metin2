
#ifndef _ABHI_SPLASH_H_
#define _ABHI_SPLASH_H_

#include "windows.h"


class CSplash
{
public:

    CSplash(int resourceId,HINSTANCE hins);
    

	void Start( COLORREF colTrans, bool hShowText, char hText[255], COLORREF hTextColor);
	void Start( COLORREF colTrans);
	void Start(LPCTSTR lpszFileName, COLORREF colTrans);
  
    virtual ~CSplash();

    void ShowSplash();

    
    int DoLoop();

   
    int CloseSplash();

   
    DWORD SetBitmap(LPCTSTR lpszFileName);
    DWORD SetBitmap(HICON hBitmap);

    
    bool SetTransparentColor(COLORREF col);

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;
	HANDLE m_SplashEvent;
private:
    void Init();
    void  OnPaint(HWND hwnd);
    bool MakeTransparent();
    HWND RegAndCreateWindow();
    COLORREF m_colTrans;
    DWORD m_dwWidth;
    DWORD m_dwHeight;
    void FreeResources();
    HICON m_hBitmap;
    LPCTSTR m_lpszClassName;
	bool m_ShowText;
	char m_TextToDisplay[255];
	COLORREF m_TextColor;
    HINSTANCE m_hins;
    int m_resourceId;
};



DWORD WINAPI SplashThread(CSplash* lpSplash) // OK
{
    lpSplash->ShowSplash();

    SetEvent(lpSplash->m_SplashEvent);

    MSG msg;

    while (GetMessage(&msg, 0, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}


void SplashScreen(int ResId,HINSTANCE hins, bool TextSwitch, char DisplayText[255], int CloseTime)
{
    CSplash splash(ResId,  hins);
    COLORREF TextColor;
    TextColor = RGB(185, 43, 43);

    if (TextSwitch)
    {
        (&splash)->Start( RGB(128, 128, 128), 1, DisplayText, TextColor);
    }
    else
    {
        (&splash)->Start( RGB(128, 128, 128));
    }
    (&splash)->m_SplashEvent = CreateEvent(0, 0, 0, 0);

    //HANDLE hThreads = nullptr;
    //NTSTATUS ret = SYSCALL(0xBB, 11, &hThreads, THREAD_ALL_ACCESS, 0, (HANDLE)-1, (LPTHREAD_START_ROUTINE)SplashThread, 0, 0, 0, 0, 0, 0);
    //if (ret != 0 || hThreads == nullptr)
    //{
    //    MessageBox(0, "error!3", 0, 0);
    //}
    //CloseHandle(hThreads);

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SplashThread, (&splash), 0, 0);

    WaitForSingleObject((&splash)->m_SplashEvent, INFINITE);

    CloseHandle((&splash)->m_SplashEvent);

    if (CloseTime > 0)
    {
        Sleep(CloseTime);
        (&splash)->CloseSplash();
    }
}
#endif //_ABHI_SPLASH_H_
