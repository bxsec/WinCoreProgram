// 1.1 CustomErrorCode.cpp : �������̨Ӧ�ó������ڵ㡣
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

