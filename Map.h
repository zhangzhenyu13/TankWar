#pragma once
#include<windows.h>
#include"GameData.h"
#include"GraphicUnit.h"
#include"MapData.h"

class Map :public GraphicUnit{
	HWND* pWnd;
	HINSTANCE* pInst;
	HDC* pDC,*pDCObj;
	MapData* _map;
	std::string mapname;
public:
	
	void setHandle(HWND*hWnd,HINSTANCE*hInst) {
		this->pWnd = hWnd;
		this->pInst = hInst;
	}
	void setDC(HDC* hdc1,HDC* hdc2) {
		pDC = hdc1;
		pDCObj = hdc2;
	}
	virtual void draw();
	std::string getName() { return mapname; }
	virtual void readData(GameData* map) {
		_map = dynamic_cast<MapData*>(map);
	}
};