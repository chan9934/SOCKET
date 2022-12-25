

#include<iostream>
#include<WinSock2.h>

using namespace std;
#define BUF_SIZE 30

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	FILE* fp;
	char buf[BUF_SIZE];
	int readcnt;
	int clntAdrSz;

	SOCKADDR_IN servAdr, clntAdr;

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	bind(hServSock, (SOCKADDR*)(&servAdr), sizeof(servAdr));
	listen(hServSock, 5);

	clntAdrSz = sizeof(clntAdr);
	hClntSock = accept(hClntSock, (SOCKADDR*)(&clntAdr), &clntAdrSz);

	fp = fopen("file_server.c", "rb"); //filewerverwin내용을 바이너리로 읽는다

	while (1)
	{
		readcnt = fread((void*)buf, 1, BUF_SIZE, fp); // fp를 BUFSIZE의 양을 1씩 읽는다.
		if (readCnt < BUF_SIZE)
		{
			send(hClntSock, buf, readCnt, 0);
			break;;
		}
	}


}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}