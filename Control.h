#pragma once
class Control {
public:
	virtual void fire(TankData* newtank) {
		if(newtank->getfireflag())
			return;
		newtank->changefireflag(1);
		newtank->changefiredirect();
		switch(newtank->getfiredirect()) {
		//up
		case 'u':
			newtank->writeposfire(newtank->getposx(),newtank->getposy()-10);
			break;
		//left
		case 'l':
			newtank->writeposfire(newtank->getposx()-10,newtank->getposy());
			break;
		//right
		case 'r':
			newtank->writeposfire(newtank->getposx()+10,newtank->getposy());
			break;
		//down
		case 'd':
			newtank->writeposfire(newtank->getposx(),newtank->getposy()+10);
			break;
		default:
			break;
		}
	}
	virtual void move(WPARAM wParam, TankData* newtank) {
		switch(wParam) {
		case VK_DOWN:
			newtank->changeposy(newtank->getposy()+5);
			newtank->changedirect('d');
			break;
		case VK_LEFT:
			newtank->changeposx(newtank->getposx()-5);
			newtank->changedirect('l');
			break;
		case VK_UP:
			newtank->changeposy(newtank->getposy()-5);
			newtank->changedirect('u');
			break;
		case VK_RIGHT:
			newtank->changeposx(newtank->getposx()+5);
			newtank->changedirect('r');
			break;
		default:
			break;
		}
	}
};
