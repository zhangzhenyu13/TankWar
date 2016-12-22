#include"Robot.h"



int Robot::hcode = 0;

WPARAM Robot::AI1() {
	srand(time(NULL) % 11110123 + num);

	WPARAM K = VK_SPACE;
	switch (rand() % 5) {
	case 0:
		K = VK_LEFT;
		break;
	case 1:
		K = VK_RIGHT;
		break;
	case 2:
		K = VK_UP;
		break;
	case 3:
		K = VK_DOWN;
		break;
	case 4:
		K = VK_SPACE;
		break;
	}

	return K;

}
WPARAM Robot::AI2() {

	std::vector<TankData*> tank = *_tank;
	if (tank[num]->isAlive() == false || tank[num]->available == false)
		return NULL;

	RECT enemyrect;
	for (int i = num; i < tank.size(); i++) {
		if (tank[i]->isAlive() && tank[i]->available && tank[i]->getTeam() != tank[num]->getTeam()) {
			enemyrect = tank[i]->getPos();
			break;
		}
		if (i == tank.size() - 1)
			i = -1;
	}

	RECT rt, myrect = tank[num]->getPos();
	TankData* nearTank = nullptr;
	int dx, dy;
	if (IntersectRect(&rt, &enemyrect, &tank[num]->viewArea())) {
		dx = enemyrect.left - myrect.left;
		dy = enemyrect.top - myrect.top;
		if (dx <20 && dx>-20) {
			if (dy > 0 && tank[num]->gesDirect() == DOWN)
				return VK_SPACE;
			else if (dy < 0 && tank[num]->gesDirect() == UP)
				return VK_SPACE;
			else {
				if (dy > 0)
					return VK_DOWN;
				else
					return VK_UP;
			}
		}
		else if (dy< 20 && dy>-20) {
			if (dx > 0 && tank[num]->gesDirect() == RIGHT)
				return VK_SPACE;
			else if (dx < 0 && tank[num]->gesDirect() == LEFT)
				return VK_SPACE;
			else {
				if (dx > 0)
					return VK_RIGHT;
				else
					return VK_LEFT;
			}
		}
		else {
			if (abs(dx) < abs(dy)) {
				if (dx < 0)
					return VK_LEFT;
				else
					return VK_RIGHT;
			}
			else {
				if (dy < 0)
					return VK_UP;
				else
					return VK_DOWN;
			}
		}
	}

	return AI1();
}
WPARAM Robot::AI3() {
	RECT rt, t1, t2;
	int dx = 9999, dy = 9999, newdx, newdy;
	std::vector<TankData*>& tank = *_tank;
	for (int i = 0; i<tank.size(); i++) {
		if (tank[i]->isAlive() == false || tank[i]->available == false)
			continue;
		if (i != num&&tank[i]->getTeam() != tank[num]->getTeam()) {
			t1 = tank[i]->getPos();
			t2 = tank[num]->getPos();
			if (IntersectRect(&rt, &t1, &tank[num]->viewArea())) {
				newdx = (t1.left - t2.left);
				newdy = (t1.top - t2.top);
				if (abs(newdx) + abs(newdy) < abs(dx) + abs(dy)) {
					dx = newdx;
					dy = newdy;
				}
			}
		}
	}
	if (dx != 9999) {
		if (dx <20 && dx>-20) {
			if (dy > 0 && tank[num]->gesDirect() == DOWN)
				return VK_SPACE;
			else if (dy < 0 && tank[num]->gesDirect() == UP)
				return VK_SPACE;
			else {
				if (dy > 0)
					return VK_DOWN;
				else
					return VK_UP;
			}
		}
		else if (dy< 20 && dy>-20) {
			if (dx > 0 && tank[num]->gesDirect() == RIGHT)
				return VK_SPACE;
			else if (dx < 0 && tank[num]->gesDirect() == LEFT)
				return VK_SPACE;
			else {
				if (dx > 0)
					return VK_RIGHT;
				else
					return VK_LEFT;
			}
		}
		else {
			if (abs(dx) < abs(dy)) {
				if (dx < 0)
					return VK_LEFT;
				else
					return VK_RIGHT;
			}
			else {
				if (dy < 0)
					return VK_UP;
				else
					return VK_DOWN;
			}
		}
	}
	return AI1();
}