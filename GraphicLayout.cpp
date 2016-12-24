#include"GraphicLayout.h"
ULONG_PTR m_gdiplusToken;

using namespace std;

void GraphicLayout::draw() {
	//Gdiplus
     Gdiplus::GdiplusStartupInput GdiplusStartupInput;
     Gdiplus::GdiplusStartup(&m_gdiplusToken, &GdiplusStartupInput, NULL);
	 //
	PAINTSTRUCT ps;
	HBRUSH bkbrush = CreateSolidBrush(RGB(10,10,30));
	RECT crect={0,0,1400,800};
	

	HDC hdc = BeginPaint(pWnd, &ps);
	HDC hmem = CreateCompatibleDC(hdc);

	HBITMAP hMbmp=CreateCompatibleBitmap(hdc, crect.right - crect.left, crect.bottom - crect.top);
	HGDIOBJ hOldSel=
	SelectObject(hmem,hMbmp);
	
	SelectObject(hmem,bkbrush);
	//SelectObject(hdc,bkbrush);
	
	
	//start drawing
	FillRect(hmem, &crect, bkbrush);
	for (int i = 0; i < data.size(); i++) {
		data[i]->setDC(&hdc,&hmem);
		if(data[i]!=status&&data[i]!=start)
		data[i]->draw();
	}
	status->draw();
	start->mode = showStartUP;
	start->draw();
	

	BitBlt(hdc,crect.left,crect.top,crect.right-crect.left,crect.bottom-crect.top,hmem,0,0,SRCCOPY);
	

	EndPaint(pWnd, &ps);

	DeleteObject(bkbrush);
	DeleteObject(hMbmp);
	
	SelectObject(hmem, hOldSel);
	DeleteDC(hmem);
	
	ReleaseDC(pWnd,hdc);
	//
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}
