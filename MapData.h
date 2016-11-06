#pragma once
#include"GameData.h"
class MapData :public GameData {
	MapData* _map;
public:
	virtual GameData* ReadData() {
		return _map;
	}
	virtual void WriteData(GameData&) {}
};
