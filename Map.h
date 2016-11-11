#pragma once
#include"GraphicUnit.h"
#include"MapData.h"
#include"windows.h"
class Map :public GraphicUnit{
	HWND& hWnd;
	HINSTANCE& hInst;
	MapData1* _map;
public:
	Map(HINSTANCE& hInst1,HWND& hWnd1):hWnd(hWnd1),hInst(hInst1) {}
	virtual void draw();

	virtual void readData(GameData& _map1) {
		_map = (MapData1*)&_map1;
	}
};