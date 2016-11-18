#pragma once
#include<string>
class GameData{
public :
	virtual std::string getName() = 0;
	virtual GameData* ReadData() { return NULL; };
	virtual void WriteData(GameData&) {};
};
