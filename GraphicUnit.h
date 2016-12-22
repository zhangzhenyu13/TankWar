#pragma once
#include<windows.h>

#include<string>
#include"GameData.h"

#include"resource.h"
#include"Direction.h"
//GDI
#include<gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
#include <comdef.h>
class GraphicUnit {
public:
	virtual void draw()=0;
	virtual void readData(GameData*) = 0;
	virtual GameData* getData() { return NULL; }
	virtual std::string getName()=0;
	virtual void setDC(HDC*,HDC*) = 0;
	virtual void setHandle(HWND* hWnd,HINSTANCE* hInst) = 0;
	virtual ~GraphicUnit(){}
};