
#include <Windows.h>
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
		// �Ѿ����ڸó��򣬼���
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
		break;
	case WM_COMMAND:
	{
		WORD lWPARAM = LOWORD(wParam);     //��16λ������ID
		WORD hWPARAM = HIWORD(wParam);     //��16λ��֪ͨ��
										   //lParam  ����������Ϣ���Ӵ��ھ��
		Dlg_OnCommand(hwnd, lWPARAM, (HWND)lParam, hWPARAM);
	}
		break;
	case ESM_POKECODEANDLOOKUP:

		break;
	}


	return FALSE;
}

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	return TRUE;
}

void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

}
