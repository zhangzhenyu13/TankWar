#include"Robot.h"

int Robot::hcode=0;
WPARAM Robot::AI1(){
		srand(time(NULL)%11110123+num);

		WPARAM K;
		switch(rand()%5){
		case 0:
			K=VK_LEFT;
			break;
		case 1:
			K=VK_RIGHT;
			break;
		case 2:
			K=VK_UP;
			break;
		case 3:
			K=VK_DOWN;
			break;
		case 4:
			K=VK_SPACE;
			break;
		}

		return K;

	}
	WPARAM Robot::AI2(){
		
		std::vector<TankData*> tank = *_tank;
		if(!tank[num]->isAlive())
			return NULL;
		if(abs(tank[num]->Xpos() - tank[tank.size()-1]->Xpos()) < 25 || abs(tank[num]->Ypos() - tank[tank.size()-1]->Ypos()) < 25)
			if((tank[num]->Xpos() - tank[tank.size()-1]->Xpos() > 0 && tank[num]->gesDirect() == LEFT) ||
				(tank[num]->Xpos() - tank[tank.size()-1]->Xpos() < 0 && tank[num]->gesDirect() == RIGHT) ||
				(tank[num]->Ypos() - tank[tank.size()-1]->Ypos() > 0 && tank[num]->gesDirect() == UP) ||
				(tank[num]->Ypos() - tank[tank.size()-1]->Ypos() < 0 && tank[num]->gesDirect() == DOWN) )
				if(rand()%2 == 1)
					return VK_SPACE;

		RECT irect;
		bool flag = false;
		RECT mrect = tank[num]->getPos();
		switch(tank[num]->moveDirect()) {
		case UP:
			mrect.bottom -= 5;
			mrect.top -= 5;
			for(int i = 0; i < tank.size() - 1; i++)
				if(tank[i]->isAlive() && i != num)
					if(IntersectRect(&irect, &tank[i]->getPos(), &mrect))
						flag = true;
			if(_map->interset(mrect) || flag) {
				if(tank[num]->Xpos() > 600 && rand()%5 != 1)
					return VK_LEFT;
				else
					return VK_RIGHT;
			}
			return VK_UP;
			break;
		case DOWN:
			mrect.bottom += 5;
			mrect.top += 5;
			for(int i = 0; i < tank.size() - 1; i++)
				if(tank[i]->isAlive() && i != num)
					if(IntersectRect(&irect, &tank[i]->getPos(), &mrect))
						flag = true;
			if(_map->interset(mrect) || flag) {
				if(tank[num]->Xpos() > 600 && rand()%5 != 1)
					return VK_LEFT;
				else
					return VK_RIGHT;
			}
			return VK_DOWN;
			break;
		case LEFT:
			mrect.left -= 5;
			mrect.right -= 5;
			for(int i = 0; i < tank.size() - 1; i++)
				if(tank[i]->isAlive() && i != num)
					if(IntersectRect(&irect, &tank[i]->getPos(), &mrect))
						flag = true;
			if(_map->interset(mrect) || flag) {
				if(tank[num]->Ypos() > 600 && rand()%5 != 1)
					return VK_UP;
				else
					return VK_DOWN;
			}
			return VK_LEFT;
			break;
		case RIGHT:
			mrect.left += 5;
			mrect.right += 5;
			for(int i = 0; i < tank.size() - 1; i++)
				if(tank[i]->isAlive() && i != num)
					if(IntersectRect(&irect, &tank[i]->getPos(), &mrect))
						flag = true;
			if(_map->interset(mrect) || flag) {
				if(tank[num]->Ypos() > 600 && rand()%5 != 1)
					return VK_UP;
				else
					return VK_DOWN;
			}
			return VK_RIGHT;
			break;
		default:
			WPARAM K;
			int a = rand()%4;
			switch(a){
			case 0:
				K=VK_LEFT;
				break;
			case 1:
				K=VK_RIGHT;
				break;
			case 2:
				K=VK_UP;
				break;
			case 3:
				K=VK_DOWN;
				break;
			}
			return K;
			break;
		}
	}