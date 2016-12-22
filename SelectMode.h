#include<windows.h>
struct SelectData {
	static const int MAXPlayer = 30,MAXLevel=3,MAXDif=3;
	int gameLevel;
	int gameStage;
	int gamePlayer;
	SelectData() :gameStage(1),gameLevel(1),gamePlayer(1){}
} ;
BOOL CALLBACK SelectModeProc(HWND, UINT, WPARAM, LPARAM);