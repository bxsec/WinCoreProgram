// 2.2ProcessEnvBlock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <strsafe.h>
#include <stdlib.h>

void DumpEnvStrings() {
	PTSTR pEnvBlock = GetEnvironmentStrings();

	TCHAR szName[MAX_PATH];
	TCHAR szValue[MAX_PATH];
	PTSTR pszCurrent = pEnvBlock;
	HRESULT hr = S_OK;
	PCTSTR pszPos = NULL;
	int current = 0;

	while (pszCurrent != NULL) {
		// 跳过无意义字符串  如："=::=::\"
		if (*pszCurrent != TEXT('=')) {
			// 查找 '=' 分隔符
			pszPos = _tcschr(pszCurrent, TEXT('='));

			pszPos++;

			//获取变量名
			size_t cbNameLength = (size_t)pszPos - (size_t)pszCurrent - sizeof(TCHAR);
			hr = StringCbCopyN(szName, MAX_PATH, pszCurrent, cbNameLength);
			if (FAILED(hr)) {
				break;
			}
			// 获取值
			hr = StringCchCopyN(szValue, MAX_PATH, pszPos, _tcslen(pszPos) + 1);
			if (SUCCEEDED(hr)) {
				_tprintf(TEXT("[%u] %s=%s\r\n"), current, szName, szValue);
			}
			else if (hr == STRSAFE_E_INSUFFICIENT_BUFFER) {
				_tprintf(TEXT("[%u] %s=%s...\r\n"), current, szName, szValue);
			}
			else {
				_tprintf(TEXT("[%u] %s=???\r\n"), current, szName);
				break;
			}
		}
		else {
			_tprintf(TEXT("[%u] %s\r\n"), current, pszCurrent);
		}

		//下一个环境变量
		current++;

		// 到环境字符串末尾
		while (*pszCurrent != TEXT('\0'))
			pszCurrent++;
		pszCurrent++;

		//判断是否是环境变量中最后一个字符串
		if (*pszCurrent == TEXT('\0'))
			break;
	}
	FreeEnvironmentStrings(pEnvBlock);
}

void DumpEnvVariables(PTSTR pEnvBlock[]) {
	int current = 0;
	PTSTR* pElement = (PTSTR*)pEnvBlock;
	PTSTR pCurrent = NULL;
	while (pElement != NULL)
	{
		pCurrent = (PTSTR)(*pElement);
		if (pCurrent == NULL) {
			pElement = NULL;
		}
		else {
			_tprintf(TEXT("[%u] %s\r\n"), current, pCurrent);
			current++;
			pElement++;
		}
	}
}


int main(int argc, TCHAR **argv, TCHAR **env)
{
	DumpEnvStrings();
	_tprintf(TEXT("====================================================="));

	DumpEnvVariables(env);

	system("pause");

    return 0;
}

