#pragma once
#include"GraphicUnit.h"
#include"MapData.h"
#include"windows.h"
class Map :public GraphicUnit{
	HDC& hdc;
	MapData* _map;
public:
	Map(HDC& hdc1):hdc(hdc1) {}
	virtual void draw();
protected:
	virtual void readData(GameData&) {
	}
};