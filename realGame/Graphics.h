#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <winnt.h>

/* Main direct2D controller class and graphics engine.


*/


class Graphics
{

	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	IDWriteTextFormat* textFormat;
	IDWriteFactory * textFactory;
	
public:

	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget * GetRenderTarget() {

		return renderTarget;

	}

	void BeginDraw() {

		renderTarget->BeginDraw();

	}

	void EndDraw() {

		renderTarget->EndDraw();

	}

	void ClearScreen(float r, float g, float b);

	void DrawCircle(float x, float y, float rad, float strokeWidth);

	void FillRect(float x, float y, float w, float h, float strokeWieght);

	void Fill(float r, float g, float b, float a);

	void Text(WCHAR *, int, int, int, int, int);

	bool Font(wchar_t *, DWRITE_FONT_WEIGHT);

	bool FontSize(float);	

private:

	WCHAR charArray[100];

	wchar_t  DEFAULT_FONT[9];

	wchar_t DEFAULT_LANGUAGE[6];

	const float DEFAULT_SIZE = 36.0f;

	bool InitText(float sz, wchar_t * font, DWRITE_FONT_WEIGHT wt);

	wchar_t * GetFamilyName();	

};