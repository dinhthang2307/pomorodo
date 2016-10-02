// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Commctrl.h"
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
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{

	case WM_CREATE: {
		
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

		HWND AddButtonBreakTime = CreateWindow(L"BUTTON", L"+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			600, 50,20, 20, hWnd, (HMENU)IDC_BUTTON2,      
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      
		//static text
		HWND TimeBreak = CreateWindow(
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

		ValueOfBreakTime = CreateWindow(
			L"Edit",  // Predefined class; Unicode assumed 
			L"5",      // Button text 
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			475,         // x position 
			50,         // y position 
			100,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		//*********************************************************************************************//
		//draw Session area
		HWND MinusButtonSessionTime = CreateWindow(
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

		HWND AddButtonSession = CreateWindow(
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
						//static text
		HWND TimeSession = CreateWindow(
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

		ValueOfSessionTime = CreateWindow(
			L"Edit",  // Predefined class; Unicode assumed 
			L"25",      // Button text 
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			475,         // x position 
			200,         // y position 
			100,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		HWND NumberOfPomdoros = CreateWindow(
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

		ValueOfPomodoros = CreateWindow(
			L"Edit",  // Predefined class; Unicode assumed 
			L"0",     
			ES_LEFT | WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			455,         // x position 
			300,         // y position 
			200,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		HWND StartButton = CreateWindow(
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

		HWND ResetButton = CreateWindow(
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
			NULL);      // Pointer not needed.
						//static text

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
		}break;
		case IDC_BUTTON2: {
			iTimeBreak++;
		}break;
		case IDC_BUTTON3: {
			iSessionTime--;
		}break;
		case IDC_BUTTON4: {
			iSessionTime++;
		}break;
		case IDC_BUTTON5: {
			iTimeBreak = 5;
			iSessionTime=25 ;
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
