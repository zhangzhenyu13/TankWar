#pragma once
#include<windows.h>
#include"Direction.h"
//
class Control {
	Direction direct;
	int bullet;
public:
	Control():direct(KEEP),bullet(0) {}
	virtual int Fire() {
		return bullet;
	}
	virtual Direction Move() {
		return direct;
	}
	void keep() { 
		direct = KEEP; 
		bullet = 0;
	}
	virtual void Input(WPARAM wParam) {
		direct = KEEP;
		switch(wParam) {
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
		if (wParam == VK_SPACE)
			bullet = 1;
		else
			bullet = 0;
	}
};
