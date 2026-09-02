// 2026_second_winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2026_second_winapi.h"
#include <string>
#include <ctime>
using std::wstring;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
UINT WINDOW_WIDTH = 1280;
UINT WINDOW_HEIGHT = 720;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2026SECONDWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2026SECONDWINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2026SECONDWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2026SECONDWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT windowRt = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   AdjustWindowRect(&windowRt, WS_OVERLAPPEDWINDOW, true);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, 0, windowRt.right - windowRt.left,
                             windowRt.bottom - windowRt.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT clientRt;

    switch (message)
    {
        case WM_CREATE:
            srand((unsigned int)time(nullptr));
            GetClientRect(hWnd, &clientRt);
            break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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

            HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
            SelectObject(hdc, pen);
            HBRUSH;

            Rectangle(hdc, 300, 200, 400, 300);
            DeleteObject(pen);
            Rectangle(hdc, 500, 500, 600, 600);

            //Rectangle(hdc, 50, 50, 300, 300);

            //wstring wstr = L"PLAYER";
            //RECT rt = { 300, 200, 400, 300 };
            //DrawText(hdc, wstr.c_str(), wstr.length(), &rt
            //         , DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            //POINT points[3] = { {410, 245}, {410, 255}, {420, 250} };
            //Polygon(hdc, points, 3);

            // 특수 도형
            //POINT points[3] = { {150, 50}, {100, 150}, {200, 150} };
            ////POINT points[5] = { {150, 50}, {100, 150}, {200, 150} };
            //Polygon(hdc, points, 3);
            //RoundRect(hdc, 100, 100, 200, 200, 20, 20);

            //SetArcDirection(hdc, AD_CLOCKWISE);
            //Pie(hdc, 100, 100, 300, 300,
            //    300, 200, 200, 100);
            //RECT rt = { 500, 500, 600, 600 };
            //InvertRect(hdc, &rt);

            //for (int i = 0; i < 25; ++i)
            //{
            //    int left = 100 + 70 * (i % 5);
            //    int top = 100 + (70 * (int)(i / 5));
            //    if (i / 5 % 2 == 0)
            //        Rectangle(hdc, left, top, left + 50, top + 50);
            //    else
            //        Ellipse(hdc, left, top, left + 50, top + 50);
            //}

            //for (int i = 0; i < 1000; ++i)
            //    SetPixel(hdc, rand() % 100, rand() % 100, RGB(0, 255, 0));
            //MoveToEx(hdc, 150, 150, nullptr);
            //LineTo(hdc, 300, 150);

            //for (int i = 0; i < 10; ++i)
            //{
            //    MoveToEx(hdc, 0, i * WINDOW_HEIGHT / 9, nullptr);
            //    LineTo(hdc, WINDOW_WIDTH, i * WINDOW_HEIGHT / 9);
            //}

            //for (int i = 0; i < 17; ++i)
            //{
            //    MoveToEx(hdc, i * WINDOW_WIDTH / 16, 0, nullptr);
            //    LineTo(hdc, i * WINDOW_WIDTH / 16, WINDOW_HEIGHT);
            //}

            
            //// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            //// 텍스트 출력
            ////LPCWSTR;
            //wstring wstr = L"2-2 2학기 겜프 찐 시작 아ㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏ";
            //TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());

            //// 2번째 텍스트 출력
            ////LPRECT;
            //Rectangle(hdc, 50, 50, 300, 300);

            //RECT rt = { 50, 50, 300, 300 };
            //RECT tempRt = { 0, 0, rt.right - rt.left, 0 };
            //DrawText(hdc, wstr.c_str(), wstr.length(), &tempRt,
            //         DT_CENTER | DT_CALCRECT | DT_WORDBREAK);
            //int textHeight = tempRt.bottom - tempRt.top;
            //int boxHeight = rt.bottom - rt.top;

            //int topOffset = (boxHeight - textHeight) / 2;
            //RECT renderRt = { rt.left, rt.top + topOffset,
            //                    rt.right, rt.top + topOffset + textHeight };

            //DrawText(hdc, wstr.c_str(), wstr.length(), &renderRt
            //         , DT_CENTER | DT_WORDBREAK);
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

// 정보 대화 상자의 메시지 처리기입니다.
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
