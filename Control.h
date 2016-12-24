#pragma once
#include<windows.h>
#include"Direction.h"
#include"StateMachine.h"
//
class Control {
	Direction direct;
	bool isfire;
	char firecooling,movecooling;
	TankAct tAct;
public:
	Control():direct(KEEP),isfire(0),firecooling(0),movecooling(0) {}
	//opt
	virtual TankAct& getAct(){
		tAct.direct=direct;
		tAct.fire=isfire;
		return tAct;
	}
	virtual int Fire() {
		int b1;
		if (firecooling > 0)
			b1 = 0;
		else{
			if(isfire)
			firecooling = 30;
			b1=isfire;
			isfire=0;
		}

		return b1;
	}

	virtual Direction Move() {
		return direct;
	}
	//input
	virtual void InputF(WPARAM wParam){
	//fire
	if (wParam == VK_SPACE) 
		isfire = 1;
	}
	virtual void InputM(WPARAM wParam) {
		//move
		//Direction d = direct;
			switch (wParam) {
			case VK_DOWN:
				direct = DOWN;
				break;
			case VK_LEFT:
				direct = LEFT;
				break;
			case VK_UP:
				direct = UP;
				break;
			case VK_RIGHT:
				direct = RIGHT;
				break;
			default:
				break;
			}
	}
	void Input(WPARAM wParam){
		InputM(wParam);
		InputF(wParam);
	}
	//cooling
	void CoolDown() {
		if (--firecooling > 0) {
			isfire = 0;
		}
		
	}
	//stop
	void Keep() {
		direct = KEEP;
	}
};
