#pragma once
#include"GameData.h"
#include<vector>
#include<windows.h>
struct Brick{
	RECT rect;
	char style;//1:normal,2:bonus,3:iron
	char health;//amount vary from 
};
class MapData :public GameData {

protected:
	virtual void generateMap()=0;
	void generateMap(std::vector<Brick>&data);
public:
	virtual int size() = 0;
	virtual Brick getPos(int i) = 0;
	void draw() {}
	virtual bool interset(RECT)=0;
	virtual bool deleteBrick(int i,int damage=1) = 0;
};
class MapData1 :public MapData {
	
	std::vector<Brick> data;
	std::string mapname;
protected:
	void generateMap();
public:
	
	std::string getName() {
		return mapname;
	}
	MapData1() { generateMap(); }
	bool interset(RECT);
	int size() { return data.size(); }
	Brick getPos(int i) {
		return data[i];
	}
	bool deleteBrick(int i,int damgage=1) {
		if((data[i].health-=damgage)>0) return false;

		std::vector<Brick>::iterator it = data.begin() + i;
		data.erase(it);
		return true;
	}
};
class MapData2 :public MapData1 {

};