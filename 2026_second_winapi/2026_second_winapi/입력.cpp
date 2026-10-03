// 2026_second_winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define NOMINMAX

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

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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

struct Object
{
    POINT pos;
    POINT size;
};

RECT GetRect(const Object& obj)
{
    RECT rt =
    {
        obj.pos.x - obj.size.x / 2,
        obj.pos.y - obj.size.y / 2,
        obj.pos.x + obj.size.x / 2,
        obj.pos.y + obj.size.y / 2
    };
    return rt;
}
void DrawColoredRect(HDC hdc, const RECT& rect, COLORREF penColor, COLORREF brushColor, bool filled)
{
    HPEN pen = CreatePen(PS_SOLID, 1, penColor);
    HBRUSH brush = filled ? CreateSolidBrush(brushColor) : (HBRUSH)GetStockObject(WHITE_BRUSH);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    if (filled)
        DeleteObject(brush);
}
void DrawCenteredText(HDC hdc, RECT rect, const wstring& text)
{
    SetBkMode(hdc, TRANSPARENT);
    DrawText(hdc, text.c_str(), text.length(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Object player = { { 100, 500 } ,{ 50, 50 } };
    static COLORREF playerColor = RGB(255, 255, 255);
    static int   nextIndex = 0;
    static bool  isOnTrap = false;
    static RECT  clientRect = { 0 };
    const int STEP = 50;

    static const RECT        zoneRect[3] = { {200,100,350,250}, {500,100,650,250}, {800,100,950,250} };
    static const COLORREF    zoneColor[3] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255) };
    static const std::wstring zoneLabel[3] = { L"1", L"2", L"3" };

    static const RECT        trapRect = { 500,400,650,550 };
    static const COLORREF    trapColor = RGB(128, 128, 128);
    static const std::wstring trapLabel = L"Trap";

    switch (message)
    {
        case WM_CREATE:
            GetClientRect(hWnd, &clientRect);
            break;
        case WM_KEYDOWN:
        {
            if (nextIndex >= 3)
                break;
            POINT next = player.pos;
            switch (wParam)
            {
                case VK_LEFT: next.x -= STEP; break;
                case VK_RIGHT: next.x += STEP; break;
                case VK_UP: next.y -= STEP; break;
                case VK_DOWN: next.y += STEP; break;
            }
            const int size = player.size.x / 2;
            bool isOut =
                ((next.x - size) < clientRect.left) ||
                ((next.x + size) > clientRect.right) ||
                ((next.y - size) < clientRect.top) ||
                ((next.y + size) > clientRect.bottom);

            if (isOut)
                break;

            player.pos = next;

            playerColor = RGB(255, 255, 255);

            RECT playerRt = GetRect(player);
            RECT tempRt;
            for (int i = 0; i < 3; ++i)
            {
                if (!IntersectRect(&tempRt, &playerRt, &zoneRect[i]))
                    continue;
                playerColor = zoneColor[i];
                if (i == nextIndex)
                    nextIndex++;
                else if (i > nextIndex)
                    nextIndex = 0;
            }
            isOnTrap = IntersectRect(&tempRt, &playerRt, &trapRect);
            if (isOnTrap)
            {
                playerColor = trapColor;
                nextIndex = 0;
            }
            InvalidateRect(hWnd, nullptr, true);
        }
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT playerRect = GetRect(player);
            for (int i = 0; i < 3; ++i)
            {
                bool visited = (i < nextIndex);
                DrawColoredRect(hdc, zoneRect[i], zoneColor[i], zoneColor[i], visited);
                if (visited)
                    DrawCenteredText(hdc, zoneRect[i], zoneLabel[i]);
            }
            // trap
            DrawColoredRect(hdc, trapRect, trapColor, trapColor, isOnTrap);
            DrawCenteredText(hdc, trapRect, trapLabel);

            DrawColoredRect(hdc, playerRect, RGB(0, 0, 0), playerColor, true);

            if (nextIndex >= 3)
            {
                TextOut(hdc, 550, 50, L"CLEAR", 5);
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

//struct Object
//{
//    POINT pos;
//    POINT size;
//};
//
//RECT GetRect(const Object& obj)
//{
//    RECT rt =
//    {
//        obj.pos.x - obj.size.x / 2,
//        obj.pos.y - obj.size.y / 2,
//        obj.pos.x + obj.size.x / 2,
//        obj.pos.y + obj.size.y / 2
//    };
//    return rt;
//}
//
//struct ColorBox
//{
//    COLORREF color;
//    RECT box;
//};
//
//void OnEnter(ColorBox box, int& curStep)
//{
//    if (curStep == 0 && box.color == RGB(255, 0, 0))
//        curStep++;
//    else if (curStep == 1 && box.color == RGB(0, 255, 0))
//        curStep++;
//    else if (curStep == 2 && box.color == RGB(0, 0, 255))
//        curStep++;
//    else
//        curStep = 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static Object player = { {100, 500}, {50, 50} };
//    static ColorBox red = { RGB(255, 0, 0), {200, 100, 350, 250} };
//    static ColorBox green = { RGB(0, 255, 0), {500, 100, 650, 250} };
//    static ColorBox blue = { RGB(0, 0, 255), {800, 100, 950, 250} };
//    static ColorBox trap = { RGB(128, 128, 128), {500, 400, 650, 550} };
//    static std::vector<ColorBox> boxs = { red, green, blue, trap };
//    static int speed = 50;
//    static int step = 0;
//    switch (message)
//    {
//        case WM_KEYDOWN:
//        {
//            POINT prevPos = player.pos;
//            switch (wParam)
//            {
//                case VK_RIGHT:
//                    player.pos.x += speed;
//                    break;
//                case VK_LEFT:
//                    player.pos.x -= speed;
//                    break;
//                case VK_UP:
//                    player.pos.y -= speed;
//                    break;
//                case VK_DOWN:
//                    player.pos.y += speed;
//                    break;
//            }
//            if (WINDOW_WIDTH < player.pos.x || 0 > player.pos.x ||
//                WINDOW_HEIGHT < player.pos.y || 0 > player.pos.y)
//                player.pos = prevPos;
//
//            RECT playerRt = GetRect(player);
//            RECT tempRt = {};
//
//            int idx = 0;
//            for (auto& box : boxs)
//            {
//                if (idx++ < step)
//                    continue;
//                if (IntersectRect(&tempRt, &playerRt, &box.box))
//                    OnEnter(box, step);
//            }
//
//            InvalidateRect(hWnd, nullptr, true);
//        }
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            SetBkMode(hdc, 0);
//            int idx = 1;
//            for (auto& box : boxs)
//            {
//                HPEN p = CreatePen(PS_SOLID, 1, box.color);
//                HPEN oldP = (HPEN)SelectObject(hdc, p);
//
//                if (idx <= step)
//                {
//                    HBRUSH b = CreateSolidBrush(box.color);
//                    HBRUSH olbB = (HBRUSH)SelectObject(hdc, b);
//                    Rectangle(hdc, box.box.left, box.box.top, box.box.right, box.box.bottom);
//                    SelectObject(hdc, olbB);
//                    DeleteObject(b);
//
//                    DrawText(hdc, std::to_wstring(idx).c_str(), 1, &box.box
//                             , DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//                }
//                else
//                {
//                    Rectangle(hdc, box.box.left, box.box.top, box.box.right, box.box.bottom);
//                }
//                SelectObject(hdc, oldP);
//                DeleteObject(p);
//                idx++;
//            }
//            wstring s = L"Trap";
//            DrawText(hdc, s.c_str(), s.size(), &trap.box
//                     , DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//
//            for (auto& box : boxs)
//            {
//                RECT playerRt = GetRect(player);
//                RECT tempRt = {};
//
//                if (IntersectRect(&tempRt, &playerRt, &box.box))
//                {
//                    HBRUSH b = CreateSolidBrush(box.color);
//                    HBRUSH olbB = (HBRUSH)SelectObject(hdc, b);
//
//                    Rectangle(hdc
//                              , player.pos.x - player.size.x / 2
//                              , player.pos.y - player.size.y / 2
//                              , player.pos.x + player.size.x / 2
//                              , player.pos.y + player.size.y / 2
//                    );
//
//                    SelectObject(hdc, olbB);
//                    DeleteObject(b);
//                }
//                else
//                {
//                    Rectangle(hdc
//                              , player.pos.x - player.size.x / 2
//                              , player.pos.y - player.size.y / 2
//                              , player.pos.x + player.size.x / 2
//                              , player.pos.y + player.size.y / 2
//                    );
//                }
//            }
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}


//struct Bomb
//{
//    POINT pos;
//    int radius;
//    int count;
//    bool isBoom;
//};
//struct Box
//{
//    POINT pos;
//    POINT size;
//};
//
//RECT GetRect(const Box& obj)
//{
//    RECT rt =
//    {
//        obj.pos.x - obj.size.x / 2,
//        obj.pos.y - obj.size.y / 2,
//        obj.pos.x + obj.size.x / 2,
//        obj.pos.y + obj.size.y / 2
//    };
//    return rt;
//}
//
//// 종합연습문제 2
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static std::vector<Bomb> vecBombs;
//    static int bombCount = 0;
//    static Box gaugeBox = { {350,525},{500,50} };
//    switch (message)
//    {
//        case WM_CREATE:
//        {
//            SetTimer(hWnd, 1, 1000, nullptr);
//        }
//        break;
//        case WM_LBUTTONDOWN:
//        {
//            Bomb bomb;
//            bomb.pos = { LOWORD(lParam),HIWORD(lParam) };
//            bomb.count = 5;
//            bomb.radius = 30;
//            bomb.isBoom = false;
//            vecBombs.push_back(bomb);
//            InvalidateRect(hWnd, nullptr, true);
//        }
//        break;
//        case WM_TIMER:
//        {
//            std::vector<Bomb>::iterator iter = vecBombs.begin();
//            for (; iter != vecBombs.end(); ++iter)
//            {
//                if (iter->isBoom == false)
//                {
//                    iter->count--;
//                    iter->radius -= 5;
//                    if (iter->count <= 0)
//                    {
//                        iter->isBoom = true;
//                        bombCount++;
//                    }
//                }
//            }
//
//            if (bombCount >= 5)
//            {
//                KillTimer(hWnd, 1);
//                PostQuitMessage(0);
//            }
//
//            InvalidateRect(hWnd, nullptr, true);
//        }
//        break;
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // 폭탄 - 원
//            std::vector<Bomb>::iterator iter = vecBombs.begin();
//            for (; iter != vecBombs.end(); ++iter)
//            {
//                int x = iter->pos.x;
//                int y = iter->pos.y;
//                int radius = iter->radius;
//                Ellipse(hdc, x - radius, y - radius,
//                        x + radius, y + radius);
//                // 글씨 
//                std::wstring text = iter->isBoom ?
//                    L"BOOM!" : std::to_wstring(iter->count);
//                RECT rt = { x - 30, y - 30, x + 30, y + 30 };
//                DrawText(hdc, text.c_str(), text.length(), &rt
//                         , DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//            }
//
//            // 게이지바 - 사각형
//            RECT gaugeRt = GetRect(gaugeBox);
//            Rectangle(hdc, gaugeRt.left, gaugeRt.top,
//                      gaugeRt.right, gaugeRt.bottom);
//
//            int gaugeWidth = gaugeRt.right - gaugeRt.left;
//            int fillWidth = gaugeWidth * (bombCount * 20) / 100;
//
//            RECT fillRt =
//            {
//                gaugeRt.left,
//                gaugeRt.top,
//                gaugeRt.left + fillWidth,
//                gaugeRt.bottom
//            };
//            HBRUSH brush = CreateSolidBrush(RGB(255, 100, 0));
//            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//
//            Rectangle(hdc, fillRt.left, fillRt.top,
//                      fillRt.right, fillRt.bottom);
//            SetBkMode(hdc, TRANSPARENT);
//            std::wstring gaugeText = L"BOOM: " +
//                std::to_wstring(bombCount * 20) + L"%";
//            TextOut(hdc, 100, 500, gaugeText.c_str(), gaugeText.length());
//            SelectObject(hdc, oldBrush);
//            DeleteObject(brush);
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//        case WM_DESTROY:
//            KillTimer(hWnd, 1);
//            PostQuitMessage(0);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}


//
//struct Line
//{
//    POINT start;
//    POINT end;
//    COLORREF color;
//};
//
//struct Button
//{
//    POINT pos;
//    POINT size;
//    COLORREF color;
//};
//
//RECT GetRect(const Button& button)
//{
//    RECT rt =
//    {
//        button.pos.x - button.size.x / 2,
//        button.pos.y - button.size.y / 2,
//        button.pos.x + button.size.x / 2,
//        button.pos.y + button.size.y / 2,
//    };
//    return rt;
//}
//
//bool InRect(RECT rect, POINT point)
//{
//    if (rect.left <= point.x && rect.right >= point.x)
//        if (rect.top <= point.y && rect.bottom >= point.y)
//            return true;
//    return false;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static std::vector<Line> vecLines;
//    static bool isClick = false;
//    static POINT prevPos;
//    static RECT redRect = { 50, 25, 150, 75 };
//    static RECT greenRect = { 150, 25, 250, 75 };
//    static RECT blueRect = { 250, 25, 350, 75 };
//    static COLORREF curColor = RGB(0,0,0);
//
//    static Button redButton  { {100, 100}, {100, 50}, RGB(255, 0, 0)};
//    static Button greenButton{ {200, 100}, {100, 50}, RGB(0, 255, 0)};
//    static Button blueButton { {300, 100}, {100, 50}, RGB(0, 0, 255)};
//
//    static HBRUSH redBrush = CreateSolidBrush(redButton.color);
//    static HBRUSH greenBrush = CreateSolidBrush(greenButton.color);
//    static HBRUSH blueBrush = CreateSolidBrush(blueButton.color);
//
//    static RECT redRect = GetRect(redButton);
//    static RECT greenRect = GetRect(greenButton);
//    static RECT blueRect = GetRect(blueButton);
//
//    switch (message)
//    {
//        case WM_LBUTTONDOWN:
//            prevPos = { LOWORD(lParam), HIWORD(lParam) };
//            if (PtInRect(&redRect, prevPos))
//            {
//                curColor = redButton.color;
//            }
//            else if (PtInRect(&blueRect, prevPos))
//            {
//                curColor = blueButton.color;
//            }
//            else if (PtInRect(&greenRect, prevPos))
//            {
//                curColor = greenButton.color;
//            }
//
//            isClick = true;
//            break;
//        case WM_LBUTTONUP:
//        {
//            isClick = false;
//
//            POINT point = { LOWORD(lParam), HIWORD(lParam) };
//        }
//            break;
//        case WM_MOUSEMOVE:
//        {
//            if (isClick)
//            {
//                vecLines.push_back({ lastPoint, { LOWORD(lParam), HIWORD(lParam) } });
//                lastPoint = vecLines.back().end;
//                InvalidateRect(hWnd, nullptr, false);
//            }
//        }
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            SelectObject(hdc, redBrush);
//            Rectangle(hdc, redRect.left, redRect.top, redRect.right, redRect.bottom);
//
//            SelectObject(hdc, greenBrush);
//            Rectangle(hdc, greenRect.left, greenRect.top, greenRect.right, greenRect.bottom);
//
//            SelectObject(hdc, blueBrush);
//            Rectangle(hdc, blueRect.left, blueRect.top, blueRect.right, blueRect.bottom);
//
//            SetBkMode(hdc, TRANSPARENT);
//            wstring str;
//            DrawText(hdc, L"Red", 3, &redRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//            DrawText(hdc, L"Green", 5, &greenRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//            DrawText(hdc, L"Blue", 4, &blueRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//
//            for (const auto& line : vecLines)
//            {
//                HPEN pen = CreatePen(PS_SOLID, 2, line.color);
//                HPEN oldPen = (HPEN)SelectObject(hdc, pen);
//                MoveToEx(hdc, line.start.x, line.start.y, nullptr);
//                LineTo(hdc, line.end.x, line.end.y);
//                SelectObject(hdc, oldPen);
//                DeleteObject(pen);
//            }
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//        case WM_DESTROY:
//            DeleteObject(redBrush);
//            DeleteObject(greenBrush);
//            DeleteObject(blueBrush);
//            PostQuitMessage(0);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static POINT playerPos = { 300, 300 };
//    static POINT playerSize = { 50,50 };
//
//    static POINT objPos = { };
//    static POINT objSize = { 50,50 };
//    static RECT rt;
//    static int floorY = 325;
//
//    static bool isJump = false;
//    static int gravity = 1;
//    static int jumpPower = -15;
//    static int jumpVelocity = 0;
//
//    switch (message)
//    {
//    case WM_CREATE:
//    {
//        SetTimer(hWnd, 1, 100, nullptr);
//        srand((unsigned int)time(nullptr));
//        GetClientRect(hWnd, &rt);
//        objPos = { rand() & rt.right, 0 };
//    }
//        break;
//    case WM_KEYDOWN:
//    {
//        if (wParam == VK_SPACE)
//        {
//            isJump = true;
//            jumpVelocity = jumpPower;
//        }
//    }
//    break;
//    case WM_TIMER:
//    {
//        if (isJump)
//        {
//            playerPos.y += jumpVelocity;
//            jumpVelocity += gravity;
//            if (playerPos.y + playerSize.y / 2 >= floorY)
//            {
//                jumpVelocity = 0;
//                isJump = false;
//            }
//        }
//
//        objPos.y += 5;
//        if (objPos.y + objSize.y / 2 >= floorY)
//        {
//            objPos = { rand() & rt.right, 0 };
//        }
//        InvalidateRect(hWnd, nullptr, true);
//    }
//        break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        
//        Ellipse(hdc
//                , objPos.x - objSize.x / 2
//                , objPos.y - objSize.y / 2
//                , objPos.x + objSize.x / 2
//                , objPos.y + objSize.y / 2);
//        Rectangle(hdc
//                  , playerPos.x - playerSize.x / 2
//                  , playerPos.y - playerSize.y / 2
//                  , playerPos.x + playerSize.x / 2
//                  , playerPos.y + playerSize.y / 2);
//        MoveToEx(hdc, 0, floorY, nullptr);
//        LineTo(hdc, rt.right, 325);
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
//struct Object
//{
//    POINT pos;
//    POINT size;
//};
//// 연습문제 10-2
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static std::vector<Object> vecObjs;
//    static bool isClick = false;
//    static POINT startPos;
//    static POINT endPos;
//    switch (message)
//    {
//        case WM_LBUTTONDOWN:
//        {
//            isClick = true;
//            startPos = { LOWORD(lParam), HIWORD(lParam) };
//            endPos = startPos;
//        }
//        break;
//        case WM_MOUSEMOVE:
//            if (isClick)
//            {
//                endPos = { LOWORD(lParam), HIWORD(lParam) };
//                InvalidateRect(hWnd, nullptr, true);
//            }
//            break;
//        case WM_LBUTTONUP:
//        {
//            isClick = false;
//            Object obj;
//            obj.pos = { {(startPos.x + endPos.x) / 2} ,{(startPos.y + endPos.y) / 2} };
//            obj.size = { {abs(endPos.x - startPos.x)},{abs(endPos.y - startPos.y)} };
//            vecObjs.push_back(obj);
//            InvalidateRect(hWnd, nullptr, true);
//        }
//        break;
//        case WM_MOUSEWHEEL:
//        {
//            short delta = GET_WHEEL_DELTA_WPARAM(wParam);
//            if (!vecObjs.empty())
//            {
//                auto& lastObj = vecObjs.back();
//                if (delta > 0)
//                {
//                    lastObj.size.x += 10;
//                    lastObj.size.y += 10;
//                }
//                else
//                {
//                    lastObj.size.x = std::max(10, (int)lastObj.size.x - 10);
//                    lastObj.size.y = std::max(10, (int)lastObj.size.y - 10);
//                }
//                InvalidateRect(hWnd, nullptr, true);
//            }
//
//        }
//        break;
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            for (const auto& obj : vecObjs)
//            {
//                Rectangle(hdc
//                          , obj.pos.x - obj.size.x / 2
//                          , obj.pos.y - obj.size.y / 2
//                          , obj.pos.x + obj.size.x / 2
//                          , obj.pos.y + obj.size.y / 2
//                );
//            }
//            if (isClick)
//            {
//                Rectangle(hdc, startPos.x, startPos.y,
//                          endPos.x, endPos.y);
//            }
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;

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
