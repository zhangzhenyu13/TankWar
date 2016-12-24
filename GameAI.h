#pragma once
#include"GraphicLayout.h"
#include"MapData.h"
#include"TankData.h"
#include"Control.h"
#include"TankData.h"
#include"MapData.h"
#include"Bullet.h"
#include"Robot.h"
#include<vector>
#include<fstream>
using namespace std;
const int onShow = 5;
enum GameResult
{
	WINNER,LOSER,COMEON
};
class GameAI {
private:
	bool playerdied;
	int playerRank;
	char level;
	std::vector<TankData*> tank;
	MapData* map;
	std::vector<Control*> control;
	std::vector<Robot*> player;
	std::vector<Bullet*> fire;
	GraphicLayout* glayout;
	RECT myArea, pcArea;
public :
	GameAI() {level = 1; playerdied = false; playerRank = 1; }
	Control* getPlayerInput() {
		return control[playerRank];
	}
	void setGraph(GraphicLayout* g) {
		glayout = g;
	}
	void setArea(RECT rect1,RECT rect2) {//upArea,downArea of the screen
		myArea = rect2;
		pcArea = rect1;
	}
	void setDifficulty(int r) {
		level = r;
	}
	void addControl(Control* C) {
		control.push_back(C);
	}
	void addPlayer(Robot* rb){
		player.push_back(rb);
	}
	virtual GameResult Handle(bool timer=false);
	void addMap(MapData* gm) {
		map=gm;
	}
	void addTank(TankData* gt) {
		tank.push_back(gt);
	}
	void addBullet(Bullet *gb) {
		fire.push_back(gb);
	}

	//
	void BeginGame();
	void EndGame() {
		glayout->showStartUP = 2;
	}
	~GameAI(){
		for(int i=tank.size()-1;i>=0;i--){
			delete tank[i];
		}
			delete map;
		for(int i=control.size()-1;i>=0;i--){
			delete control[i];
		}
		for(int i=player.size()-1;i>=0;i--){
			delete player[i];
		}
	}
	POINT properPos(RECT Area);
	void SaveData(wstring );
protected:
	int countLevel();
	void fireMove();
	void tankMove();

};
