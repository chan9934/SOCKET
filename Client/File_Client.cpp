#include<iostream>
#include<WinSock2.h>

using namespace std;
#define BUF_SIZE 30

void ErrorHandling(const char* message);

int main()
{

}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}