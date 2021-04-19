#pragma once


class Network 
{
public:


	static bool GetHostName(char* szName, int size);


	static bool SetConnection(const char* c_szAddr, int port);

	static void SetLocalIP();
	static void SetIP(DWORD ip);
	static void SetIP(const char* c_szIP);
	static bool SetDNS(const char* c_szDNS);

	static void SetPort(int port);

	static int GetPort();
	static int GetSize();

	static void GetIP(char* szIP, int len);

	static DWORD GetIP();
	static bool IsIP(const char* c_szAddr);

	static void SetRecvBufferSize(int recvBufSize);
	static void SetSendBufferSize(int sendBufSize);


	static int	GetRecvBufferSize();
	static bool Initialize();
	static void Clear();
	static void ClearRecvBuffer();

	static void Process();


	static bool Connect(const char* c_szAddr, int port, int limitSec = 3);

	static void Disconnect();
	static void Destroy();
	static bool Peek(int len);
	static bool Peek(int len, char* pDestBuf);
	static bool Peek(int len, void* pDestBuf);
	static bool Recv(int len);
	static bool Recv(int len, char* pDestBuf);
	static bool Recv(int len, void* pDestBuf);
	static bool Send(int len, const char* pSrcBuf);
	static bool Send(int len, const void* pSrcBuf);
	static bool SendFlush(int len, const void* pSrcBuf);

	static bool IsOnline();


protected:
	static void OnConnectSuccess();
	static void OnConnectFailure();
	static void OnRemoteDisconnect();
	static void OnDisconnect();
	static bool OnProcess();

	static bool SendInternalBuffer();
	static bool RecvInternalBuffer();

	static void PopSendBuffer();

	static int GetSendBufferSize();



private:
	static time_t	m_connectLimitTime;



	static char* m_recvBuf;
	static int	m_recvBufSize;
	static int	m_recvBufInputPos;
	static int	m_recvBufOutputPos;

	static char* m_sendBuf;
	static int	m_sendBufSize;
	static int	m_sendBufInputPos;
	static int	m_sendBufOutputPos;

	static bool	m_isOnline;
	static SOCKET	m_sock;

	static SOCKADDR_IN m_sockAddrIn;
};
