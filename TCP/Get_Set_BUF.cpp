#include <iostream>
#include<WinSock2.h>

using namespace std;
void ShowSocketBufSize(SOCKET sock);
void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSock;
	int sndBuf, rcvBuf, state;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup Error() !");
	}
	hSock = socket(PF_INET, SOCK_STREAM, 0);
	ShowSocketBufSize(hSock);

	sndBuf = 1024 * 3;
	rcvBuf = 1024 * 3;
	state = setsockopt(hSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, sizeof(sndBuf));
	if (state == SOCKET_ERROR)
	{
		ErrorHandling("setsockopt() SO_SNDBUF error");
	}
	state = setsockopt(hSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, sizeof(rcvBuf));
	if (state == SOCKET_ERROR)
	{
		ErrorHandling("setsockopt() SO_RCVBUF error");
	}

	ShowSocketBufSize(hSock);
	closesocket(hSock);
	WSACleanup();
	return 0;
}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void ShowSocketBufSize(SOCKET sock)
{
	int sndBuf, rcvBuf, state, len;

	len = sizeof(sndBuf);

	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
	if (state == SOCKET_ERROR)
	{
		ErrorHandling("getsockopt() SO_SNDBUF error");
	}

	len = sizeof(rcvBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
	if (state == SOCKET_ERROR)
	{
		ErrorHandling("getsockopt() SO_RCVBUF error");
	}

	printf("Input buffer size: %d \n", rcvBuf);
	printf("Input buffer size: %d \n", sndBuf);

}