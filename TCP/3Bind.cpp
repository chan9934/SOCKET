#include<WinSock2.h>
#include<iostream>

using namespace std;

int main()
{
	SOCKET servSock;
	struct sockaddr_in servAddr;
	const char* servPort = "9190";

	servSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(servPort));

	bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr));


}