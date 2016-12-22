#include"StartUpWnd.h"
void StartUpWnd::draw() {
	HBITMAP hbmp1;
	HDC hmem = CreateCompatibleDC(*pDC);//current dc
	BITMAP bmp1;
	hbmp1 = LoadBitmap(*pInst, MAKEINTRESOURCE(STARTUP_PIC));//load resource with hbmp
	GetObject(hbmp1,sizeof(BITMAP),&bmp1);
	HGDIOBJ hOldSel;
	hOldSel = SelectObject(hmem, hbmp1);
	StretchBlt(*pDCObj,0,0,1400,800,hmem,0,0,bmp1.bmWidth,bmp1.bmHeight,SRCCOPY);
	

	//release Mem
	DeleteObject(hbmp1);
	DeleteObject(hOldSel);
	DeleteDC(hmem);
}