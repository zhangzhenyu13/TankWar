#pragma once
#include<windows.h>
#include"GraphicUnit.h"
#include"TankData.h"
class Tank:public GraphicUnit{
	HDC hdc;
	TankData* _tank;
public:
	Tank(HDC& hdc1):hdc(hdc1) {}
	virtual void draw();
protected:
	virtual void readData(GameData&) {}
};