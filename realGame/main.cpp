#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Graphics.h"
#include "GameLevel.h"
#include "Level2.h"
#include "GameController.h"

//Dimensions
const static int LOCX = 100;
const static int LOCY = 100;
const static int WIDTH = 500;
const static int HEIGHT = 500;

static bool running = true;

long micros();

Graphics* gfx;

LARGE_INTEGER st, et, ms, freq;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_DESTROY:
		PostQuitMessage(0);
		exit(0);

	case WM_WINDOWPOSCHANGING:
		running = false;

	case WM_KEYDOWN:

		switch (wParam) {

		case VK_LEFT:

			Beep(1500, 15);
			break;

		default:
			break;

		}


	default:
		DefWindowProc(hwnd, uMsg, wParam, lParam);
		running = true;
	}

	return 5000;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	QueryPerformanceCounter(&st);
	QueryPerformanceFrequency(&freq);

	WNDCLASSEX windowClass;
	// Zero the strucutre
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	//Initialise the window paramtres.
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "Window";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	//Register the class the we just created.
	RegisterClassEx(&windowClass);

	//Make the client area the specified dimensions.
	RECT rect = { 0, 0, WIDTH, HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//Create the window and get its handle (pointer)
	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Window", "DirectX HHI", WS_OVERLAPPEDWINDOW, LOCX, LOCY, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	//Use this if WS_VISIBLE style not used earlier in the CreateWindow function
	ShowWindow(windowHandle, ncmdshow);

	//Begin gameController
	GameController::Init(WIDTH, HEIGHT);

	//Create a graphics object
	gfx = new Graphics();

	if (!gfx->Init(windowHandle)) {

		delete gfx;
		return -1;

	}

	GameLevel::Init(gfx);

	//Load initial level	
	GameController::LoadInitialLevel(new Level2());

	MSG message;

	//use peek message to regain control when there is no message to thw window
	message.message = WM_NULL;

	long lastTime = micros();
	long currentTime;

	long ticks = 60;

	double ns = 1000000 / ticks;

	double delta = 0;

	Gdiplus::Bitmap bmp(L"ts.png");

	Gdiplus::Color c;

	
	while (running) {
		//Run a loop for getting window events
		while ((message.message != WM_QUIT) || (message.message != WM_DESTROY)) {

			currentTime = micros();

			delta += (currentTime - lastTime) / ns;

			lastTime = currentTime;


			//for (int i = 0; i < 55; i++) {

			//	for (int j = 0; j < 55; j++) {

			//		bmp.GetPixel(i, j, &c);

			//		printf("%d %d %c %c %c\n", i, j, c.GetRed(), c.GetBlue(), c.GetGreen());

			//	}

			//}


			if (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE))
				DispatchMessage(&message);


			while (delta > 1) {

				//GameController::Update();

				delta--;

			}

			gfx->BeginDraw();

			int x = rand() % 255;			

			gfx->Fill(0, 255, 0, x);

			gfx->FillRect(0,0,WIDTH/2,HEIGHT,1);
			

			gfx->EndDraw();

		}

		return 10;

	}
}

long micros() {

	QueryPerformanceCounter(&et);
	et.QuadPart = et.QuadPart - st.QuadPart;
	et.QuadPart *= 1000000;
	et.QuadPart /= freq.QuadPart;
	return et.QuadPart;

}
