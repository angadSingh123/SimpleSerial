#include "Graphics.h"
#include <stdio.h>


Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;

}

Graphics::~Graphics()
{
	if (brush) brush->Release();
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (textFactory) textFactory->Release();
	if (textFormat) textFormat->Release();

}

bool Graphics::Init(HWND windowHandle) {

	//Create a directX factory and see if all is valid.
	HRESULT hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (hResult != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	hResult = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (hResult != S_OK) return false;	

	wcscpy_s(DEFAULT_FONT, L"Gabriola");

	wcscpy_s(DEFAULT_LANGUAGE, L"en-us");

	if(!InitText(DEFAULT_SIZE, &DEFAULT_FONT[0], DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL)) return false;

	Fill(0, 0, 0, 0);

	return true;

}

void Graphics::ClearScreen(float r, float g, float b) {


	renderTarget->Clear(D2D1::ColorF(r, g, b));

}

void Graphics::DrawCircle(float x, float y, float radius, float strokeWidth) {

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, strokeWidth);

}

void Graphics::FillRect(float x, float y, float w, float h, float strokeWieght)
{

	D2D1_RECT_F rect = D2D1::RectF(x, y, w, h);

	renderTarget->FillRectangle(&rect, brush);

}

void Graphics::Fill(float r, float g, float b, float a) {

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

}

//Draws Text
void Graphics::Text(WCHAR * string, int len, int x, int y, int w, int h)
{	

	renderTarget->DrawTextA(string, len, textFormat, D2D1::Rect(0,0,w,h), brush);

}

bool Graphics::Font(wchar_t * font, DWRITE_FONT_WEIGHT wt)
{

	return InitText(textFormat->GetFontSize(), font, wt);

}

bool Graphics::FontSize(float)
{

	wchar_t * ptr = GetFamilyName();

	return InitText(textFormat->GetFontSize(), ptr, textFormat->GetFontWeight());

	delete ptr;

}

bool  Graphics::InitText(float sz, wchar_t * font, DWRITE_FONT_WEIGHT wt)
{

	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast <IUnknown**>(&textFactory));

	if (hr != S_OK) return false;

	 hr = textFactory->CreateTextFormat(font, 
		NULL, 
		wt, 
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_NORMAL,
		sz, DEFAULT_LANGUAGE, 
		&textFormat);

	if (hr != S_OK) return false;	

	return true;

}

wchar_t * Graphics::GetFamilyName()
{
	wchar_t famName[64];

	int len = textFormat->GetFontFamilyNameLength();

	textFormat->GetFontFamilyName(famName, len+1);

	return &famName[0];

}
