#include"StartUpWnd.h"
void StartUpWnd::draw() {
	if (mode == 1) return;
	HBITMAP hbmp1, hbmp2;
	HDC hmem = CreateCompatibleDC(*pDC);//current dc
	BITMAP bmp1,bmp2;
	hbmp1 = LoadBitmap(*pInst, MAKEINTRESOURCE(STARTUP_PIC));//load resource with hbmp
	hbmp2 = LoadBitmap(*pInst, MAKEINTRESOURCE(ENDUP_PIC));//load resource with hbmp
	GetObject(hbmp1,sizeof(BITMAP),&bmp1);
	GetObject(hbmp2, sizeof(BITMAP), &bmp2);
	HGDIOBJ hOldSel;
	hOldSel = SelectObject(hmem, hbmp1);
	if (mode == 2)
		SelectObject(hmem,hbmp2);
	//
	if(mode==0)
		StretchBlt(*pDCObj,0,0,1400,800,hmem,0,0,bmp1.bmWidth,bmp1.bmHeight,SRCCOPY);
	else if(mode==2)
		StretchBlt(*pDCObj, 0, 0, 1400, 800, hmem, 0, 0, bmp2.bmWidth, bmp2.bmHeight, SRCCOPY);
	//release Mem
	DeleteObject(hbmp1);
	DeleteObject(hbmp2);
	DeleteObject(hOldSel);
	DeleteDC(hmem);
}