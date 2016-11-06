#pragma once
#include"GameData.h"
class GraphicUnit {
public:
	virtual void draw()=0;
	virtual void readData(GameData&) = 0;
};