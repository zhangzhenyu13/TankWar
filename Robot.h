#pragma once
#include<windows.h>
#include<ctime>
#include"TankData.h"
#include"MapData.h"

class Robot{
private:
	
	MapData* _map;
	std::vector<TankData*>* _tank;
	int num;
protected:
	WPARAM AI1();
	WPARAM AI2();
	WPARAM AI3();
public:
	static int hcode;
	bool enabled;
	Robot():num(hcode++),enabled(true){}
	WPARAM getNextAct(int k=1){
		if (k == 1)
			return AI1();
		else if (k == 2)
			return AI2();
		else if (k == 3)
			return AI3();
		//default
		return AI1();
	}
	void ShareData(MapData* map,std::vector<TankData*>* tank){
		_map=map;
		_tank=tank;
	}
	
};
