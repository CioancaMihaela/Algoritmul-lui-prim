// Alg_prim.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Alg_prim.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MINIM 10000

int n;
int a[9][9], min, i_min, j_min;
int sters[9];
int marcat[9];
int v[];
int *vect;
int arbore[9][2];
int count;
int b[10][10];
LPCWSTR *result[10];


enum operation { BUC,CT,OR, IS, GL, DR, CR, TM,SB};
operation op;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ALG_PRIM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ALG_PRIM));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ALG_PRIM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(180, 180, 180));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ALG_PRIM);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, 1000,600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void alege(int *min, int*i_min, int*j_min)
{
	int j;
	int i;
	*min = MINIM;
	sters[*i_min] = 1;
	for (i = *i_min; i < n; i++)
	{
		for (j = *j_min; j < n; j++)
		{
			if (sters[j] == 0 && marcat[i] != 1)
			{
				if (b[i][j] < *min)
				{
					*min = b[i][j];
					*j_min = j;
					*i_min = i;
				}
			}
		}
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
LPCWSTR convertCharArrayToLPCWSTR(char* charArray)
{
	const char* cs = charArray;
	wchar_t filename[4096] = { 0 };
	MultiByteToWideChar(0, 0, &cs[1], strlen(&cs[1]), filename, strlen(&cs[1]));
	return filename;
}
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{


	case WM_CREATE:
		//Creaza orasele
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			600, 100, 200, 25, hWnd, (HMENU)IDC_HR1, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("   OK "),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			680, 150, 50, 25, hWnd, (HMENU)IDC_BUT, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("                       Alegeti   orasele"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			300, 20, 300, 30, hWnd, (HMENU)IDC_HR4, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Oradea"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			350, 100, 85, 25, hWnd, (HMENU)IDC_OR, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Timisoara"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			350, 200, 85, 25, hWnd, (HMENU)IDC_TM, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Drobeta"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			200, 100, 85, 25, hWnd, (HMENU)IDC_DR, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Craiova"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			50, 200, 85, 25, hWnd, (HMENU)IDC_CR, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Bucuresti"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			50, 100, 85, 25, hWnd, (HMENU)IDC_BUC, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Sibiu"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			350, 150, 85, 25, hWnd, (HMENU)IDC_SB, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Iasi"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			200, 200, 85, 25, hWnd, (HMENU)IDC_IS, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Constanta"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			50, 150, 85, 25, hWnd, (HMENU)IDC_CT, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("Galati"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			200, 150, 85, 25, hWnd, (HMENU)IDC_GL, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			200,250, 600, 250, hWnd, (HMENU)IDC_HR2, GetModuleHandle(NULL), NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("GATA"),
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
			660, 200, 85, 25, hWnd, (HMENU)IDC_HR3, GetModuleHandle(NULL), NULL);





	case WM_COMMAND:
	{wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);
	int res[9];
	// Parse the menu selections:
	switch (wmId)
	{
	case IDC_BUC:
	{
					SetDlgItemText(hWnd, IDC_HR1, TEXT("BUCURESTI"));
					op = BUC;
					break;
	}
	case IDC_OR:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("ORADEA"));
				   op = OR;
				   break;


	}
	case IDC_CR:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("CRAIOVA"));
				   op = CR;
				   break;
	}
	case IDC_DR:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("DROBETA"));
				   op = DR;
				   break;
	}
	case IDC_GL:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("GALATI"));
				   op = GL;
				   break;
	}
	case IDC_CT:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("CONSTANTA"));
				   op = CT;
				   break;
	}
	case IDC_IS:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("IASI"));
				   op = IS;
				   break;
	}
	case IDC_SB:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("SIBIU"));
				   op = SB;
				   break;
	}
	case IDC_TM:
	{
				   SetDlgItemText(hWnd, IDC_HR1, TEXT("TIMISOARA"));
				   op = TM;
				   break;
	}


	case IDC_BUT:
	{
					
					
					switch (op)
					{
					case BUC:
						res[1] = 1;
						break;

					case TM:
						res[9] = 9;
						break;

					case SB:
						res[8] = 8;
						break;
					case IS:
						res[6] = 6;
						break;
					case DR:
						res[4] = 4;
						break;
					case CR:
						res[3] = 3;
						break;
					case CT:
						res[2] = 2;
						break;
					case GL:
						res[5] = 5;
						break;
					case OR:
						res[7] = 7;
						break;

					}
					

	}
	case IDC_HR3:
	{
	/*char*q[9] = { "Bucuresti", "Constanta", "Craiova", "Drobeta", "Galati", "Iasi", "Oradea", "Sibiu", "Timisoara" };
	int j = 0;
	for (int i = 1; i <= 9; i++)
	{
		if (res[i] != 0)
		{
			n++;
			
			vect[j] = i;
			j++;
		}
	}

	FILE*f;

	
	
	min = MINIM;
	f = fopen("matrice.txt", "r");
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			fscanf(f, "%d", &a[i][k]);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = a[vect[i]][vect[j]];
		}
	}



	for (int i = 0; i < 9; i++)
	{
		marcat[i] = 0;
		sters[i] = 0;
	}


	sters[0] = 1;
	marcat[0] = 1;
	for (int i = 1; i < n; i++)
	{
		if (b[0][i] < min)
		{
			min = b[0][i];
			arbore[count][0] = 0;
			arbore[count][1] = i;
		}

	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (marcat[i] != 1)
			{

				i_min = i;
				j_min = j;
				alege(&min, &i_min, &j_min);
				marcat[i_min] = 1;
				sters[j_min] = 1;
				count++;
				arbore[count][0] = i_min;
				arbore[count][1] = j_min;
			}
		}
	}


	for (int i = 0; i < n - 1; i++)
	{
		printf("%d,%d cu costul %d \n", arbore[i][0], arbore[i][1], b[arbore[i][0]][arbore[i][1]]);
		SetDlgItemText(hWnd, IDC_HR2, convertCharArrayToLPCWSTR( q[arbore[i][0]]));
		SetDlgItemInt(hWnd, IDC_HR2, b[arbore[i][0]][arbore[i][1]], true);
		SetDlgItemText(hWnd, IDC_HR2, convertCharArrayToLPCWSTR( q[arbore[i][1]]));
		
	}
	*/
					for (int i = 0; i < 9; i++)
					{
						if (res[i] != 0)
							SetDlgItemInt(hWnd, IDC_HR2, res[i], true);
					}
					break;
	}
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

		break;
	}
case WM_PAINT:
	{hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	HPEN hpenOld = static_cast<HPEN>(SelectObject(hdc, GetStockObject(DC_PEN)));
	HBRUSH hbrushOld = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(NULL_BRUSH)));

	/*// Calculate the dimensions of the 4 equal rectangles.
	RECT rcWindow;
	GetClientRect(hWnd, &rcWindow);

	RECT rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8, rc9;
	rc1 = rc2 = rc3 = rc4 = rc5 = rc6 = rc7 = rc8 = rc9 = rcWindow;

	rc1.right = (rcWindow.right - rcWindow.left) / 3;
	rc1.bottom = (rcWindow.bottom - rcWindow.top) / 3;

	rc2.left = rc1.right;
	rc2.right = (rcWindow.right - rcWindow.left) / 1.5;
	rc2.bottom = rc1.bottom;

	rc3.left = rc2.right;
	rc3.bottom = rc1.bottom;

	rc4.top = rc1.bottom;
	rc4.right = rc1.right;
	rc4.bottom = (rcWindow.bottom - rcWindow.top) / 1.5;
	rc4.left = rc1.left;

	rc5.top = rc1.bottom;
	rc5.left = rc4.right;
	rc5.right = rc2.right;
	rc5.bottom = rc4.bottom;

	rc6.top = rc1.bottom;
	rc6.right = rc3.right;
	rc6.bottom = rc4.bottom;
	rc6.left = rc5.right;

	rc7.top = rc4.bottom;
	rc7.right = rc4.right;
	rc7.bottom = (rcWindow.bottom - rcWindow.top);
	rc7.left = rc1.left;

	rc8.top = rc4.bottom;
	rc8.bottom = rc7.bottom;
	rc8.right = rc5.right;
	rc8.left = rc7.right;

	rc9.top = rc4.bottom;
	rc9.bottom = rc7.bottom;
	rc9.right = rc6.right;
	rc9.left = rc8.right;

	// Optionally, deflate each of the rectangles by an arbitrary amount so that
	// they don't butt up right next to each other and we can distinguish them.
	InflateRect(&rc1, -5, -5);
	InflateRect(&rc2, -5, -5);
	InflateRect(&rc3, -5, -5);
	InflateRect(&rc4, -5, -5);
	InflateRect(&rc5, -5, -5);
	InflateRect(&rc6, -5, -5);
	InflateRect(&rc7, -5, -5);
	InflateRect(&rc8, -5, -5);
	InflateRect(&rc9, -5, -5);


	// Draw (differently-colored) borders around these rectangles.
	SetDCPenColor(hdc, RGB(255, 0, 0));    // red
	Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
	SetDCPenColor(hdc, RGB(0, 255, 0));    // green
	Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
	SetDCPenColor(hdc, RGB(0, 0, 255));    // blue
	Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
	SetDCPenColor(hdc, RGB(255, 0, 0));
	Rectangle(hdc, rc4.left, rc4.top, rc4.right, rc4.bottom);
	SetDCPenColor(hdc, RGB(0, 255, 0));
	Rectangle(hdc, rc5.left, rc5.top, rc5.right, rc5.bottom);
	SetDCPenColor(hdc, RGB(0, 0, 255));
	Rectangle(hdc, rc6.left, rc6.top, rc6.right, rc6.bottom);
	SetDCPenColor(hdc, RGB(255, 0, 0));
	Rectangle(hdc, rc7.left, rc7.top, rc7.right, rc7.bottom);
	SetDCPenColor(hdc, RGB(0, 255, 0));
	Rectangle(hdc, rc8.left, rc8.top, rc8.right, rc8.bottom);
	SetDCPenColor(hdc, RGB(0, 0, 255));
	Rectangle(hdc, rc9.left, rc9.top, rc9.right, rc9.bottom);

	// Draw the text into the center of each of the rectangles.
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(0, 0, 0));   // black
	// TODO: Optionally, set a nicer font than the default.
	DrawText(hdc, TEXT("Oradea"), -1, &rc1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	DrawText(hdc, TEXT("Iasi"), -1, &rc2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Timisoara"), -1, &rc3, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Sibiu"), -1, &rc4, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Galati"), -1, &rc5, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Drobeta"), -1, &rc6, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Craiova"), -1, &rc7, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Bucuresti"), -1, &rc8, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(hdc, TEXT("Constanta"), -1, &rc9, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	*/
	// Clean up after ourselves.
	SelectObject(hdc, hpenOld);
	SelectObject(hdc, hbrushOld);

	EndPaint(hWnd, &ps);
	break; }
	
	case WM_DESTROY:
	PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
		return 0;
	}
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
