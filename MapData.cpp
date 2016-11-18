#include"MapData.h"
#include"CommonFunc.h"
using namespace std;
void MapData::generateMap(std::vector<Brick>& data) {
	Brick brick;
	brick.health = 10000;
	brick.style = 1;
	int x, y;
	//up
	x = 0;
	y = -10;
	brick.rect = { x,y,x + 1208,y + 10 };
	data.push_back(brick);
	//left
	x = -10;
	y = 0;
	brick.rect = { x,y,x + 10,y + 720 };
	data.push_back(brick);
	//down
	x = 0;
	y = 700;
	brick.rect = { x,y,x + 1208,y + 10 };
	data.push_back(brick);
	//right
	x = 1200;
	y = 0;
	brick.rect = { x,y,x + 10,y + 720 };
	data.push_back(brick);
}
//map of stages
//stage 1
bool MapData1::interset(RECT rect) {
	RECT inrect;
	for (int i = 0; i < data.size(); i++) {
		if (IntersectRect(&inrect,&data[i].rect,&rect))
			return true;
	}
	return false;
}



void MapData1::generateMap() {
	MapData::generateMap(data);
	Brick brick;
	int x, y;
	//T
	for (int i = 0; i < 5; i++) {
		x = 60 + i * 50; 
		y = 60;
		brick.rect = {x,y,x+50,y+50};
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 5; i++) {
		x = 160;
		y = 110 + i * 50;
		brick.rect = {x,y,x+50,y+50};
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	//A
	for (int i = 0; i < 2; i++) {
		x = 420 + i * 50;
		y = 60;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 210;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	
	for (int i = 0; i < 6; i++) {
		x = 370;
		y = 60+i*50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 520;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	//N
	for (int i = 0; i < 6; i++) {
		x = 630;
		y = 60 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 780;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 680;
		y = 60 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 730;
		brick.rect = { x,y+150,x + 50,y + 200};
		data.push_back(brick);
	}
	//K
	for (int i = 0; i < 6; i++) {
		x = 890;
		y = 60 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 940+i*50;
		y = 110;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 210;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
}

