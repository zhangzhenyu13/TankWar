#include"Map.h"
void Map::draw() {
	
	HBITMAP hbmp1,hbmp2;//handle bmp
	BITMAP bmp1,bmp2;//info of bmp

	HDC hmem = CreateCompatibleDC(*pDC);//current dc

	hbmp1 = LoadBitmap(*pInst, MAKEINTRESOURCE(NORMAL_BRICK));//load resource with hbmp
	hbmp2 = LoadBitmap(*pInst, MAKEINTRESOURCE(BONUS_BRICK));
	GetObject(hbmp1,sizeof(BITMAP),&bmp1);
	GetObject(hbmp2, sizeof(BITMAP), &bmp2);

	HGDIOBJ hOldSel;
	hOldSel=SelectObject(hmem, hbmp1);
	
	RECT rect;
	for (int i = 0; i < _map->size(); i++) {
		if (_map->getPos(i).style == 1) {
			SelectObject(hmem,hbmp1);
			rect = _map->getPos(i).rect;
			StretchBlt(*pDCObj, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,//copy data between dc
				hmem, 0, 0, bmp1.bmWidth,bmp1.bmHeight,SRCCOPY);
		}
		
	}

	//release Mem
	DeleteObject(hbmp1);
	DeleteObject(hbmp2);
	DeleteObject(hOldSel);
	DeleteDC(hmem);
}