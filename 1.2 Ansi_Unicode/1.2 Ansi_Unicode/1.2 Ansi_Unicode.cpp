// 1.2 Ansi_Unicode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


bool CharToWChar(LPSTR pChar, LPWSTR* pWchar)
{
	//1. 获取转换后需要的空间大小
	DWORD dwBufSize = MultiByteToWideChar(CP_ACP, 0, pChar, strlen(pChar), NULL, 0);

	*pWchar = new wchar_t[dwBufSize+1];
	wmemset(*pWchar, 0, dwBufSize+1);

	int nRet = MultiByteToWideChar(CP_ACP, 0, pChar, strlen(pChar),*pWchar, dwBufSize);

	if (nRet <= 0)
		return false;
	return true;
}

bool WCharToChar(LPWSTR pWchar, LPSTR *pChar)
{
	DWORD dwBufSize = WideCharToMultiByte(CP_OEMCP, 0, pWchar, -1, NULL, 0, NULL, FALSE);

	//分配转换后存储空间
	*pChar = new char[dwBufSize];
	memset(*pChar, 0, dwBufSize);

	int nRet = WideCharToMultiByte(CP_OEMCP, 0, pWchar, -1, *pChar, dwBufSize, NULL, FALSE);
	if (nRet <= 0)
		return false;

	return true;
}

int main()
{
	wchar_t *wpStr = L"这是宽字符";
	char *pStr = "这是窄字符";
	
	wchar_t *pwStr1 = NULL;
	if (!CharToWChar(pStr, &pwStr1))
	{
		printf("窄字符转换成宽字符失败...");
	}

	char *pStr2 = NULL;
	if (!WCharToChar(wpStr, &pStr2))
	{
		printf("宽字符转窄字符失败...");
	}


    return 0;
}

