#include"MapData.h"
#include"CommonFunc.h"
using namespace std;
void MapData::generateMap(std::vector<Brick>& data) {
	Brick brick;
	brick.health = 100000;
	brick.style = 1;
	int x, y;
	RECT rt;
	//up
	x = 0;
	y = -20;
	rt.left=x;rt.top=y;rt.right=x+1200;rt.bottom=y+20;
	
	brick.rect = rt;
	data.push_back(brick);
	//left
	x = -20;
	y = 0;
	rt.left=x;rt.top=y;rt.right=x+20;rt.bottom=y+750;
	brick.rect = rt;
	data.push_back(brick);
	//down
	x = 0;
	y = 750;
	rt.left=x;rt.top=y;rt.right=x+1200;rt.bottom=y+20;
	brick.rect = rt;
	data.push_back(brick);
	//right
	x = 1200;
	y = 0;
	rt.left=x;rt.top=y;rt.right=x+20;rt.bottom=y+750;
	brick.rect = rt;
	data.push_back(brick);
}
//map of stages
//stage 1
bool MapData1::interset(RECT rect) {
	RECT inrect;
	for (int i = 0; i < data.size(); i++) {
		if (IntersectRect(&inrect,&data[i].rect,&rect))
			return true;
		if(rect.top < 0 || rect.bottom > 700 || rect.left < 0 || rect.right > 1200)
			return true;
	}
	return false;
}

void MapData1::method1() {
	Brick brick;
	brick.health = 6;
	brick.style = 1;
	RECT rt;
	int x, y;
	//T
	for (int i = 0; i < 5; i++) {
		x = 50 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 150;
		y = 100 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	//A
	for (int i = 0; i < 2; i++) {
		x = 400 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 150;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}

	for (int i = 0; i < 5; i++) {
		x = 350;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 500;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	//N
	for (int i = 0; i < 5; i++) {
		x = 600;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 800;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 650 + i * 50;
		y = 100 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//K
	for (int i = 0; i < 5; i++) {
		x = 900;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			x = 950;
			y = 150;
			brick.rect = { x,y,x + 50,y + 50 };
			brick.health = 5;
			brick.style = 1;
			data.push_back(brick);
		}
		else
			x = 950 + i * 50;
		y = 150 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 150 - i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}

}
void MapData1::method2() {
	Brick brick;
	brick.health = 6;
	brick.style = 1;
	RECT rt;
	int x, y;
	//T
	for (int i = 0; i < 5; i++) {
		x = 50 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 150;
		y = 100 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	//A
	for (int i = 0; i < 2; i++) {
		x = 400 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 150;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}

	for (int i = 0; i < 5; i++) {
		x = 350;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 500;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	//N
	for (int i = 0; i < 5; i++) {
		x = 600;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		x = 800;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 650 + i * 50;
		y = 100 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//K
	for (int i = 0; i < 5; i++) {
		x = 900;
		y = 50 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			x = 950;
			y = 150;
			brick.rect = { x,y,x + 50,y + 50 };
			brick.health = 5;
			brick.style = 1;
			data.push_back(brick);
		}
		else
			x = 950 + i * 50;
		y = 150 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
		y = 150 - i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		data.push_back(brick);
	}

	//Middle Line
	for (int i = 0; i < 4; i++) {
		x = 50 + i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 1050 - i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 250 + i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 3;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 850 - i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 3;
		data.push_back(brick);
	}
	for (int i = 0; i < 5; i++) {
		x = 450 + i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//Square
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i*j != 1) {
				x = 50 + i * 50;
				y = 450 + j * 50;
				brick.rect = { x,y,x + 50,y + 50 };
				brick.health = 5;
				brick.style = 1;
				data.push_back(brick);
			}

		}

	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i*j != 1) {
				x = 250 + i * 50;
				y = 450 + j * 50;
				brick.rect = { x,y,x + 50,y + 50 };
				brick.health = 5;
				brick.style = 1;
				data.push_back(brick);
			}

		}

	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i*j != 1) {
				x = 1050 - i * 50;
				y = 450 + j * 50;
				brick.rect = { x,y,x + 50,y + 50 };
				brick.health = 5;
				brick.style = 1;
				data.push_back(brick);
			}

		}

	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i*j != 1) {
				x = 850 - i * 50;
				y = 450 + j * 50;
				brick.rect = { x,y,x + 50,y + 50 };
				brick.health = 5;
				brick.style = 1;
				data.push_back(brick);
			}

		}

	}

	//Home
	for (int i = 0; i < 5; i++) {
		x = 450 + i * 50;
		y = 500;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 450;
		y = 550 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 650;
		y = 550 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//Line
	for (int i = 0; i < 7; i++) {
		x = 400 + i * 50;
		y = 450;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 3;
		data.push_back(brick);
	}
}

void MapData1::method3() {
	Brick brick;
	int x, y;
	//ÓÒÐ±
	for (int i = 0; i < 11; i++) {
		x = 250 + i * 50;
		y = 550 - i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 11; i++) {
		x = 350 + i * 50;
		y = 600 - i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 2; i++) {
		x = 250 + i * 50;
		y = 600;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 2; i++) {
		x = 800 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	//×óÐ±
	for (int i = 0; i < 12; i++) {
		if (i != 5 && i != 6) {
			x = 300 + i * 50;
			y = 50 + i * 50;
			brick.rect = { x,y,x + 50,y + 50 };
			brick.health = 5;
			brick.style = 1;
			data.push_back(brick);
		}
	}
	for (int i = 0; i < 12; i++) {
		if (i != 6 && i != 7) {
			x = 200 + i * 50;
			y = 50 + i * 50;
			brick.rect = { x,y,x + 50,y + 50 };
			brick.health = 5;
			brick.style = 1;
			data.push_back(brick);
		}
	}
	for (int i = 0; i < 12; i++) {
		if (i != 5 && i != 6) {
			x = 250 + i * 50;
			y = 50 + i * 50;
			brick.rect = { x,y,x + 50,y + 50 };
			brick.health = 5;
			brick.style = 1;
			data.push_back(brick);
		}
	}

	//Home
	for (int i = 0; i < 3; i++) {
		x = 500 + i * 50;
		y = 560;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 1; i++) {
		x = 500;
		y = 610 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 1; i++) {
		x = 600;
		y = 610 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//×ó²à
	for (int i = 0; i < 3; i++) {
		x = 0 + i * 50;
		y = 250;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 0 + i * 50;
		y = 300;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 0 + i * 50;
		y = 350;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 3; i++) {
		x = 0 + i * 50;
		y = 400;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//ÉÏ²à
	for (int i = 0; i < 4; i++) {
		x = 450 + i * 50;
		y = 0;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 450 + i * 50;
		y = 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//ÓÒ²à
	for (int i = 0; i < 4; i++) {
		x = 1000;
		y = 250 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 1050;
		y = 250 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 1100;
		y = 250 + i * 50;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 5;
		brick.style = 1;
		data.push_back(brick);
	}

	//ÌúÇ½
	for (int i = 0; i < 4; i++) {
		x = 0 + i * 50;
		y = 150;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 99;
		brick.style = 3;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 0 + i * 50;
		y = 500;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 99;
		brick.style = 3;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 950 + i * 50;
		y = 150;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 99;
		brick.style = 3;
		data.push_back(brick);
	}
	for (int i = 0; i < 4; i++) {
		x = 950 + i * 50;
		y = 500;
		brick.rect = { x,y,x + 50,y + 50 };
		brick.health = 99;
		brick.style = 3;
		data.push_back(brick);
	}
}

void MapData1::generateMap(int r) {
	MapData::generateMap(data);
	switch (r)
	{
	case 1:
		method1();
		break;
	case 2:
		method2();
		break;
	case 3:
		method3();
		break;
	default:
		break;
	}
}