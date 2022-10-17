#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<string>
#include<WinSock2.h>

using namespace std;

#define BUF_SIZE 1024

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr;

	if (argc != 3)
	{
		printf("usage : % s < IP<PORT>\n", argv[0]);
			exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	ErrorHandling("Socket() Error!");

	memset(&servAdr, 0, sizeof(servAdr));

	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr))== SOCKET_ERROR)
		ErrorHandling("connect() error!");

	else
		puts("connected ...........");

	while (1)
	{
		fputs("Input message(Q to quit) : ", stdout);// stdout 표준 출력
		fgets(message, BUF_SIZE, stdin);//stdin 표준 입력

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) // 두 스트링 비교
		{
			break;
		}
		int recv_Len = 0;
		strLen = send(hSocket, message, strlen(message), 0); //strlen 문자열 길이
		while (strLen > recv_Len)
		{
			int recv_Cnt = recv(hSocket, message, BUF_SIZE - 1, 0);
			if (recv_Cnt == SOCKET_ERROR)
			{
				ErrorHandling("read() error");
			}
			recv_Len += recv_Cnt;


		}

		message[strLen] = 0;
		printf("Message from server: %s", message);
	}
	closesocket(hSocket);
	WSACleanup();
	return 0;


}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}