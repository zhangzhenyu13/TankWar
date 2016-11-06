#pragma once
class GameData{
public :
	virtual GameData* ReadData() = 0;
	virtual void WriteData(GameData&) = 0;
};