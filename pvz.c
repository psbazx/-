#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   
#include <stdint.h>
#include <pthread.h>  
#include <time.h>
#include <windows.h>
#include <string.h>
#include <tlhelp32.h>
#pragma comment(lib, "pthreadVC2.lib")

unsigned char checksign = 0;
unsigned char checksign2 = 0;
int find_process();
DWORD WINAPI nocd(HANDLE phandle);
int main()
{
	int ppid = find_process();
	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, false, ppid);
	HANDLE hThread1;
	DWORD EXITCODE;
	unsigned int sun;
	unsigned int coin;
	unsigned int nopcode = 0x90;
	unsigned int origincode[2] = { 0x75 ,0x5F };
	unsigned char choice;
	while (true)
	{
		printf("1.修改阳光值\n");
		printf("2.无CD时间\n");
		printf("3.终极大嘴花\n");
		printf("4.修改金币\n");
		printf("plz input your choice:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("请输入阳光值:");
			scanf("%d", &sun);
			DWORD addr;
			ReadProcessMemory(phandle, (void*)(0x331C50 + 0x400000), &addr, sizeof(DWORD), NULL);
			ReadProcessMemory(phandle, (void*)(addr + 0x868), &addr, sizeof(DWORD), NULL);
			WriteProcessMemory(phandle, (void*)(addr + 0x5578), &sun, sizeof(DWORD), NULL);
			break;
		case 2:
			checksign ^= 1;
			if (checksign)
			{
				hThread1 = ::CreateThread(NULL, 0, nocd, phandle, 0, NULL);
			}
			break;
		case 3:
			checksign2 ^= 1;
			if (checksign2)
			{
				WriteProcessMemory(phandle, (void*)(0x467905), &nopcode, sizeof(BYTE), NULL);
				WriteProcessMemory(phandle, (void*)(0x467906), &nopcode, sizeof(BYTE), NULL);
			}
			else
			{
				WriteProcessMemory(phandle, (void*)(0x467905), &origincode[0], sizeof(BYTE), NULL);
				WriteProcessMemory(phandle, (void*)(0x467906), &origincode[1], sizeof(BYTE), NULL);
			}
			break;
		case 4:
			printf("请输入金币值(金币最小单位为10):");
			scanf("%d", &coin);
			DWORD addr2;
			ReadProcessMemory(phandle, (void*)(0x331C50 + 0x400000), &addr2, sizeof(DWORD), NULL);
			ReadProcessMemory(phandle, (void*)(addr2 + 0x94C), &addr2, sizeof(DWORD), NULL);
			WriteProcessMemory(phandle, (void*)(addr2 + 0x54), &coin, sizeof(DWORD), NULL);
			break;
		default:
			printf("error input\n");
			break;
		}
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
			if (wcscoll(stProcess.szExeFile, (L"popcapgame1.exe")) == 0)
			{
				processPid = stProcess.th32ProcessID;
				printf("检测到进程!\n");
				return processPid;
			}
			flag = Process32Next(hSnapShot, &stProcess);
		} while (flag);
	}
}
DWORD WINAPI nocd(HANDLE phandle)
{
	DWORD addr2;
	int i;
	unsigned int cd = 1;
	while (true)
	{
		if (!checksign)
		{
			return 0;
		}
		for (i = 0; i < 10; i++)
		{
			ReadProcessMemory(phandle, (void*)(0x331C50 + 0x400000), &addr2, sizeof(DWORD), NULL);
			ReadProcessMemory(phandle, (void*)(addr2 + 0x868), &addr2, sizeof(DWORD), NULL);
			ReadProcessMemory(phandle, (void*)(addr2 + 0x15C), &addr2, sizeof(DWORD), NULL);
			WriteProcessMemory(phandle, (void*)(addr2 + 0x70 + 0x50*i), &cd, sizeof(DWORD), NULL);
		}
	}
}
