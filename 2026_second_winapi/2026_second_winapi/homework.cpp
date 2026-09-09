LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static WCHAR wArr[2];

    switch (message)
    {
        //case WM_KEYDOWN:
        //{
        //    int a = 0;
        //}
        //break;
        case WM_CHAR:
        {
            HDC hdc = GetDC(hWnd);
            //wstring str = L"2-2반 이제 진짜 시작";
            //TextOut(hdc, 10, 10, str.c_str(), str.length());
            wArr[0] = wParam;
            wArr[1] = '\0';
            TextOut(hdc, 10, 10, wArr, wcslen(wArr));
            ReleaseDC(hWnd, hdc);
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            HBRUSH bodyBrush = CreateSolidBrush(RGB(50, 50, 50));
            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));

            HPEN defaultPen = (HPEN)SelectObject(hdc, pen);

            HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, bodyBrush);
            Rectangle(hdc, 100, 50, 250, 350);

            SelectObject(hdc, redBrush);
            Ellipse(hdc, 125, 75, 225, 175);

            SelectObject(hdc, greenBrush);
            Ellipse(hdc, 125, 75 + 150, 225, 175 + 150);

            SelectObject(hdc, defaultPen);
            SelectObject(hdc, defaultBrush);
            DeleteObject(pen);
            DeleteObject(bodyBrush);
            DeleteObject(redBrush);
            DeleteObject(greenBrush);

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