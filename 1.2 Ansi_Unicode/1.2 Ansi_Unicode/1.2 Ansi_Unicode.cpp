// 1.2 Ansi_Unicode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>


bool CharToWChar(LPSTR pChar, LPWSTR* pWchar)
{
	//1. ��ȡת������Ҫ�Ŀռ��С
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

	//����ת����洢�ռ�
	*pChar = new char[dwBufSize];
	memset(*pChar, 0, dwBufSize);

	int nRet = WideCharToMultiByte(CP_OEMCP, 0, pWchar, -1, *pChar, dwBufSize, NULL, FALSE);
	if (nRet <= 0)
		return false;

	return true;
}

int main()
{
	wchar_t *wpStr = L"���ǿ��ַ�";
	char *pStr = "����խ�ַ�";
	
	wchar_t *pwStr1 = NULL;
	if (!CharToWChar(pStr, &pwStr1))
	{
		printf("խ�ַ�ת���ɿ��ַ�ʧ��...");
	}

	char *pStr2 = NULL;
	if (!WCharToChar(wpStr, &pStr2))
	{
		printf("���ַ�תխ�ַ�ʧ��...");
	}


    return 0;
}

