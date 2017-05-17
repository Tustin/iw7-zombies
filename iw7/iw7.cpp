// iw7.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "iw7.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }
#else
extern "C" { int __afxForceUSRDLL; }
#endif

typedef int(__stdcall* _CBuf_AddText)(int, const char*);
_CBuf_AddText CBuf_AddText = (_CBuf_AddText)0x140B34B10;

typedef int(__stdcall* _SV_GameSendServerCommand)(int, int, const char*);
_SV_GameSendServerCommand SV_GameSendServerCommand = (_SV_GameSendServerCommand)0x140BF7640;



CButton *GetSelectedRadioButton(HWND hDlg) {
	CButton* gssc = (CButton*)GetDlgItem(hDlg, IDC_GSSC);
	CButton* cbuf = (CButton*)GetDlgItem(hDlg, IDC_CBUF);

	if (gssc->IsDlgButtonChecked(IDC_GSSC) != BST_CHECKED && cbuf->IsDlgButtonChecked(IDC_CBUF) != BST_CHECKED) {
		return nullptr;
	}
	return gssc->IsDlgButtonChecked(IDC_GSSC) ? gssc : cbuf;
}

BOOL CALLBACK EventHandler(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (wParam)
			{
			case IDOK: {

				char cmd[1024];
				int commandLen = strlen(cmd);

				GetDlgItemTextA(hDlg, IDC_EDIT1, cmd, commandLen);

				switch (selectedCommandType) {
				case CommandTypes::GSSC:
					SV_GameSendServerCommand(-1, 0, cmd);
					break;
				case CommandTypes::CBUF:
					CBuf_AddText(0, cmd);
					break;
				default:
					MessageBoxA(NULL, "Error", "Please select a command mode.", MB_OK);
					break;
				}

				break;
			}
			case IDC_GSSC:
				selectedCommandType = CommandTypes::GSSC;
				break;
			case IDC_CBUF:
				selectedCommandType = CommandTypes::CBUF;
				break;
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		ExitThread(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ExitThread(0);
		break;
	default:
		return DefWindowProc(hDlg, uMsg, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI MainWindow(HMODULE hMod) {
	HMODULE iw7 = GetModuleHandle(NULL);

	DialogBox(hMod, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)EventHandler);
	ExitThread(0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainWindow, hModule, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}