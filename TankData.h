#pragma once
#include"GameData.h"
class TankData :public GameData {
	TankData* _tank;
	char direction, firedirection;
	int posfire[2];
	int posx, posy;
	int fireflag;
public:
	TankData() {
		direction = 'u';
		firedirection = 'u';
		posx = 500;
		posy = 500;
		fireflag = 0;
	}
	virtual GameData* ReadData() {

		return _tank;
	}
	virtual void WriteData(GameData&) {}
	int getposx() {
		return posx;
	}
	int getposy() {
		return posy;
	}
	void changeposx(int x) {
		posx = x;
	}
	void changeposy(int y) {
		posy = y;
	}
	char getdirection() {
		return direction;
	}
	void changedirect(char direct) {
		direction = direct;
	}
	int getfireflag() {
		return fireflag;
	}
	void changefireflag(int flag) {
		fireflag = flag;
	}
	char getfiredirect() {
		return firedirection;
	}
	void changefiredirect() {
		firedirection = direction;
	}
	int* getfirepos() {
		return posfire;
	}
	void writeposfire(int x, int y) {
		posfire[0] = x;
		posfire[1] = y;
	}
};