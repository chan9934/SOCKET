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

	int a = 0;

		fputs("Operand Count : ", stdout);

		cin >> a;
		string s = " ";
		char b = ' ';
		for (int i = 0; i < a; ++i)
		{
			
			
			printf("Operand %d: ", i + 1);
			cin >> b;
			s += b + ' ';
			cout << "\n";
			
		}
		cout << "Operator: ";
		cin >> b;
		s += b;


		
		send(hSocket, const_cast<char*>(s.c_str()), s.length(), 0);

		recv(hSocket, message, 4, 0);
		cout << message;
		//fgets(message, BUF_SIZE, stdin);//stdin ǥ�� �Է�

		//if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) // �� ��Ʈ�� ��
		//{
		//	break;
		//}
	//int recv_Len = 0;
		//strLen = send(hSocket, message, strlen(message), 0); //strlen ���ڿ� ����

		//int Count = 3;

	/*	while (strLen > recv_Len)
		{
			int recv_Cnt = ;
			if (recv_Cnt == SOCKET_ERROR)
			{
				ErrorHandling("read() error");
			}
			recv_Len += recv_Cnt;


		}*/

		//message[strLen] = 0;
		//printf("Message from server: %s", message);
	
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