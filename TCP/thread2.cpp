#include <iostream>
#include <WinSock2.h>
#include <process.h>

using namespace std;

unsigned WINAPI ThreadFunc(void* arg);

int main(int argc, char* argv[])
{
	HANDLE hThread;
	DWORD wr;
	unsigned threadID;
	int params = 6;

	hThread = (HANDLE*)_beginthreadex(NULL, 0, ThreadFunc, (void*)&params, 0, &threadID);
	if (hThread == 0)
	{
		puts("beginthreadex() error");
		return -1;
	}

	if ((wr = WaitForSingleObject(hThread, INFINITE)) == WAIT_FAILED)
	{
		puts("WaitForSigleObject() Error");
		return -1;
	}

	printf("Wait Result: %s \n", (wr == WAIT_OBJECT_0) ? "signaled" : "time-out");
	puts("end of main");
	return 0;
}
unsigned WINAPI ThreadFunc(void* arg)
{
	int i;
	int cnt = *((int*)arg);
	for (i = cnt-1; i >= 0; --i)
	{
		Sleep(1000);
		if (i != 0)
		{
			printf("Remained Time : %d\n", i); 
		}
	}
	return 0;
}