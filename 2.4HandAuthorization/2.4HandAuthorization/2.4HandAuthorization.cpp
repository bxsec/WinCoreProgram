// 2.4HandAuthorization.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <shellapi.h>

// �ֶ�����Ȩ��
void Fun1()
{
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };

	// �������ԱȨ��
	sei.lpVerb = TEXT("runas");
	// ���г���
	sei.lpFile = TEXT("cmd.exe");

	sei.nShow = SW_SHOWNORMAL;

	if (!ShellExecuteEx(&sei))
	{
		DWORD dwStatus = GetLastError();
		if (dwStatus == ERROR_CANCELLED) {

		}
		else if (dwStatus == ERROR_FILE_NOT_FOUND)
		{

		}
	}
}


int main()
{
	



    return 0;
}

