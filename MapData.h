#pragma once
#include<vector>
#include"GameData.h"
#include<windows.h>
struct Brick{
	RECT rect;
	char style;//1:normal,2:bonus,3:iron
};
class MapData1 :public GameData {
	MapData1* _map;
	std::vector<Brick> data;
protected:
	virtual void generateMap();
public:
	virtual GameData* ReadData() {
		return _map;
	}
	MapData1() { generateMap(); }
	virtual void WriteData(GameData&) {}
	int size() { return data.size(); }
	Brick getPos(int i) {
		
		return data[i];
	
	}
};
class MapData2 :public MapData1 {

};