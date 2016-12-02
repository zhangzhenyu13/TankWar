#pragma once
#include<windows.h>
#include<ctime>
#include"TankData.h"
#include"MapData.h"

class Robot{
private:
	static int hcode;
	MapData* _map;
	std::vector<TankData*>* _tank;
	int num;
protected:
	WPARAM AI1();
	WPARAM AI2();
public:
	Robot():num(hcode++){}
	WPARAM getNextAct(int k=1){
		if(k==1)
			return AI1();
		if(k==2)
			return AI2();
		
	}
	void ShareData(MapData* map,std::vector<TankData*>* tank){
		_map=map;
		_tank=tank;
	}
	
};
