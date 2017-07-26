// 2.1DllImageBase.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

extern "C" const IMAGE_DOS_HEADER __ImageBase;


void DumpModule() {
	//��ȡ�������г���Ļ�ַ
	HMODULE hModule = GetModuleHandle(NULL);
	_tprintf(TEXT("with GetModuleHandle(NULL) = 0x%x\r\n"), hModule);

	//ͨ�� __ImageBase ��ȡ��ַ
	_tprintf(TEXT("with __ImageBase = 0x%x\r\n"), (HINSTANCE)&__ImageBase);

	//��ȡ�İ�ǰģ��� hModule/hInstance
	hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(PCTSTR)DumpModule,
		&hModule);
	_tprintf(TEXT("with GetModuleHandleEx = 0x%x\r\n"), hModule);
}

int main()
{
	DumpModule();

	system("pause");

    return 0;
}

