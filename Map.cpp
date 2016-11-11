#include"Map.h"
#include<windows.h>
#include"resource.h"
void Map::draw() {
	HDC hdc = GetDC(hWnd);

	//
	
	//
	HBITMAP hbmp,hbmp1;
	BITMAP bmp,bmp1;
	HDC hmem,hmem1;

	hmem = CreateCompatibleDC(hdc);
	hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(NORMAL_BRICK));
	hbmp1 = LoadBitmap(hInst, MAKEINTRESOURCE(BONUS_BRICK));
	
	GetObject(hbmp1,sizeof(BITMAP),&bmp1);
	GetObject(hbmp, sizeof(BITMAP), &bmp);
	RECT crect;
	GetClientRect(hWnd, &crect);
	int x=1, y=1;
	RECT rect;
	SelectObject(hmem, hbmp1);
	
	for (int i = 0; i < _map->size(); i++) {
		if (_map->getPos(i).style == 1) {
			SelectObject(hmem,hbmp);
			rect = _map->getPos(i).rect;
			StretchBlt(hdc, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
				hmem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		}
		
	}
	DeleteObject(hbmp);
	DeleteObject(hbmp1);
	ReleaseDC(hWnd, hdc);
}