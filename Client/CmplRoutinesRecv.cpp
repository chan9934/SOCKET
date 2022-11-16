#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<WinSock2.h>

using namespace std;

#define BUF_SIZE 1024

void CALLBACK CompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void ErrorHandling(const char* msg);

WSABUF dataBuf;
char buf[BUF_SIZE];
DWORD recvBytes = 0;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;

	WSAOVERLAPPED overlapped;
	WSAEVENT evObj;

	int idx = 0;
	int recvAdrSz = 0;
	DWORD flags = 0;
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&lisnAdr, 0, sizeof(lisnAdr));
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() Error");
	if (listen(hLisnSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() Error");

	recvAdrSz = sizeof(recvAdr);

	hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
	memset(&overlapped, 0, sizeof(overlapped));

	dataBuf.len = BUF_SIZE;
	dataBuf.buf = buf;

	evObj = WSACreateEvent();

	if (WSARecv(hRecvSock, &dataBuf, 1, &recvBytes, &flags, &overlapped, CompRoutine) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSA_IO_PENDING)
		{
			puts("Background data receive");
		}
	}

	idx - WSAWaitForMultipleEvents(1, &evObj, FALSE, WSA_INFINITE, TRUE);
	if (idx == WAIT_IO_COMPLETION)
	{
		puts("Overlapped I/O Completed");
	}
	else
	{
		ErrorHandling("WSARecv() error");
	}


	WSACloseEvent(evObj);
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	return 0;

}
void ErrorHandling(const char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
void CALLBACK CompRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped , DWORD flags)
{
	if (dwError != 0)
	{
		ErrorHandling("CompRoutine error");
	}
	else
	{
		recvBytes = szRecvBytes;
		printf("Received message: %s \n", buf);
	}
}