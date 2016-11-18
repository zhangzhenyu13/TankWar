#include"Bullet.h"

void Bullet::draw() {
	HDC mdc = CreateCompatibleDC(*pDC);
	HBITMAP hbmp = LoadBitmap(*pInst,MAKEINTRESOURCE(RED_BULLET));
	BITMAP bmp;
	HGDIOBJ hOldSel = SelectObject(mdc,hbmp);
	GetObject(hbmp,sizeof(BITMAP),&bmp);

	StretchBlt(*pDCObj,x,y,5,5,mdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	DeleteObject(hOldSel);
	
	DeleteObject(hbmp);
	DeleteDC(mdc);
}