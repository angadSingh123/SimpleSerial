#pragma once
#include <Windows.h>
#include <wingdi.h>
#include <gdiplus.h>
#include <gdipluscolor.h>


class ImageReader
{

	Gdiplus::GdiplusStartupInput h_inp;

	static Gdiplus::Bitmap bmp;

	ULONG_PTR gdiToken;	

	int width, height;

public:
	
	ImageReader(const wchar_t * file);

	~ImageReader();	

	Gdiplus::Color Read(int, int);

	inline int GetWidth() { return bmp.GetWidth(); }

	inline int GetHeight() { return bmp.GetHeight(); }

};

