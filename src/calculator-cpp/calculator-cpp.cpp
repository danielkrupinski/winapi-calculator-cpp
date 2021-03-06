#include "stdafx.h"
#include "calculator-cpp.h"
#include <string> 

#define MAX_LOADSTRING 100

HWND bAdd, bSubstr, bMultipl, bDiv;
HWND hNumber1, hNumber2, hResult;
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączonych w tym module kodu:
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

    // TODO: W tym miejscu umieść kod.


    // Zainicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULATORCPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjacje aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATORCPP));

    MSG msg;

    // Główna pętla wiadomości:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATORCPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULATORCPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojście wystąpienia w zmiennej globalnej

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 370, 350, nullptr, nullptr, hInstance, nullptr);

   bAdd = CreateWindowEx(0, "BUTTON", "Addition", WS_CHILD | WS_VISIBLE,
	   250, 0, 100, 50, hWnd, NULL, hInstance, NULL);
   bSubstr = CreateWindowEx(0, "BUTTON", "Subtraction", WS_CHILD | WS_VISIBLE,
	   250, 50, 100, 50, hWnd, NULL, hInstance, NULL);
   bMultipl = CreateWindowEx(0, "BUTTON", "Multiplication", WS_CHILD | WS_VISIBLE,
	   250, 100, 100, 50, hWnd, NULL, hInstance, NULL);
   bDiv = CreateWindowEx(0, "BUTTON", "Division", WS_CHILD | WS_VISIBLE,
	   250, 150, 100, 50, hWnd, NULL, hInstance, NULL);

   hNumber1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
	   50, 50, 150, 20, hWnd, NULL, hInstance, NULL);
   hNumber2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
	   50, 100, 150, 20, hWnd, NULL, hInstance, NULL);

   hResult = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "Result", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   50, 150, 150, 20, hWnd, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomości dla okna głównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno główne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
			Calc calc;
			calc.Buttons(lParam, hWnd);
            int wmId = LOWORD(wParam);
            // Analizuj zaznaczenia menu:
            switch (wmId)
            {
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
            // TODO: tutaj dodaj kod rysowania używający elementu hdc...
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

//Procedura obsługi wiadomości dla okna informacji o programie.
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

void Calc::Buttons(LPARAM lParam, HWND hWnd)
{
	if ((HWND)lParam == bAdd)
	{
		DWORD lenght = GetWindowTextLength(hNumber1);
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber1, buffer, lenght + 1);
		number1 = atof(buffer);
		lenght = GetWindowTextLength(hNumber2);
		buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber2, buffer, lenght + 1);
		number2 = atof(buffer);
		result = number1 + number2;
		std::string resultstr = std::to_string(result);
		SetWindowText(hResult, resultstr.c_str());
	}
	if ((HWND)lParam == bSubstr)
	{
		DWORD lenght = GetWindowTextLength(hNumber1);
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber1, buffer, lenght + 1);
		number1 = atof(buffer);
		lenght = GetWindowTextLength(hNumber2);
		buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber2, buffer, lenght + 1);
		number2 = atof(buffer);
		result = number1 - number2;
		std::string resultstr = std::to_string(result);
		SetWindowText(hResult, resultstr.c_str());
	}
	if ((HWND)lParam == bMultipl)
	{
		DWORD lenght = GetWindowTextLength(hNumber1);
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber1, buffer, lenght + 1);
		number1 = atof(buffer);
		lenght = GetWindowTextLength(hNumber2);
		buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber2, buffer, lenght + 1);
		number2 = atof(buffer);
		result = number1 * number2;
		std::string resultstr = std::to_string(result);
		SetWindowText(hResult, resultstr.c_str());
	}
	if ((HWND)lParam == bDiv)
	{
		DWORD lenght = GetWindowTextLength(hNumber1);
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber1, buffer, lenght + 1);
		number1 = atof(buffer);
		lenght = GetWindowTextLength(hNumber2);
		buffer = (LPSTR)GlobalAlloc(GPTR, lenght + 1);
		GetWindowText(hNumber2, buffer, lenght + 1);
		number2 = atof(buffer);
		result = number1 / number2;
		std::string resultstr = std::to_string(result);
		SetWindowText(hResult, resultstr.c_str());
	}
}
