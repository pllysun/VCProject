#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include<ctime>
//#define   VK_W	0x57 
//#define   VK_D	0x44 
//#define   VK_A	0x41
//#define   VK_S	0x53
//
//#define   VK_a	0x61 
//#define   VK_s	0x73 
//#define   VK_d	0x64
//#define   VK_w	0x77
static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

int L = 100;
int T = 100;
int R = 120;
int B = 120;
HINSTANCE hInst;
int  dir = 3;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,_T("Call to RegisterClassEx failed!"),_T("Windows Desktop Guided Tour"),NULL);
        return 1;
    }

    hInst = hInstance;


    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 650, 655, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);
  
    SetTimer(hWnd, 1, 100, NULL);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
int Food[5];
bool Judge = true;
void food(HDC hdc,HBRUSH hb)
{
    if (Judge) {
            srand((unsigned)time(NULL));
            Food[0]= rand() % 610 + 20;
            Food[1]= rand() % 600 + 20;
            Food[2]= Food[0]+20;
            Food[3] = Food[1] + 20;
        Judge = false;
    }
    
    hb = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, hb);
    Ellipse(hdc, Food[0], Food[1], Food[2], Food[3]);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HPEN hp;
    HBRUSH hb;
    TCHAR greeting[] = _T("Hello, Windows desktop!");
    RECT rc;
    rc.left = L;
    rc.top = T;
    rc.right = R;
    rc.bottom = B;
    RECT A1;
    switch (message)
    {
    case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
            dir = 1;
			break;
		case VK_RIGHT:
            dir = 2;
			break;
		case VK_DOWN:
            dir = 3;
			break;
		case VK_LEFT:
            dir = 4;
			break;
		}
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        //hb = CreateSolidBrush(RGB(255,0,0));
       // FillRect(hdc, &rc, hb);*/
        hb = CreateSolidBrush(RGB(175, 238, 238));
        SelectObject(hdc, hb);
        Rectangle(hdc, 20, 20, 610, 600);
        hb = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hb);
        Rectangle(hdc, L, T, R, B);
        food(hdc, hb);
      /*  for (int i = 0; i <= 640; i += 20) {
            Rectangle(hdc, i, 0, i + 15, 20);
            Rectangle(hdc, i, 600, i + 15, 620);
        }
        for (int i = 0; i <= 640; i += 20)
        {
            Rectangle(hdc, 0, i, 20, i + 15);
            Rectangle(hdc, 620, i, 640, i + 15);
        }*/
        EndPaint(hWnd, &ps);
        break;
    case WM_TIMER:
        if (dir == 1){
            T -=20;
            B -=20;
        }
        else if (dir == 2) {
            L +=20;
            R +=20;
        }
        else if (dir == 3) {
            T +=20;
            B +=20;
        }
        else if (dir == 4) {
            L -=20;
            R -=20 ;
        }
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_CREATE:
        hdc = GetDC(hWnd);
    
        ReleaseDC(hWnd,hdc);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

