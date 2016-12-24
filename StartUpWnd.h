#pragma once
#include<windows.h>
#include"GameData.h"
#include"GraphicUnit.h"
class StartUpWnd :public GraphicUnit {
	HWND* pWnd;
	HINSTANCE* pInst;
	HDC* pDC, *pDCObj;
	std::string mapname;
public:
	char mode = 0;//0,1,2
	void setHandle(HWND*hWnd, HINSTANCE*hInst) {
		this->pWnd = hWnd;
		this->pInst = hInst;
	}
	void setDC(HDC* hdc1, HDC* hdc2) {
		pDC = hdc1;
		pDCObj = hdc2;
	}
	virtual void draw();
	std::string getName() { return mapname; }
	virtual void readData(GameData* map) {
		
	}
};