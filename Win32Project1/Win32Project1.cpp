// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Commctrl.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#include <time.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Alert(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(CTLCOLOR_BTN + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

//global var here
int iTimeBreak = 5;
int iSessionTime = 25;
int iNumberOfPomodoro = 0;
HWND ValueOfBreakTime;
HWND ValueOfSessionTime;
HWND ValueOfPomodoros;
WCHAR* bufferTimeBreak = new WCHAR[255];
WCHAR* bufferSessionTime = new WCHAR[255];
WCHAR* bufferNumberOfPomodoro = new WCHAR[255];
bool bSessionRunning = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case WM_CREATE: {

		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);

		// Lấy font hệ thống
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);



		//draw bread area
		HWND MinusButtonBreakTime = CreateWindowEx(0, L"BUTTON", L"-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
			450,
			50,
			20,
			20,
			hWnd,
			(HMENU)IDC_BUTTON1,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);
		SendMessage(MinusButtonBreakTime, WM_SETFONT, WPARAM(hFont), TRUE);

		HWND AddButtonBreakTime = CreateWindowEx(0,L"BUTTON", L"+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			600, 50, 20, 20, hWnd, (HMENU)IDC_BUTTON2,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		SendMessage(AddButtonBreakTime, WM_SETFONT, WPARAM(hFont), TRUE);

		//static text
		HWND TimeBreak = CreateWindowEx(0,
			L"Static",  // Predefined class; Unicode assumed 
			L"Break Time",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			475,         // x position 
			10,         // y position 
			100,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(TimeBreak, WM_SETFONT, WPARAM(hFont), TRUE);

		ValueOfBreakTime = CreateWindowEx(0,
			L"Edit",  // Predefined class; Unicode assumed 
			L"5",      // Button text 
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD|ES_READONLY,  // Styles 
			475,         // x position 
			50,         // y position 
			100,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(ValueOfBreakTime, WM_SETFONT, WPARAM(hFont), TRUE);
		//*********************************************************************************************//
		//draw Session area
		HWND MinusButtonSessionTime = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"-",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			450,         // x position 
			200,         // y position 
			20,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			(HMENU)IDC_BUTTON3,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(MinusButtonBreakTime, WM_SETFONT, WPARAM(hFont), TRUE);
		HWND AddButtonSession = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"+",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			600,         // x position 
			200,         // y position 
			20,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			(HMENU)IDC_BUTTON4,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(AddButtonSession, WM_SETFONT, WPARAM(hFont), TRUE);
						//static text
		HWND TimeSession = CreateWindowEx(0,
			L"Static",  // Predefined class; Unicode assumed 
			L"Session Time",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			475,         // x position 
			160,         // y position 
			100,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(TimeSession, WM_SETFONT, WPARAM(hFont), TRUE);
		ValueOfSessionTime = CreateWindowEx(0,
			L"Edit",  // Predefined class; Unicode assumed 
			L"25",      // Button text 
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD|ES_READONLY,  // Styles 
			475,         // x position 
			200,         // y position 
			100,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(ValueOfSessionTime, WM_SETFONT, WPARAM(hFont), TRUE);
		HWND NumberOfPomdoros = CreateWindowEx(0,
			L"Static",  // Predefined class; Unicode assumed 
			L"Number Of Pomdoros:",      // Button text 
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			450,         // x position 
			250,         // y position 
			200,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(NumberOfPomdoros, WM_SETFONT, WPARAM(hFont), TRUE);
		ValueOfPomodoros = CreateWindowEx(0,
			L"Edit",  // Predefined class; Unicode assumed 
			L"0",
			ES_CENTER | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD|ES_READONLY,  // Styles 
			455,         // x position 
			300,         // y position 
			200,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		SendMessage(ValueOfPomodoros, WM_SETFONT, WPARAM(hFont), TRUE);
		HWND StartButton = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Start",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			450,         // x position 
			340,         // y position 
			50,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			(HMENU)IDC_BUTTON5,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
						//static text
		SendMessage(StartButton, WM_SETFONT, WPARAM(hFont), TRUE);
		HWND ResetButton = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Reset",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			520,         // x position 
			340,         // y position 
			50,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			(HMENU)IDC_BUTTON6,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      
		SendMessage(ResetButton, WM_SETFONT, WPARAM(hFont), TRUE);
		return 0;
	}break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_BUTTON1: {
			iTimeBreak--;
			wsprintf(bufferTimeBreak, L"%d", iTimeBreak);
			SetWindowText(ValueOfBreakTime, bufferTimeBreak);

			if (!bufferTimeBreak)
				delete[] bufferTimeBreak;
		}break;
		case IDC_BUTTON2: {
			iTimeBreak++;
			wsprintf(bufferTimeBreak, L"%d", iTimeBreak);
			SetWindowText(ValueOfBreakTime, bufferTimeBreak);

			if (!bufferTimeBreak)
				delete[] bufferTimeBreak;
		}break;
		case IDC_BUTTON3: {
			iSessionTime--;
			wsprintf(bufferSessionTime, L"%d", iSessionTime);
			SetWindowText(ValueOfSessionTime, bufferSessionTime);

			if (!bufferSessionTime)
				delete[] bufferSessionTime;
		}break;
		case IDC_BUTTON4: {
			iSessionTime++;
			wsprintf(bufferSessionTime, L"%d", iSessionTime);
			SetWindowText(ValueOfSessionTime, bufferSessionTime);

			if (!bufferSessionTime)
				delete[] bufferSessionTime;
		}break;
		case IDC_BUTTON6: {
			iTimeBreak = 5;
			iSessionTime = 25;


			wsprintf(bufferSessionTime, L"%d", iSessionTime);
			wsprintf(bufferTimeBreak, L"%d", iTimeBreak);
			SetWindowText(ValueOfSessionTime, bufferSessionTime);
			SetWindowText(ValueOfBreakTime, bufferTimeBreak);


			if (!bufferSessionTime)
				delete[] bufferSessionTime;
			if (!bufferTimeBreak)
				delete[] bufferTimeBreak;
		}break;

		case IDC_BUTTON5: {

			//main code here
			int iSecondSession = 60 * iSessionTime;
			int iSecondBreak = 60 * iTimeBreak;
			int iSecondPassed;
			int lStartTime = clock();
			for(;;) {
				if (bSessionRunning == true) {
					iSecondPassed = (clock() - lStartTime);
					if (iSecondPassed >= iSecondSession) {
						DialogBox(hInst, MAKEINTRESOURCE(IDD_ALERTBOX), NULL, Alert);
						iNumberOfPomodoro++;
						bSessionRunning = false;
						wsprintf(bufferNumberOfPomodoro, L"%d", iNumberOfPomodoro);
						SetWindowText(ValueOfPomodoros, bufferNumberOfPomodoro);
						lStartTime = clock();
					}
				}
				else if(bSessionRunning==false){
					if (iNumberOfPomodoro < 4) {
						iSecondPassed = (clock() - lStartTime);
						if (iSecondPassed >= iSecondBreak) {
							DialogBox(hInst, MAKEINTRESOURCE(IDD_ALERTBOX), NULL, Alert);
							bSessionRunning = true;
							lStartTime = clock();
						}
					}
					else {
						iSecondPassed = (clock() - lStartTime);
						if (iSecondPassed >= 15*60) {
							DialogBox(hInst, MAKEINTRESOURCE(IDD_ALERTBOX), NULL, Alert);
							bSessionRunning = true;
							lStartTime = clock();
							iNumberOfPomodoro = 0;
						}
					}
				}
				if (!bufferSessionTime)
					delete[] bufferSessionTime;

			}
			
		}break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Alert(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	
	return (INT_PTR)FALSE;
}
