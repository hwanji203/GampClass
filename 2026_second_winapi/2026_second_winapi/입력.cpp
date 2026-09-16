// 2026_second_winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2026_second_winapi.h"
#include <string>
#include <ctime>
#include <vector>
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

//// 연습문제 9-4
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
//bool InCircle(POINT mousePos, POINT pos, int radius)
//{
//    int dx = pos.x - mousePos.x;
//    int dy = pos.y - mousePos.y;
//    return dx * dx + dy * dy < radius * radius;
//}
//// 마우스 
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    // 원을 클릭하면 뒤에 사각형  아웃라인
//    static POINT objPos = { 100,100 };
//    static POINT objSize = { 200,200 };
//    static bool isClick = false;
//    static POINT mousePos;
//    switch (message)
//    {
//    case WM_MOUSEMOVE:
//        if (isClick)
//        {
//            mousePos = { LOWORD(lParam), HIWORD(lParam) };
//            objPos = mousePos;
//            InvalidateRect(hWnd, nullptr, true);
//        }
//        break;
//    case WM_LBUTTONDOWN:
//    {
//        mousePos = {LOWORD(lParam), HIWORD(lParam)};
//        if(InCircle(mousePos, objPos, objSize.x / 2))
//            isClick = true;
//        InvalidateRect(hWnd, nullptr, true);
//    }
//    break;
//    case WM_LBUTTONUP:
//    {
//        isClick = false;
//        InvalidateRect(hWnd, nullptr, true);
//    }
//        break;
//
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        if (isClick)
//            Rectangle(hdc
//                , objPos.x - objSize.x / 2
//                , objPos.y - objSize.y / 2
//                , objPos.x + objSize.x / 2
//                , objPos.y + objSize.y / 2
//            );
//        Ellipse(hdc
//            , objPos.x - objSize.x / 2
//            , objPos.y - objSize.y / 2
//            , objPos.x + objSize.x / 2
//            , objPos.y + objSize.y / 2
//        );
//
//        EndPaint(hWnd, &ps);
//    }
//    break;
//
//
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

//// 연습문제 10-1
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static std::vector<POINT> vecCircles;
//    switch (message)
//    {
//    case WM_LBUTTONDOWN:
//    {
//        vecCircles.push_back({LOWORD(lParam), HIWORD(lParam)});
//        InvalidateRect(hWnd, nullptr, true);
//    }
//        break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        for (const auto& pt : vecCircles)
//            Ellipse(hdc, pt.x - 10, pt.y - 10,
//                        pt.x + 10, pt.y + 10);
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
struct Object
{
    POINT pos;
    POINT size;
};
// 연습문제 10-2
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static std::vector<Object> vecObjs;
    static bool isClick = false;
    static POINT startPos;
    static POINT endPos;
    switch (message)
    {
        case WM_LBUTTONDOWN:
        {
            isClick = true;
            startPos = { LOWORD(lParam), HIWORD(lParam) };
            endPos = startPos;
        }
        break;
        case WM_MOUSEMOVE:
            if (isClick)
            {
                endPos = { LOWORD(lParam), HIWORD(lParam) };
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
        case WM_LBUTTONUP:
        {
            isClick = false;
            Object obj;
            obj.pos = { {(startPos.x + endPos.x) / 2} ,{(startPos.y + endPos.y) / 2} };
            obj.size = { {abs(endPos.x - startPos.x)},{abs(endPos.y - startPos.y)} };
            vecObjs.push_back(obj);
            InvalidateRect(hWnd, nullptr, true);
        }
        break;
        case WM_MOUSEWHEEL:
        {
            short delta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (!vecObjs.empty())
            {
                auto& lastObj = vecObjs.back();
                if (delta > 0)
                {
                    lastObj.size.x += 10;
                    lastObj.size.y += 10;
                }
                else
                {
                    lastObj.size.x = std::max(10, (int)lastObj.size.x - 10);
                    lastObj.size.y = std::max(10, (int)lastObj.size.y - 10);
                }
                InvalidateRect(hWnd, nullptr, true);
            }

        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            for (const auto& obj : vecObjs)
            {
                Rectangle(hdc
                          , obj.pos.x - obj.size.x / 2
                          , obj.pos.y - obj.size.y / 2
                          , obj.pos.x + obj.size.x / 2
                          , obj.pos.y + obj.size.y / 2
                );
            }
            if (isClick)
            {
                Rectangle(hdc, startPos.x, startPos.y,
                          endPos.x, endPos.y);
            }

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
