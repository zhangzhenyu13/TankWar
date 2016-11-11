#include"MapData.h"
using namespace std;
void MapData1::generateMap() {
	Brick brick;
	
	for(int i=0;i<6;i++)
		for (int j = 0; j < 12; j++) {
			brick.style = 1;
			//brick.rect = {60+i*20,60+j*20,60+i*20+20,60+j*20+20};
			brick.rect.bottom = 60+j*20+20;
			brick.rect.left = 60+i*20;
			brick.rect.right = 60+i*20+20;
			brick.rect.top = 60+j*20;
			data.push_back(brick);
		}
}