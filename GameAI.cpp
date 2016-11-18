#include"GameAI.h"

using namespace std;

void GameAI::Handle(bool timer) {
	
	//operation response

	tankMove();
	fireMove();
}
//
void GameAI::tankMove() {
	Control* C = control[0];
	MapData* map1 = map[stage-1];
	TankData* tank1=NULL;
	
	for (int i = 0;i<tank.size(); i++) {
		tank1 = tank[i];
		tank1->tankPos((C->Move()));
		if (C->Fire() > 0) {
			Bullet* b = new Bullet(tank1->fire(), tank1->gesDirect());
			fire.push_back(b);
			glayout->addGraphicUnit(b);
		}

		int x = tank1->Xpos(), y = tank1->Ypos();
		RECT rect = { x,y,x + 50,y + 50 };
		if (map1->interset(rect) != 0)
			tank1->stepback();
	}
}
//
void GameAI::fireMove() {
	MapData* map1 = map[0];

	for (int i = 0; i < fire.size(); i++) {
		fire[i]->Move();
		if (fire[i]->Xpos()<3 || fire[i]->Ypos()<0 || fire[i]->Ypos()>719 || fire[i]->Xpos()>1204) {
			
			glayout->deleteGraphicUnit(fire[i]);
			std::vector<Bullet*>::iterator it = fire.begin() + i;
			fire.erase(it);
			break;
		}

		for (int j = 0; j < map1->size(); j++) {
			Brick brick = map1->getPos(j);
			RECT bulletrect = { fire[i]->Xpos()- 2, fire[i]->Ypos() - 2, fire[i]->Xpos() + 2, fire[i]->Ypos() + 2 };
			RECT rt;
			if (IntersectRect(&rt, &brick.rect, &bulletrect)) {
				switch (brick.style) {
				case 1: //ordinary brick
				{
					if (map1->deleteBrick(j, fire[i]->power())) {
						//delete the bullet
						glayout->deleteGraphicUnit(fire[i]);
						std::vector<Bullet*>::iterator it = fire.begin() + i;
						fire.erase(it);
					}
					break;
				}
				case 3: //iron brick
				{
					if (map1->deleteBrick(j, fire[i]->power())) {
						//delete the bullet
						glayout->deleteGraphicUnit(fire[i]);
						std::vector<Bullet*>::iterator it = fire.begin() + i;
						fire.erase(it);
					}
					break;
				}
				default:
					break;
				}
				break;
			}
		}
	}

}