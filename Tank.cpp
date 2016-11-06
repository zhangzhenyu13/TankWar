#include"Tank.h"
void Tank::draw() {
	readData(*_tank);
	HBRUSH brush=CreateSolidBrush(RGB(255,10,10));
	SelectObject(hdc,brush);
	Rectangle(hdc,450,200,490,240);
	DeleteObject(brush);
}