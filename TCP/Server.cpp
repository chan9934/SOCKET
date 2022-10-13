#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <string>

using std::string;
void ErrorHandling(string message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[] = "Hello World";
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	if (listen(hServSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);

	if (hClntSock == INVALID_SOCKET)
	{
		ErrorHandling("accept() error");
	}

	while (sizeof(message)-1 == send(hClntSock, message, 1, 0))
	{
		
		
	}
	int a = sizeof(message);
	for (int i = 1; i < a; ++i)
	{
		send(hClntSock, message+i, 1, 0);
		
	}

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;


}

void ErrorHandling(string message)
{
	char* message2 = const_cast<char*>(message.c_str());
	fputs(message2, stderr);
	fputc('\n', stderr);
	exit(1);
}