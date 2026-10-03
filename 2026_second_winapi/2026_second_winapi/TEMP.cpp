//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static POINT objPos = { 300, 300 };
//    static POINT objSize = { 50, 50 };
//    static POINT obj2Pos = { rand() % (int)WINDOW_WIDTH, 0 };
//    static POINT obj2Size = { 50, 50 };
//    static float playerYVel = 0;
//    static float gravity = -9.8f;
//    static int jumpPower = 15;
//    static int delta = 100;
//    static bool isGrounded = false;
//    switch (message)
//    {
//        case WM_CREATE:
//            SetTimer(hWnd, 1, 100, nullptr);
//            break;
//        case WM_TIMER:
//            isGrounded = false;
//
//            if (objPos.y >= 300 && playerYVel >= 0)
//            {
//                objPos.y = 300;
//                isGrounded = true;
//                playerYVel = 0;
//            }
//            
//            playerYVel += 1;
//            objPos.y += playerYVel;
//
//            obj2Pos.y += 5;
//            if (obj2Pos.y >= 300)
//                obj2Pos = { rand() % (int)WINDOW_WIDTH, 0 };
//
//            InvalidateRect(hWnd, nullptr, true);
//            break;
//        case WM_KEYDOWN:
//        {
//            if (wParam == VK_SPACE && isGrounded)
//                playerYVel = -jumpPower;
//            //int x = LOWORD(lParam);
//            //int y = HIWORD(lParam);
//            //isVisible = false;
//            //int ax = objPos.x - x;
//            //int ay = objPos.y - y;
//            //if (ax * ax + ay * ay < 100 * 100)
//            //{
//            //    isVisible = true;
//            //    objPos = { x, y };
//            //}
//            //InvalidateRect(hWnd, nullptr, true);
//        }
//        break;
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//
//            //if (isVisible)
//            //    Rectangle(hdc
//            //              , objPos.x - objSize.x / 2
//            //              , objPos.y - objSize.y / 2
//            //              , objPos.x + objSize.x / 2
//            //              , objPos.y + objSize.y / 2
//            //    );
//
//            Rectangle(hdc
//                    , objPos.x - objSize.x / 2
//                    , objPos.y - objSize.y / 2
//                    , objPos.x + objSize.x / 2
//                    , objPos.y + objSize.y / 2
//            );
//            MoveToEx(hdc, 0, 325, nullptr);
//            LineTo(hdc, 2000, 325);
//            Ellipse(hdc
//                      , obj2Pos.x - obj2Size.x / 2
//                      , obj2Pos.y - obj2Size.y / 2
//                      , obj2Pos.x + obj2Size.x / 2
//                      , obj2Pos.y + obj2Size.y / 2
//            );
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