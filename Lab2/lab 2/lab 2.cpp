// lab 2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "lab 2.h"

#define MAX_LOADSTRING 100
#define BUFFER_SIZE 128

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hAddButton;
HWND hClearButton;
HWND hToRightButton;
HWND hDeleteButton;
HWND hLabel;
HWND hListBox1;
HWND hListBox2;
HWND hEdit;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 600, nullptr, nullptr, hInstance, nullptr);

   hAddButton = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
	   WS_CHILD | WS_VISIBLE, 400, 100, 100, 30, hWnd, HMENU(10001), hInstance, NULL);
   SetWindowTextW(hAddButton, L"&Add");

   hClearButton = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
	   WS_CHILD | WS_VISIBLE, 400, 150, 100, 30, hWnd, HMENU(10002), hInstance, NULL);
   SetWindowTextW(hClearButton, L"&Clear");

   hToRightButton = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
	   WS_CHILD | WS_VISIBLE, 400, 200, 100, 30, hWnd, HMENU(10003), hInstance, NULL);
   SetWindowTextW(hToRightButton, L"&To Right");

   hDeleteButton = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
	   WS_CHILD | WS_VISIBLE, 400, 250, 100, 30, hWnd, HMENU(10004), hInstance, NULL);
   SetWindowTextW(hDeleteButton, L"&Delete");

   hListBox1 = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
	   WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 50, 35, 300, 200,
	   hWnd, NULL, hInstance, NULL);

   hListBox2 = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
	   WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 550, 35, 300, 200,
	   hWnd, NULL, hInstance, NULL);

   hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
	   WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 375, 50, 150, 30,
	   hWnd, NULL, hInstance, NULL);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
 
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;

			case IDM_ADD://Add button
				{
					wchar_t buffer[BUFFER_SIZE] = {};
					GetWindowText(hEdit, buffer, 128);

					if (!SearchStr(buffer, hListBox1))
					{
						SetWindowText(hEdit, L"");
						SendMessage(hListBox1, LB_INSERTSTRING, NULL, (LPARAM)buffer);
					}
					else
					{
						MessageBox(NULL, L"String already exists", L"Warning", MB_OK | MB_ICONWARNING);
					}
				}
				break;

			case IDM_CLEAR:
				SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);
				SendMessage(hListBox2, LB_RESETCONTENT, 0, 0);
				break;

			case IDM_TO_RIGHT:
				{
					wchar_t buffer[BUFFER_SIZE] = {};
					int number = SendMessage(hListBox1, LB_GETCURSEL, 0, wParam);
					
					if (number != -1) 
					{
						SendMessage(hListBox1, LB_GETTEXT, number, (LPARAM)buffer);
						
						if (!SearchStr(buffer, hListBox2))
						{
							SendMessage(hListBox2, LB_INSERTSTRING, NULL, (LPARAM)buffer);
						}
						else
						{
							MessageBox(NULL, L"String already exists", L"Warning", MB_OK | MB_ICONWARNING);
						}
					}
					else
					{
						MessageBox(NULL, L"Nothing selected", L"Warning", MB_OK | MB_ICONWARNING);
					}
				}
				break;
				

			case IDM_DELETE:
				{
				int number1 = SendMessage(hListBox1, LB_GETCURSEL, 0, wParam);
				int number2 = SendMessage(hListBox2, LB_GETCURSEL, 0, wParam);
				if (number1 != -1) 
				{
					SendMessage(hListBox1, LB_DELETESTRING, number1, 0);
				}
				if (number2 != -1)
				{
					SendMessage(hListBox2, LB_DELETESTRING, number2, 0);
				}
				if (number1 == -1 && number2 == -1) 
				{
					MessageBox(NULL, L"Nothing selected", L"Warning", MB_OK | MB_ICONWARNING);
				}
					
				}
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

// Обработчик сообщений для окна "О программе".
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

bool SearchStr(wchar_t* str , HWND src)
{
	wchar_t buffer[BUFFER_SIZE];

	int lines = SendMessage(hListBox1, LB_GETCOUNT, 0, 0);

	for (int i = 0; i < lines; i++)
	{
		SendMessage(src, LB_GETTEXT, i, (LPARAM)buffer);

		if (!wcscmp(str, buffer))
		{
			return true;
		}
	}
	return false;
}