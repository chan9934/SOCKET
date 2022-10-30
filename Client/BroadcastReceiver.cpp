#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<WS2tcpip.h>

#define BUF_SIZE 30

using namespace std;

void ErrorHandling(const char* message)
{
	printf("%s\n", message);
	exit(1);
}

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hRecvSock;
	SOCKADDR_IN adr;
	char buf[BUF_SIZE];
	int strLen;

	if (argc != 2)
	{
		printf("USage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		ErrorHandling("WSAStartup Error");
	}

	hRecvSock = socket(PF_INET, SOCK_DGRAM, 0);

	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = htonl(INADDR_ANY);
	adr.sin_port = htons(atoi(argv[1]));

	if (bind(hRecvSock, (SOCKADDR*)&adr, sizeof(adr)) == SOCKET_ERROR)
	{
		ErrorHandling("bindError");
	}



	while (1)
	{
		strLen = recvfrom(hRecvSock, buf, sizeof(buf) - 1, 0, NULL, 0);
		if (strLen < 0)
		{
			break;
		}
		buf[strLen] = 0;
		printf(buf);
	}
	closesocket(hRecvSock);
	WSACleanup();
	return 0;


}