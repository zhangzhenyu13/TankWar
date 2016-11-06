#pragma once
#include"GameData.h"
class TankData :public GameData {
TankData* _tank;
public:
	virtual GameData* ReadData() {

		return _tank;
	}
	virtual void WriteData(GameData&) {}
};