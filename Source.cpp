#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32")

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1;
	static HWND hButton2;
	switch (msg)
	{
	case WM_CREATE:
		hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("TaskDialog"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1000, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("TaskDialogIndirect "), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1001, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hButton1, 10, 10, 256, 32, TRUE);
		MoveWindow(hButton2, 10, 50, 256, 32, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 1000)
		{
			int nButtonPressed = 0;
			TaskDialog(hWnd, GetModuleHandle(0), L"タイトル", L"メインの説明", L"補足", TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON, TD_INFORMATION_ICON/*MAKEINTRESOURCE(IDI_ICON1)*/, &nButtonPressed);
		}
		else if (LOWORD(wParam) == 1001)
		{
			TASKDIALOGCONFIG tdc = { sizeof(tdc) };
			tdc.hwndParent = hWnd;
			tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION;
			tdc.pszWindowTitle = L"タイトル";
			tdc.pszMainInstruction = L"メインの説明";
			tdc.pszContent = L"補足";
			tdc.cButtons = 2;
			TASKDIALOG_BUTTON tdb[2] = { { 100, L"ボタン1" },{ 101, L"ボタン2" } };
			tdc.pButtons = tdb;
			int nButtonPressed = 0;
			TaskDialogIndirect(&tdc, &nButtonPressed, 0, 0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPWSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
