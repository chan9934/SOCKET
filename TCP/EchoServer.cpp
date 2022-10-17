#include <iostream>
#include <string>
#include <WinSock2.h>

#define BUF_SIZE 1024

using namespace std;

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	char message[BUF_SIZE];
	int strLen, i;

	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;

	if (argc != 2) //포트넘버의 길이가 2여야한다
	{
		printf("Usage : %s<port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 성공 시 0 반환
	{
		ErrorHandling("WSAStartup() error!");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() error!");
	}

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = (INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1])); // 왜 1이지
	
	if (bind(hServSock, (SOCKADDR*)(&servAdr), sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	if (listen(hServSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	clntAdrSize = sizeof(clntAdr);

	for (i = 0; i < 5; ++i)
	{
		hClntSock = accept(hServSock, (SOCKADDR*)(&clntAdr), &clntAdrSize); // 이건 왜 또 &로 받지
		if (hClntSock == SOCKET_ERROR)
		{
			ErrorHandling("accept() error");
		}
		else
			printf("Connected client %d \n", i + 1);

		//while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0)
		//{
		//	send(hClntSock, message, strLen, 0);

		//}
		recv(hClntSock, message, BUF_SIZE, 0);
		string a = message;

		string b;
		string c = a.substr(a.rfind(' ')+1);
		int g;
		if (c == "+")
		{
			while (1)
			{
				b = a.substr(0, a.find(' '));
				int f = stoi(b);
				g += f;
			}
		}


		closesocket(hClntSock);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;


}
void ErrorHandling(const char* message)
{
	fputs(message, stderr); // stderr  표준 에러 출력 장치(모니터) 로 출력되는 메시지는 버퍼링없이 즉시 출력된다. 따라서 문제가 생겼을 경우 즉시 출력된다.
	fputc('\n', stderr);
	exit(1); // 프로세스 강제종료

}