#pragma once
#include"GameData.h"
#include<vector>
#include<windows.h>
struct Brick{
	RECT rect;
	char style;//1:normal,2:bonus,3:iron
	int health;//amount vary from 
	
	Brick() :style(1),health(1) {
		
	}
};
class MapData :public GameData {

protected:
	void generateMap(std::vector<Brick>&data);
public:
	virtual int size() = 0;
	virtual Brick getPos(int i) = 0;
	void draw() {}
	virtual bool interset(RECT)=0;
	virtual bool deleteBrick(int i,int damage=1) = 0;
	virtual bool addBrick(Brick brick) = 0;
};
class MapData1 :public MapData {//static method to create map
	
	std::vector<Brick> data;
	std::string mapname;
	void method1();
	void method2();
	void method3();
protected:

	void generateMap(int r);
public:
	
	std::string getName() {
		return mapname;
	}
	MapData1(int r) { generateMap(r); }
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
	bool addBrick(Brick brick) {
		data.push_back(brick);
		return true;
	}
};
class MapData2 :public MapData1 {//dynamic method to create map from disk file
	std::vector<Brick> data;
	std::string mapname;
protected:
	void generateMap();
public:
	MapData2():MapData1(0) { generateMap(); }

};