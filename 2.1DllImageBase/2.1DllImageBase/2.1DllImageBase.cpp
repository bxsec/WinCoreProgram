// 2.1DllImageBase.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

extern "C" const IMAGE_DOS_HEADER __ImageBase;


void DumpModule() {
	//获取正在运行程序的基址
	HMODULE hModule = GetModuleHandle(NULL);
	_tprintf(TEXT("with GetModuleHandle(NULL) = 0x%x\r\n"), hModule);

	//通过 __ImageBase 获取基址
	_tprintf(TEXT("with __ImageBase = 0x%x\r\n"), (HINSTANCE)&__ImageBase);

	//获取的昂前模块的 hModule/hInstance
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

