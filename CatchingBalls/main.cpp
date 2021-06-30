/********************************************************
 Source Filename: main.cpp
 Student Name (ID): Siu Chun Kit (200089921)
 Course Name (Code): HD in Games & Animation (IT114206)
 Program Description:
 This program is CatchingBalls
*********************************************************/
#include <iostream>
#include <windows.h>

using namespace std;
int			score = 0;					//game score
int         x = 0, y = 0;				//ball x,y
int			counter = 665;				//time counter
bool		click = false;

#define WINDOW_CLASS_NAME   "wc1"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

LRESULT CALLBACK WndProc(	HWND hWnd,
							UINT msg,
							WPARAM wParam,
							LPARAM lParam) {

	HDC         hDC;
	COLORREF colorWanted = RGB(255, 255, 255);

	switch (msg) {
	case WM_CREATE:
		return(0);
		break;

	case WM_PAINT:
		return(0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);
		break;

	case WM_LBUTTONDOWN: {				//mouse click kill ball
		hDC = GetDC(hWnd);
		LONG mouseX = LOWORD(lParam);
		LONG mouseY = HIWORD(lParam);
		DWORD color = GetPixel(hDC, mouseX, mouseY);
		if (color == colorWanted && counter>0) {
			score++;
			click = true;
		}
		return(0);
		break;
	}

	case WM_CLOSE:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
		break;

	case WM_KEYDOWN: {
		int virtual_code = (int)wParam;
		int key_state = (int)lParam;

		if (wParam == VK_SPACE) {
			system("pause");
		}
			

		if (counter == 0) {
			switch (virtual_code) {
			case VK_RETURN:				//Game Replay
				click = true;
				score = 0;
				counter = 665;
				break;
			case VK_ESCAPE:				//Quit Game
				PostQuitMessage(0);
				break;
			}
		}
		return(0);
		break;
	}

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
		break;

	}
}

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR szCmdLine,
					int iCmdShow) {

	WNDCLASSEX  wc1;
	HWND        hWnd;
	MSG         msg;

	int         z = rand() % 141 - 60;	//ball size
	int			s = (rand() % 4) + 1;	//ball random set
	int			rx = (rand() % 13 + 2);		//ball x rate
	int			ry = (rand() % 13 + 2);		//ball y rate

	wc1.cbSize = sizeof(WNDCLASSEX);
	wc1.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc1.lpfnWndProc = WndProc;
	wc1.cbClsExtra = 0;
	wc1.cbWndExtra = 0;
	wc1.hInstance = hInstance;
	wc1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc1.hCursor = LoadCursor(NULL, IDC_HAND);
	wc1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc1.lpszMenuName = NULL;
	wc1.lpszClassName = WINDOW_CLASS_NAME;
	wc1.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc1))
		return(0);

	if (!(hWnd = CreateWindowEx(NULL, WINDOW_CLASS_NAME,
		"CatchingBalls - Siu Chun Kit (200089921) - Compiled on June 20 2021, 17:00",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 1000, 800, NULL, NULL, hInstance, NULL)))
		return(0);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	while (TRUE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		HDC hDC = GetDC(hWnd);

		// create a brush to fill the background
		COLORREF bgColor = RGB(0, 0, 0);
		HBRUSH bgBrush = CreateSolidBrush(bgColor);

		// fill the background
		RECT bgRect;
		bgRect.left = 0;
		bgRect.bottom = 0;
		bgRect.right = 1000;
		bgRect.top = 800;

		FillRect(hDC, &bgRect, bgBrush);

		// draw a text string at a random location
		//SetBkMode(hDC, TRANSPARENT);
		int			time = counter / 22;
		char outStr[100] = "";			// output string buffer
		sprintf_s(outStr, "Time Remain: %ds  Score: %d  (Press [Space] to stop game)", time, score);

		// set foreground to  color
		SetTextColor(hDC, RGB(254, 254, 254));
		SetBkColor(hDC, RGB(0, 0, 0)); // set background to black

		TextOut(hDC, 10, 10, outStr, strlen(outStr));

		//stop game in 30 seconds 
		if (counter == 0)
		{
			TextOut(hDC, 10, 25, "Game over!!!", strlen("Game over!!!"));
			TextOut(hDC, 10, 40, "Press [Esc] to quit, [Enter] to replay!", strlen("Press [Esc] to quit, [Enter] to replay!"));
		}
		// clean up all brushs
		DeleteObject(bgBrush);

		// create pens for drawing
		HPEN facePen = CreatePen(PS_SOLID, 50, RGB(255, 255, 255));

		// draw a ball
		SelectObject(hDC, facePen);
		Arc(hDC, x, y, z + x, z + y, 0, 0, 0, 0);

		// clean up all pens
		DeleteObject(facePen);

		ReleaseDC(hWnd, hDC);

		//set time
		if (counter > 0) {
			Sleep(1000 / 25);
			counter--;
		}

		//set time end sleep
		if (counter == 0) {
			Sleep(1000 / 25);
		}

		// move the ball
		if (s == 1) {
			if (y < 800 && !click) {
				y += ry;
			}
			else{
				x = rand() % 1000;
				y = 0;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}

			if (x < 1000 && !click) {
				x += rx;
			}
			else {
				x = 0;
				y = rand() % 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}
		}

		if (s == 2) {
			if (y < 800 && !click) {
				y += ry;
			}
			else {
				x = rand() % 1000;
				y = 0;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}

			if (x > 0 && !click) {
				x -= rx;
			}
			else {
				x = 1000;
				y = rand() % 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}
		}

		if (s == 3) {
			if (y > 0 && !click) {
				y -= ry;
			}
			else {
				x = rand() % 1000;
				y = 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}

			if (x < 1000 && !click) {
				x += rx;
			}
			else {
				x = 0;
				y = rand() % 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}
		}

		if (s == 4) {
			if (y > 0 && !click) {
				y -= ry;
			}
			else {
				x = rand() % 1000;
				y = 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}

			if (x > 0 && !click) {
				x -= rx;
			}
			else {
				x = 1000;
				y = rand() % 800;
				z = rand() % 101 - 50;
				s = (rand() % 4) + 1;
				rx = (rand() % 13 + 2);	//ball x rate
				ry = (rand() % 13 + 2);	//ball y rate
				click = false;
			}
		}
	}
	return((int)(msg.wParam));
}