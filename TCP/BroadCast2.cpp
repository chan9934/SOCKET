#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 30

void ErrorHandling(const char* message)
{
	printf("%s\n", message);
	exit(1);
}

using namespace std;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSendSock;
	SOCKADDR_IN broad_adr;
	FILE* fp;
	char buf[BUF_SIZE];
	int so_brd = 1;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		ErrorHandling("WSAStartupError");
	}

	hSendSock = socket(PF_INET, SOCK_DGRAM, 0);

	memset(&broad_adr, 0, sizeof(broad_adr));
	broad_adr.sin_family = AF_INET;
	broad_adr.sin_addr.s_addr = inet_addr(argv[1]);
	broad_adr.sin_port = htons(atoi(argv[2]));

	setsockopt(hSendSock, SOL_SOCKET, SO_BROADCAST, (char*)&so_brd, sizeof(so_brd));

	if ((fp = fopen("news.txt", "r")) == NULL)
	{
		ErrorHandling("fopenError");
	}

	while (!feof(fp))
	{
		fgets(buf, BUF_SIZE, fp);
		sendto(hSendSock, buf, strlen(buf), 0, (SOCKADDR*)&broad_adr, sizeof(broad_adr));
		Sleep(1000);
	}
	closesocket(hSendSock);
	WSACleanup();
	return 0;
}