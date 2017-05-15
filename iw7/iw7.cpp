// iw7.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "iw7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

//CWinApp theApp;

using namespace std;

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }
#else
extern "C" { int __afxForceUSRDLL; }
#endif

typedef int(__stdcall* _CBuf_AddText)(int, const char*);
_CBuf_AddText CBuf_AddText = (_CBuf_AddText)0x140B34B10;

DWORD WINAPI MainWindow(HMODULE hMod) {
	HMODULE iw7 = GetModuleHandle(NULL);

	CBuf_AddText(0, "map cp_zmb\n");
	MessageBoxA(NULL, "working", "ok", MB_OK);

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