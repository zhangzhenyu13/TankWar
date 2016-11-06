#include"Map.h"
#include<cstdlib>
void Map::draw() {
	readData(*_map);
	HBRUSH brush=CreateSolidBrush(RGB(100,200,100));
	SelectObject(hdc,brush);
	int x, y;
	for (y = 0; y < 14; y++)
		for (x = 0; x < 24; x++)
			rand() % 2 == 1 ? Rectangle(hdc, x * 50, y * 50, x * 50 + 50, y * 50 + 50) :1;
	DeleteObject(brush);
}