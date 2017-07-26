// 2.4HandAuthorization.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <shellapi.h>

// 手动提升权限
void Fun1()
{
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };

	// 请求管理员权限
	sei.lpVerb = TEXT("runas");
	// 运行程序
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

