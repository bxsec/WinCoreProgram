// 1.1 CustomErrorCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <winerror.h>

void SetCusErrorCode()
{
	DWORD dwError = 0xA0000001;


	SetLastError(257);
}

int main()
{
	SetCusErrorCode();
	DWORD dwError = GetLastError();

    return 0;
}

