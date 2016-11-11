#pragma once
#include<windows.h>
#include"GraphicUnit.h"
#include"TankData.h"
class Tank:public GraphicUnit{
	HWND& hWnd;
	HINSTANCE &hInst;
	TankData* _tank;
public:
	Tank(HINSTANCE& hInst1,HWND& hWnd1):hWnd(hWnd1),hInst(hInst1){

	}

	TankData* getData() {
		return _tank;
	}
	
	virtual void draw();

	virtual void readData(GameData& newtank) {
		_tank = (TankData*)&newtank;
	}
};