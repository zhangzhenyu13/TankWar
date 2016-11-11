#include"Tank.h"
#include"resource.h"
void Tank::draw() {
	
	HDC hdc = GetDC(hWnd);
	
	
	//
	readData(*_tank);
	
	//
	HBITMAP hbmp;
	BITMAP bmp;
	HDC hmem;
	
	hmem = CreateCompatibleDC(hdc);
	hbmp = LoadBitmap(hInst,MAKEINTRESOURCE(MY_TANK));
	SelectObject(hmem,hbmp);
	GetObject(hbmp,sizeof(BITMAP),&bmp);
	if(_tank->getfireflag()) {
		RECT crect;
		GetClientRect(hWnd, &crect);
		int *pos = _tank->getfirepos();
		if(pos[0]<crect.left || pos[0]>crect.right || pos[1]<crect.top || pos[1]>crect.bottom)
			_tank->changefireflag(0);
		else
			Ellipse(hdc,pos[0]-2,pos[1]-2,pos[0]+2,pos[1]+2);
	}
	RECT myrect;
	myrect.bottom = _tank->getposy()+10;
	myrect.left = _tank->getposx()-10;
	myrect.right = _tank->getposx()+10;
	myrect.top = _tank->getposy()-10;
	StretchBlt(hdc,myrect.left,myrect.top,myrect.right-myrect.left,myrect.bottom-myrect.top,
		hmem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	DeleteObject(hbmp);
	ReleaseDC(hWnd,hdc);
}