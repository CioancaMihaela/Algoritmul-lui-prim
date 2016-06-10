
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
int vect[50];
int arbore[9][2];
int count;
int b[10][10];
int res[10];
LPCWSTR *result[10];
HWND IDC_HR40, IDC_BUC, IDC_OR, IDC_CR, IDC_DR, IDC_GL, IDC_IS, IDC_HR3, IDC_SB, IDC_CT, IDC_TM;
HWND IDC_HR1, IDC_HR2, IDC_HR5, IDC_HR4, IDC_HR6, IDC_HR7, IDC_HR8, IDC_HR9, IDC_HR10, IDC_HR11;
HWND IDC_HR12, IDC_HR13, IDC_HR14, IDC_HR15, IDC_HR16, IDC_HR17, IDC_HR18, IDC_HR19, IDC_HR20;
HWND IDC_BUT;

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
	wcex.hbrBackground = CreateSolidBrush(0x0099CC99);
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




//



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
  
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, 850,600, NULL, NULL, hInstance, NULL);

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
	sters[*j_min] = 1;
	marcat[*i_min] = 1;
	for (i = *i_min; i < n; i++)
	{
		for (j = *j_min; j < n; j++)
		{
			if (sters[j] == 0 && marcat[i] == 1)
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{


	case WM_CREATE:
		//Creaza orasele
	{

					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  600, 100, 200, 25, hWnd, (HMENU)IDC_HR1, GetModuleHandle(NULL), NULL);

					  IDC_HR40 = CreateWindowEx(NULL, L"BUTTON", L"Alegeti orasele", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  300, 20, 300, 30, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_OR = CreateWindowEx(NULL, L"BUTTON", L"Oradea", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  350, 100, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_TM = CreateWindowEx(NULL, L"BUTTON", L"Timisoara", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  350, 200, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_DR = CreateWindowEx(NULL, L"BUTTON", L"Drobeta", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  200, 100, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_CR = CreateWindowEx(NULL, L"BUTTON", L"Craiova", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  50, 200, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_BUC = CreateWindowEx(NULL, L"BUTTON", L"Bucuresti", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  50, 100, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_SB = CreateWindowEx(NULL, L"BUTTON", L"Sibiu", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  350, 150, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_IS = CreateWindowEx(NULL, L"BUTTON", L"Iasi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  200, 200, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_CT = CreateWindowEx(NULL, L"BUTTON", L"Constanta", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  50, 150, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_GL = CreateWindowEx(NULL, L"BUTTON", L"Galati", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  200, 150, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
					  IDC_HR3 = CreateWindowEx(NULL, L"BUTTON", L"Gata", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  660, 150, 85, 25, hWnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);





					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  50, 300, 100, 25, hWnd, (HMENU)IDC_HR2, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  300, 300, 100, 25, hWnd, (HMENU)IDC_HR4, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  550, 300, 100, 25, hWnd, (HMENU)IDC_HR5, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  200, 300, 50, 25, hWnd, (HMENU)IDC_HR12, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  450, 300, 50, 25, hWnd, (HMENU)IDC_HR13, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  700, 300, 50, 25, hWnd, (HMENU)IDC_HR14, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  50, 400, 100, 25, hWnd, (HMENU)IDC_HR6, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  300, 400, 100, 25, hWnd, (HMENU)IDC_HR7, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  550, 400, 100, 25, hWnd, (HMENU)IDC_HR8, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  200, 400, 50, 25, hWnd, (HMENU)IDC_HR15, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  450, 400, 50, 25, hWnd, (HMENU)IDC_HR16, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  700, 400, 50, 25, hWnd, (HMENU)IDC_HR17, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  50, 500, 100, 25, hWnd, (HMENU)IDC_HR9, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  300, 500, 100, 25, hWnd, (HMENU)IDC_HR10, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  550, 500, 100, 25, hWnd, (HMENU)IDC_HR11, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  200, 500, 50, 25, hWnd, (HMENU)IDC_HR18, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  450, 500, 50, 25, hWnd, (HMENU)IDC_HR19, GetModuleHandle(NULL), NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
						  WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
						  700, 500, 50, 25, hWnd, (HMENU)IDC_HR20, GetModuleHandle(NULL), NULL);
					  break;
	}

	case WM_COMMAND:
	{
					   switch (HIWORD(wParam))
					   {
					   case BN_CLICKED:
					   {
										  
										  if ((HWND)lParam == IDC_BUC)
										  {
											  SetDlgItemText(hWnd,int(IDC_HR1), TEXT("Bucuresti"));
											  op = BUC;
											  res[0] = 1;
										  }
										  if ((HWND)lParam == IDC_OR)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Oradea"));
											  op = OR;
											  res[6] = 1;

										  }
										  if ((HWND)lParam == IDC_CR)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Craiova"));
											  op = CR;
											  res[2] = 1;
										  }
										  if ((HWND)lParam == IDC_DR)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Drobeta"));
											  op = DR;
											  res[3] = 1;
										  }
										  if ((HWND)lParam == IDC_GL)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Galati"));
											  op = GL;
											  res[4] = 1;
										  }
										  if ((HWND)lParam == IDC_CT)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Constanta"));
											  op = CT;
											  res[1] = 1;
										  }
										  if ((HWND)lParam == IDC_IS)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Iasi"));
											  op = IS;
											  res[5] = 1;
										  }
										  if ((HWND)lParam == IDC_SB)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Sibiu"));
											  op = SB;
											  res[7] = 1;
										  }
										  if ((HWND)lParam == IDC_TM)
										  {
											  SetDlgItemText(hWnd, int(IDC_HR1), TEXT("Timisoara"));
											  op = TM;
											  res[8] = 1;
										  }
										  if ((HWND)lParam == IDC_HR3)
										  {
											  char*q[9] = { "Bucuresti", "Constanta", "Craiova", "Drobeta", "Galati", "Iasi", "Oradea", "Sibiu", "Timisoara" };



											 /* int it = 0;
											  for (int i = 0; i < 9; i++)
											  {
												  if (res[i] >0)
												  {
													  n++;

													  vect[it] = i;
													  it++;
												  }
											  }
											  int aux;
											  for (int i = 0; i < n; i++)
											  {
												  for (int j = i + 1; j < n; j++)
												  {
													  if (vect[j] < vect[i])
													  {
														  aux = vect[i];
														  vect[i] = vect[j];
														  vect[j] = aux;

													  }
												  }
											  }*/ 


											  FILE*f;

											  int vect[9] = { 1,2,3,0,0,0,0,0,0 };

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



											  for (int i = 0; i < n; i++)
											  {
												  for (int j = 0; j < n; j++)
												  {
													  if (sters[j] != 1 && marcat[i] != 1)
													  {

														  i_min = i;
														  j_min = j;
														  alege(&min, &i_min, &j_min);

														  arbore[count][0] = i_min;
														  arbore[count][1] = j_min;
														  count++;
													  }
												  }
											  }
											 
											  SetDlgItemText(hWnd,int(IDC_HR2), TEXT("Aa"));

											  SetDlgItemText(hWnd, int(IDC_HR4),  convertCharArrayToLPCWSTR(q[vect[arbore[1][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR5),  convertCharArrayToLPCWSTR(q[vect[arbore[2][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR6), convertCharArrayToLPCWSTR(q[vect[arbore[3][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR7), convertCharArrayToLPCWSTR(q[vect[arbore[4][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR8), convertCharArrayToLPCWSTR(q[vect[arbore[5][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR9), convertCharArrayToLPCWSTR(q[vect[arbore[6][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR10), convertCharArrayToLPCWSTR(q[vect[arbore[7][0]]] - 1));

											  SetDlgItemText(hWnd, int(IDC_HR11), convertCharArrayToLPCWSTR(q[vect[arbore[8][0]]] - 1));
											  SetDlgItemInt(hWnd, int(IDC_HR12), vect[1], true);
											  SetDlgItemInt(hWnd, int(IDC_HR13), res[7], true);
											  SetDlgItemInt(hWnd, int(IDC_HR14), vect[arbore[0][0]], true);
											  SetDlgItemInt(hWnd, int(IDC_HR15), a[vect[3]][vect[4]], true);
											  SetDlgItemInt(hWnd, int(IDC_HR16), a[vect[4]][vect[5]], true);
											  SetDlgItemInt(hWnd, int(IDC_HR17), a[vect[5]][vect[6]], true);
											  SetDlgItemInt(hWnd, int(IDC_HR18), a[vect[6]][vect[7]], true);
											  SetDlgItemInt(hWnd, int(IDC_HR19), a[vect[7]][vect[8]], true);
											  //SetDlgItemInt(hWnd, int(IDC_HR20), a[vect[8]][vect[9]], true);


											  break;

										  }break;
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
			break;
	}
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
