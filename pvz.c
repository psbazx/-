#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include <tlhelp32.h>

int find_process();
int main()
{
	int ppid = find_process();
	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, false, ppid);
	unsigned int sun;
	while (true)
	{
		printf("输入阳光值:");
		scanf("%d", &sun);
		DWORD addr;
		ReadProcessMemory(phandle, (void*)(0x331C50+0x400000), &addr, sizeof(DWORD), NULL);
		ReadProcessMemory(phandle, (void*)(addr + 0x868), &addr, sizeof(DWORD), NULL);
		WriteProcessMemory(phandle, (void*)(addr + 0x5578), &sun, sizeof(DWORD), NULL);
	}
	return 0;
}
int find_process()
{
	printf("正在检测进程。。。\n");
	while (true)
	{
		int processPid;
		PROCESSENTRY32 stProcess;
		BOOL flag;
		memset(&stProcess, 0, sizeof(PROCESSENTRY32));
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		stProcess.dwSize = sizeof(PROCESSENTRY32);
		flag = Process32First(hSnapShot, &stProcess);
		do
		{
			if (strcmp((const char*)stProcess.szExeFile, (const char*)(L"popcapgame1.exe")) == 0)
			{
				processPid = stProcess.th32ProcessID;
				printf("检测到进程!\n");
				return processPid;
			}
			flag = Process32Next(hSnapShot, &stProcess);
		} while (flag);
	}
}