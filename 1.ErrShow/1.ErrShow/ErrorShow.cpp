
#include <Windows.h>
#include <Windowsx.h>
#include <tchar.h>
#include "Resource.h"


#define ESM_POKECODEANDLOOKUP	(WM_USER + 100)
const TCHAR g_szAppName[] = TEXT("Error Show");

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int)
{
	HWND hwnd = FindWindow(TEXT("#32770"), TEXT("Error Show"));
	if (IsWindow(hwnd)){
		// 已经存在该程序，激活
		SendMessage(hwnd, ESM_POKECODEANDLOOKUP, _ttoi(pszCmdLine), 0);
	}
	else {
		DialogBoxParam(hinstExe, MAKEINTRESOURCE(IDD_ERRORSHOW), NULL, Dlg_Proc, _ttoi(pszCmdLine));
	}

	return 0;
}

INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
	{
		return Dlg_OnInitDialog(hwnd, (HWND)wParam, lParam);
	}
		break;
	case WM_COMMAND:
	{
		WORD lWPARAM = LOWORD(wParam);     //低16位，命令ID
		WORD hWPARAM = HIWORD(wParam);     //高16位，通知码
										   //lParam  发送命令消息的子窗口句柄
		Dlg_OnCommand(hwnd, lWPARAM, (HWND)lParam, hWPARAM);
	}
		break;
	case ESM_POKECODEANDLOOKUP:
	{
		SetDlgItemInt(hwnd, IDC_ERRORCODE, (UINT)wParam, FALSE);
		PostMessage(hwnd, WM_COMMAND, MAKEWPARAM((UINT)(int)(IDOK), (UINT)(BN_CLICKED)),
			(LPARAM)(HWND)(GetDlgItem(hwnd, IDOK)));
		SetForegroundWindow(hwnd);
	}
		break;
	}


	return FALSE;
}

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Set the dialog box icons
	//chSETDLGICONS(hwnd, IDI_ERRORSHOW);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)
		LoadIcon((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDI_ERRORSHOW)));
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)
		LoadIcon((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDI_ERRORSHOW)));

	//设置错误码不超过5位
	//Edit_LimitText(GetDlgItem(hwnd, IDC_ERRORCODE), 5);
	SendMessage(GetDlgItem(hwnd, IDC_ERRORCODE), EM_LIMITTEXT, (WPARAM)(5), 0);

	SendMessage(hwnd, ESM_POKECODEANDLOOKUP, lParam, 0);

	return TRUE;
}

void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDCANCEL:
		EndDialog(hwnd, id);
		break;
	case IDC_ALWAYSONTOP:
		SetWindowPos(hwnd, IsDlgButtonChecked(hwnd, IDC_ALWAYSONTOP) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0,
			0, 0, SWP_NOMOVE | SWP_NOSIZE);
		break;

	case IDC_ERRORCODE:
		EnableWindow(GetDlgItem(hwnd, IDOK), GetWindowTextLength(hwndCtl) > 0);
		break;

	case IDOK:
		//获取错误码
		DWORD dwError = GetDlgItemInt(hwnd, IDC_ERRORCODE, NULL, FALSE);
		HLOCAL hlocal = NULL;

		DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

		BOOL fOk = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_ALLOCATE_BUFFER,
			NULL, dwError, systemLocale,
			(PTSTR)&hlocal, 0, NULL
		);

		if (!fOk) {
			HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL,
				DONT_RESOLVE_DLL_REFERENCES);

			if (hDll != NULL) {
				fOk = FormatMessage(
					FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS |
					FORMAT_MESSAGE_ALLOCATE_BUFFER,
					hDll, dwError, systemLocale,
					(PTSTR)&hlocal, 0, NULL);
				FreeLibrary(hDll);
			}
		}
		if (fOk && (hlocal != NULL)) {
			SetDlgItemText(hwnd, IDC_ERRORTEXT, (PCTSTR)LocalLock(hlocal));
			LocalFree(hlocal);
		}
		else {
			SetDlgItemText(hwnd, IDC_ERRORTEXT,
				TEXT("No text found for this error number."));
		}
		break;

	}
}
