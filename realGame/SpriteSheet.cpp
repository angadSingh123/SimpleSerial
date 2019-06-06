#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(wchar_t * f, Graphics * gfx)
{
	this->g = gfx;
	this->bmp = NULL;
	HRESULT hr = NULL;	

	IWICImagingFactory * wicFactory = NULL;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID *)&wicFactory);

	if (!(hr == S_OK)) return;

	IWICBitmapDecoder * wicDecoder = NULL;

	hr = wicFactory->CreateDecoderFromFilename(f, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);

	IWICBitmapFrameDecode * wicFrame = NULL;

	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter * wicConverter = NULL;

	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

	hr = g->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);

	//Release garbage

	if (wicFactory) wicFactory->Release();

	if (wicDecoder) wicDecoder->Release();

	if (wicConverter) wicConverter->Release();

	if (wicFrame) wicFrame->Release();

	this->height = this->bmp->GetSize().height;

	this->width = this->bmp->GetSize().width;

}

SpriteSheet::SpriteSheet(wchar_t * f, Graphics * gfx, int size) : SpriteSheet::SpriteSheet(f, gfx) {

	this->spriteSize = size;

	this->spritesAcrossH = this->width / size;

	this->spritesAcrossV = this->height / size;

}

SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();

}

void SpriteSheet::Draw() {

	//Source Rectangle
	D2D1_RECT_F source = D2D1::RectF(0, 0, bmp->GetSize().width, bmp->GetSize().height);

	//Destination Rectangle
	D2D1_RECT_F dest = D2D1::RectF(0, 0, bmp->GetSize().width, bmp->GetSize().height);

	//draw it
	g->GetRenderTarget()->DrawBitmap(bmp, &dest, 1, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &source);

}

void SpriteSheet::Draw(int row, int col, int x, int y)
{
	//Algo

	D2D1_RECT_F source = D2D1::RectF((col * spriteSize), (row * spriteSize), (col * spriteSize) + spriteSize, (row * spriteSize) + spriteSize);

	//Destination on screen
	D2D1_RECT_F dest = D2D1::RectF(x, y, x + this->spriteSize, y + this->spriteSize);

	g->GetRenderTarget()->DrawBitmap(bmp, &dest, 1, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &source);


}
