#include"GraphicLayout.h"

using namespace std;

void GraphicLayout::draw() {
	PAINTSTRUCT ps;
	HBRUSH bkbrush = CreateSolidBrush(RGB(0,10,0));
	RECT crect;
	GetClientRect(pWnd, &crect);

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
		data[i]->draw();
	}
	
	
	BitBlt(hdc,crect.left,crect.top,crect.right-crect.left,crect.bottom-crect.top,hmem,0,0,SRCCOPY);
	

	EndPaint(pWnd, &ps);

	DeleteObject(bkbrush);
	DeleteObject(hMbmp);
	
	SelectObject(hmem, hOldSel);
	DeleteDC(hmem);
	
	ReleaseDC(pWnd,hdc);
	
}
