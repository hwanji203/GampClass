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
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2026SECONDWINAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2026SECONDWINAPI);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
// 연습문제 9-4

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT objPos = { 300, 300 };
    static POINT objSize = { 50, 50 };
    static float playerYVec = 0;
    static float gravity = -9.8f;
    static int jumpPower = 10;
    static int delta = 100;
    static bool isGrounded = true;
    switch (message)
    {
        case WM_CREATE:
            SetTimer(hWnd, 1, 10, nullptr);
            break;
        case WM_TIMER:
            if (objPos.y >= 300 && playerYVec < 0)
            {
                objPos.y = 300;
                isGrounded = true;
                playerYVec = 0;
            }

            if (true)
            {
                playerYVec -= gravity / delta;
                objPos.y += playerYVec;
            }

            InvalidateRect(hWnd, nullptr, true);
            break;
        case WM_LBUTTONDOWN:
        {
            playerYVec = 100;
            //int x = LOWORD(lParam);
            //int y = HIWORD(lParam);
            //isVisible = false;
            //int ax = objPos.x - x;
            //int ay = objPos.y - y;
            //if (ax * ax + ay * ay < 100 * 100)
            //{
            //    isVisible = true;
            //    objPos = { x, y };
            //}
            //InvalidateRect(hWnd, nullptr, true);
        }
        break;
        case WM_LBUTTONUP:
            //isVisible = false;
            //InvalidateRect(hWnd, nullptr, true);
            break;
        case WM_MOUSEMOVE:
        {
            //int x = LOWORD(lParam);
            //int y = HIWORD(lParam);

            //if (isVisible)
            //    objPos = { x, y };

            //InvalidateRect(hWnd, nullptr, true);
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            //if (isVisible)
            //    Rectangle(hdc
            //              , objPos.x - objSize.x / 2
            //              , objPos.y - objSize.y / 2
            //              , objPos.x + objSize.x / 2
            //              , objPos.y + objSize.y / 2
            //    );

            Ellipse(hdc
                    , objPos.x - objSize.x / 2
                    , objPos.y - objSize.y / 2
                    , objPos.x + objSize.x / 2
                    , objPos.y + objSize.y / 2
            );

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
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static POINT objPos = { 100,100 };
//    static POINT objSize = { 50,50 };
//    static int speed = 5;
//    static RECT rt = { 0,0,300, 300 };
//    static bool isVisible = true;
//    switch (message)
//    {
//    case WM_CREATE:
//        SetTimer(hWnd, 1, 500, nullptr);
//        break;
//    case WM_TIMER:
//        objPos.x += speed;
//        if (objPos.x - objSize.x / 2 <= 0 ||
//            objPos.x + objSize.x / 2 >= rt.right)
//        {
//            speed = -speed;
//        }
//        isVisible = !isVisible;
//        InvalidateRect(hWnd, nullptr, true);
//        break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        Rectangle(hdc
//            , objPos.x - objSize.x / 2
//            , objPos.y - objSize.y / 2
//            , objPos.x + objSize.x / 2
//            , objPos.y + objSize.y / 2
//        );
//        if (isVisible)
//        {
//            wstring str = L"PLAYER";
//
//            TextOut(hdc, objPos.x - objSize.x / 2
//                , objPos.y - objSize.y / 2 - 20,
//                str.c_str(), str.length());
//        }
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

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
