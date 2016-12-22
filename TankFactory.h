#pragma once

#include<queue>
#include"TankData.h"
class TankFactory {
private:
	std::queue<TankData*> tankBuf;
	int team;
public:
	TankFactory(int team) {
		this->team=team;
	}
	TankData* Retrieve(const POINT& p) {
		
		if (tankBuf.empty() == false) {
			TankData* atank = tankBuf.front();
			atank->setTeam(team);
			tankBuf.pop();
			atank->setPos(p);
			return atank;
		}
		
		return nullptr;
	}
	void Produce(int n) {

		for (int i = 0; i<n; i++) {
			tankBuf.push(new TankData());
		}
	}
};