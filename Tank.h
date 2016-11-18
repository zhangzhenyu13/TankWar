#pragma once
#include<windows.h>
#include"GraphicUnit.h"
#include"TankData.h"
class Tank:public GraphicUnit{
	HWND* pWnd;
	HINSTANCE *pInst;
	HDC* pDC,*pDCObj;
	TankData* _tank;
	std::string tankname;
public:
	void setHandle(HWND* hWnd1,HINSTANCE* hInst1){
		this->pInst = hInst1;
		this->pWnd = hWnd1;
	}
	void setDC(HDC* hdc1,HDC*hdc2) {
		pDC = hdc1;
		pDCObj = hdc2;
	}
	
	std::string getName() {
		return tankname;
	}
	virtual void draw();

	virtual void readData(GameData* newtank) {
		_tank = dynamic_cast<TankData*>(newtank);
	}
};