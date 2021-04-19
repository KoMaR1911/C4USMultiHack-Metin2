#include "stdafx.h"
#include "Network.h"

time_t	Network::m_connectLimitTime;

char* Network::m_recvBuf;
int	Network::m_recvBufSize;
int	Network::m_recvBufInputPos;
int	Network::m_recvBufOutputPos;

char* Network::m_sendBuf;
int	Network::m_sendBufSize;
int	Network::m_sendBufInputPos;
int	Network::m_sendBufOutputPos;

bool	Network::m_isOnline;
SOCKET	Network::m_sock ;

SOCKADDR_IN Network::m_sockAddrIn;

bool Network::GetHostName(char* szName, int size)
{
	if (gethostname(szName, size) == SOCKET_ERROR)
		return false;
	return true;
}

bool Network::IsIP(const char* c_szAddr)
{
	if (c_szAddr[0] < '0' || c_szAddr[0]>'9')
		return false;
	return true;
}

bool Network::SetConnection(const char* c_szAddr, int port)
{
	memset(&m_sockAddrIn, 0, sizeof(m_sockAddrIn));
	m_sockAddrIn.sin_family = AF_INET;
	if (IsIP(c_szAddr))
	{
		SetIP(c_szAddr);
	}
	else
	{
		if (!SetDNS(c_szAddr))
			return false;
	}

	SetPort(port);
	return true;
}

void Network::SetLocalIP()
{
	SetIP(INADDR_ANY);
}

void Network::SetIP(DWORD ip)
{
	m_sockAddrIn.sin_addr.s_addr = htonl(ip);
}

void Network::SetIP(const char* c_szIP)
{
	m_sockAddrIn.sin_addr.s_addr = inet_addr(c_szIP);
}

bool Network::SetDNS(const char* c_szDNS)
{
	HOSTENT* pHostent = gethostbyname(c_szDNS);
	if (!pHostent) return false;
	memcpy(&m_sockAddrIn.sin_addr, pHostent->h_addr, sizeof(m_sockAddrIn.sin_addr));
	return true;
}

void Network::SetPort(int port)
{
	m_sockAddrIn.sin_port = htons(port);
}

int Network::GetSize()
{
	return sizeof(m_sockAddrIn);
}

DWORD Network::GetIP()
{
	return ntohl(m_sockAddrIn.sin_addr.s_addr);
}

void Network::GetIP(char* szIP, int len)
{
	BYTE IPs[4];
	*((DWORD*)IPs) = m_sockAddrIn.sin_addr.s_addr;

	_snprintf(szIP, len, "%d.%d.%d.%d", IPs[0], IPs[1], IPs[2], IPs[3]);
}

int Network::GetPort()
{
	return ntohs(m_sockAddrIn.sin_port);
}
void Network::SetRecvBufferSize(int recvBufSize)
{
	if (m_recvBuf)
	{
		if (m_recvBufSize>recvBufSize)
			return;

		delete [] m_recvBuf;

		
	}
	m_recvBufSize = recvBufSize;
	m_recvBuf = new char[m_recvBufSize];
	
}

void Network::SetSendBufferSize(int sendBufSize)
{
	if (m_sendBuf)
	{
		if (m_sendBufSize > sendBufSize)
			return;

		delete [] m_sendBuf;

		
	}

	m_sendBufSize = sendBufSize;
	m_sendBuf = new char[m_sendBufSize];
	
}

bool Network::RecvInternalBuffer()
{
	if (m_recvBufOutputPos>0)
	{
		int recvBufDataSize = m_recvBufInputPos - m_recvBufOutputPos;
		if (recvBufDataSize>0)
		{
			memmove(m_recvBuf, m_recvBuf + m_recvBufOutputPos, recvBufDataSize);
		}

		m_recvBufInputPos -= m_recvBufOutputPos;
		m_recvBufOutputPos = 0;
	}
	int restSize = m_recvBufSize - m_recvBufInputPos;
	if (restSize>0)
	{
		int recvSize = recv(m_sock, m_recvBuf + m_recvBufInputPos, m_recvBufSize - m_recvBufInputPos, 0);
		

		if (recvSize < 0)
		{
			int error = WSAGetLastError();

			if (error != WSAEWOULDBLOCK)
			{
				return false;
			}
		}
		else if (recvSize == 0)
		{
			return false;
		}

		m_recvBufInputPos += recvSize;
	}
	return true;
}


bool Network::SendInternalBuffer()
{
	int dataSize=GetSendBufferSize();
	if (dataSize<=0)
		return true;

	int sendSize = send(m_sock, m_sendBuf+m_sendBufOutputPos, dataSize, 0);
	if (sendSize < 0)
		return false;

	m_sendBufOutputPos+=sendSize;

	PopSendBuffer();

	return true;
}

void Network::PopSendBuffer()
{
	if (m_sendBufOutputPos<=0)
		return;

	int sendBufDataSize = m_sendBufInputPos - m_sendBufOutputPos;

	if (sendBufDataSize>0)
	{
		memmove(m_sendBuf, m_sendBuf+m_sendBufOutputPos, sendBufDataSize);
	}

	m_sendBufInputPos = sendBufDataSize;
	m_sendBufOutputPos = 0;
}

#pragma warning(push)
#pragma warning(disable:4127)
void Network::Process()
{
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}
		

	fd_set fdsRecv;
	fd_set fdsSend;

	FD_ZERO(&fdsRecv);
	FD_ZERO(&fdsSend);

	FD_SET(m_sock, &fdsRecv);
	FD_SET(m_sock, &fdsSend);

	TIMEVAL delay;

	delay.tv_sec = 0;
	delay.tv_usec = 0;

	if (select(0, &fdsRecv, &fdsSend, NULL, &delay) == SOCKET_ERROR)
	{
		return;
	}
		

	if (!m_isOnline)
	{
		if (FD_ISSET(m_sock, &fdsSend))
		{
			m_isOnline = true;
			OnConnectSuccess();
		}
		else if (time(NULL) > m_connectLimitTime)
		{
			Clear();
			OnConnectFailure();
		}

		return;
	}

	if (FD_ISSET(m_sock, &fdsSend) && (m_sendBufInputPos > m_sendBufOutputPos))
	{
		if (!SendInternalBuffer())
		{
			int error = WSAGetLastError();

			if (error != WSAEWOULDBLOCK)
			{
				
				OnRemoteDisconnect();
				Clear();
				return;
			}
		}
	}

	if (FD_ISSET(m_sock, &fdsRecv))
	{
		if (!RecvInternalBuffer())
		{
			
			OnRemoteDisconnect();
			Clear();
			return;
		}
	}

	if (!OnProcess())
	{
		OnRemoteDisconnect();
		Clear();
	}
}
#pragma warning(pop)

void Network::Disconnect()
{
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}
		

	OnDisconnect();

	Clear();
}
bool Network::Initialize()
{

	m_sock = NULL;
	m_isOnline = false;
	m_connectLimitTime = 0;



	m_recvBuf = NULL;
	m_recvBufSize = 0;
	m_recvBufOutputPos = 0;
	m_recvBufInputPos = 0;


	m_sendBuf = NULL;
	m_sendBufSize = 0;
	m_sendBufOutputPos = 0;
	m_sendBufInputPos = 0;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}
		
	return true;
}
void Network::Clear()
{

	if (m_sock)
	{
		closesocket(m_sock);
	}
		
	m_sock = NULL;
	m_isOnline = false;
	m_connectLimitTime = 0;

	

	m_recvBufInputPos = 0;
	m_recvBufOutputPos = 0;

	m_sendBufInputPos = 0;
	m_sendBufOutputPos = 0;

}

bool Network::Connect(const char* c_szAddr, int port, int limitSec)
{
	if (m_sock)
	{
		OnRemoteDisconnect();
	}
	Clear();
	SetConnection(c_szAddr, port);
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{
		Clear();
		OnConnectFailure();
		return false;
	}

	DWORD arg = 1;
	ioctlsocket(m_sock, FIONBIO, &arg);

	if (connect(m_sock, (struct sockaddr*) & m_sockAddrIn, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		int error = WSAGetLastError();

		if (error != WSAEWOULDBLOCK)
		{
			
			Clear();
			OnConnectFailure();
			return false;
		}
	}

	m_connectLimitTime = time(NULL) + limitSec;
	return true;
}




void Network::ClearRecvBuffer()
{
	m_recvBufOutputPos = m_recvBufInputPos = 0;
}

int Network::GetRecvBufferSize()
{
	return m_recvBufInputPos - m_recvBufOutputPos;
}

bool Network::Peek(int size)
{
	if (GetRecvBufferSize() < size)
		return false;

	return true;
}

bool Network::Peek(int size, char * pDestBuf)
{
	if (GetRecvBufferSize() < size)
		return false;

	memcpy(pDestBuf, m_recvBuf + m_recvBufOutputPos, size);
	return true;
}




bool Network::Recv(int size)
{
	if (!Peek(size))
		return false;

	m_recvBufOutputPos += size;
	return true;
}


bool Network::Recv(int size, char * pDestBuf)
{
	if (!Peek(size, pDestBuf))
		return false;

	m_recvBufOutputPos += size;
	return true;
}

int Network::GetSendBufferSize()
{
	return m_sendBufInputPos-m_sendBufOutputPos;
}


bool Network::Send(int size, const char* pSrcBuf)
{
	int sendBufRestSize = m_sendBufSize - m_sendBufInputPos;
	if ((size + 1) > sendBufRestSize)
	{
		return false;
	}
		

	memcpy(m_sendBuf + m_sendBufInputPos, pSrcBuf, size);
	m_sendBufInputPos += size;

	return true;
}

bool Network::Peek(int len, void* pDestBuf)
{
	return Peek(len, (char*)pDestBuf);
}

bool Network::Recv(int len, void* pDestBuf)
{
	return Recv(len, (char*)pDestBuf);
}

bool Network::SendFlush(int len, const void* pSrcBuf)
{
	if (!Send(len, pSrcBuf))
		return false;
	return SendInternalBuffer();
}

bool Network::Send(int len, const void* pSrcBuf)
{
	return Send(len, (const char*)pSrcBuf);
}

bool Network::IsOnline()
{
	return m_isOnline;
}

bool Network::OnProcess()
{
	return true;
}

void Network::OnRemoteDisconnect()
{
	
#ifdef _DEBUG
	cout << "OnRemoteDisconnect" << endl;
#endif
}

void Network::OnDisconnect()
{
#ifdef _DEBUG
	cout << "OnDisconnect" << endl;
#endif
}

void Network::OnConnectSuccess()
{
#ifdef _DEBUG
	cout << "OnConnectSuccess" << endl;
#endif
}

void Network::OnConnectFailure()
{
#ifdef _DEBUG
	cout << "OnConnectFailure" << endl;
#endif
}





void Network::Destroy()
{
	Clear();

	WSACleanup();

	
}

