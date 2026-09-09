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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static WCHAR wArr[100];
    static UINT cnt = 0;
    static UINT yPos = 0;

    static UINT colorIdx = 0;
    auto curColor = [](int idx){
        switch (idx % 3)
        {
            case 0: return RGB(255, 0, 0);
            case 1: return RGB(0, 0, 255);
            case 2: return RGB(0, 255, 0);
        }
    };
    static bool isFontAdded = false;
    static HFONT font = nullptr;
    static HFONT testFont = nullptr;
    static UINT defaultSize = 30;
    switch (message)
    {
        //case WM_KEYDOWN:
        //{
        //    int a = 0;
        //}
        //break;
        case WM_CREATE:
        {
            srand((unsigned int)time(nullptr));
            // 폰트 설치 -> 제거
            // 폰트 생성 -> 잡기
            if (AddFontResourceEx(L"나눔손글씨 암스테르담.ttf", FR_PRIVATE, 0) > 0)
                isFontAdded = true;
            font = CreateFont(
                0, 0, 0, 0,
                FW_NORMAL, false, false, false,
                HANGEUL_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"나눔손글씨 암스테르담"
            );

            testFont = CreateFont(
                defaultSize, 0, 0, 0,
                FW_NORMAL, false, false, false,
                HANGEUL_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"맑은 고딕"
            );
        }
        break;
        case WM_KEYDOWN:
        {
            int plusSize = 0;
            bool isBold = false;

            switch (wParam)
            {
                case VK_UP:
                {
                    plusSize = 2;
                }
                break;
                case VK_DOWN:
                {
                    plusSize = -2;
                }
                break;
                case 'B':
                {
                    if (isBold)
                    {
                        isBold = false;
                    }
                    else
                    {
                        isBold = true;
                    }
                }
                case 'b':
                {
                    isBold = isBold ? false : true;
                }
                break;
            }
            defaultSize += plusSize;
            testFont = CreateFont(
                defaultSize, 0, 0, 0,
                isBold ? FW_BOLD : FW_NORMAL, false, false, false,
                HANGEUL_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"맑은 고딕"
            );
        }
        case WM_CHAR:
        {
            HDC hdc = GetDC(hWnd);
            //wstring str = L"2-2반 이제 진짜 시작";
            //TextOut(hdc, 10, 10, str.c_str(), str.length());
            if (wParam == VK_BACK && cnt > 0)
            {
                cnt--;
            }
            else if (wParam == VK_SPACE && cnt > 0)
                cnt = 0;
            //else if (wParam == VK_RETURN)
            //{
            //    cnt = 0;
            //    yPos += 20;
            //}
            else
                wArr[cnt++] = wParam;
            wArr[cnt] = '\0';
            //colorIdx++;
            InvalidateRect(hWnd, nullptr, true);
            //TextOut(hdc, 10, 10, wArr, wcslen(wArr));
            //ReleaseDC(hWnd, hdc);
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HFONT def = (HFONT)SelectObject(hdc, testFont);
            //TextOut(hdc, 10, yPos, wArr, wcslen(wArr));
            //SetTextColor(hdc, curColor(colorIdx));
            RECT rt = { 200, 300, 300, 400};
            Rectangle(hdc, 200, 300, 300, 400);
            TextOut(hdc, 200, 100, L"Font Text (Up/Down/B Key)", wcslen(L"Font Text (Up/Down/B Key)"));
            DrawText(hdc, L"START", wcslen(L"START"), &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdc, def);
            DeleteObject(testFont);
            //HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            //HBRUSH bodyBrush = CreateSolidBrush(RGB(50, 50, 50));
            //HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            //HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));

            //HPEN defaultPen = (HPEN)SelectObject(hdc, pen);

            //HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, bodyBrush);
            //Rectangle(hdc, 100, 50, 250, 350);

            //SelectObject(hdc, redBrush);
            //Ellipse(hdc, 125, 75, 225, 175);

            //SelectObject(hdc, greenBrush);
            //Ellipse(hdc, 125, 75 + 150, 225, 175 + 150);

            //SelectObject(hdc, defaultPen);
            //SelectObject(hdc, defaultBrush);
            //DeleteObject(pen);
            //DeleteObject(bodyBrush);
            //DeleteObject(redBrush);
            //DeleteObject(greenBrush);

            EndPaint(hWnd, &ps);
        }
        break;
        case WM_DESTROY:
        {
            if (font != nullptr)
            {
                DeleteObject(font);
            }
            if (isFontAdded)
                RemoveFontResourceEx(L"나눔손글씨 암스테르담.ttf", FR_PRIVATE, 0);
            PostQuitMessage(0);
        }
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
