#include"TankWarApp.h"
#include"SelectMode.h"
#include<fstream>
using namespace std;

/*

GameSketch : MCV
720p screen utility
GameInput-->GameAIHandle-->GameDraw
in WndProc as
case WM_PAINT, case WM_KEYDOWN
*/
SelectData myMode;
wstring path = L"userfile\\";
wstring username;
wstring password;
static TankFactory *mytkfc,*pctkfc;
static HINSTANCE hInst;
static Control* Input;
static std::vector<Control*> options;
static Robot* robot;
static TankData* tankData;
static MapData* mapData;
static GameAI* RuleAI;
static GraphicUnit *tank, *map;
static GraphicLayout* Layout;
static StatusWnd * Status;
static StartUpWnd *Startwnd;

BOOLEAN InitData(HWND& hWnd) {
	mytkfc = new TankFactory(2);
	pctkfc = new TankFactory(1);
	mytkfc->Produce(myMode.gamePlayer);
	pctkfc->Produce(myMode.gamePlayer);
	//
	Robot::hcode = 0;
	Layout = new GraphicLayout(hWnd, hInst);
	RuleAI = new GameAI();
	Status=new StatusWnd();
	Startwnd = new StartUpWnd();
	Layout->addGraphicUnit(Status);
	Layout->addStatusZone(Status);
	Layout->addGraphicUnit(Startwnd);
	Layout->addStartUp(Startwnd);
//map
	mapData = new MapData1(myMode.gameStage);
	RuleAI->addMap(mapData);
	map = new Map();
	map->readData(mapData);
	Layout->addGraphicUnit(map);
//tank	
	RECT rctA={0,0,1200,200};
	RECT rctB={0,500,1200,700};
	RuleAI->setArea(rctA,rctB);
	for (int i = 0; i < myMode.gamePlayer; i++) {
		//A
		tankData = pctkfc->Retrieve(RuleAI->properPos(rctA));
		Input = new Control();
		robot=new Robot();
		options.push_back(Input);
		
		RuleAI->addPlayer(robot);
		RuleAI->addTank(tankData);
		RuleAI->addControl(Input);
		//
		tank = new Tank();
		tank->readData(tankData);
		Layout->addGraphicUnit(tank);
		//B
		tankData = mytkfc->Retrieve(RuleAI->properPos(rctB));
		Input = new Control();
		robot=new Robot();
		options.push_back(Input);
		
		RuleAI->addPlayer(robot);
		RuleAI->addTank(tankData);
		RuleAI->addControl(Input);
		//
		tank = new Tank();
		tank->readData(tankData);
		Layout->addGraphicUnit(tank);
	}
	//for man's control
	//options.pop_back();
	//players.pop_back();
	//Input=options[0];
//	
	Layout->Init();
	RuleAI->setGraph(Layout);
//gamestart
	RuleAI->setDifficulty(myMode.gameLevel);
	//RuleAI->BeginGame();
	//MessageBox(NULL,L"yes",L"info",0);
	return TRUE;
}

BOOLEAN ContinueGame(HWND& hWnd, wstring filename) {
	mytkfc = new TankFactory(2);
	pctkfc = new TankFactory(1);
	Robot::hcode = 0;
	Layout = new GraphicLayout(hWnd, hInst);
	RuleAI = new GameAI();
	Status = new StatusWnd();
	Startwnd = new StartUpWnd();
	Layout->addGraphicUnit(Status);
	Layout->addStatusZone(Status);
	Layout->addGraphicUnit(Startwnd);
	Layout->addStartUp(Startwnd);

	//tank
	wfstream file;
	file.open(filename, ios::in);
	file.seekp(20, ios::beg);
	int x, y, team, level;
	file >> x;
	while (x != 11457680) {
		file >> y >> team >> level;
		tankData = new TankData(x, y, team, level);

		Input = new Control();
		robot = new Robot();
		options.push_back(Input);

		RuleAI->addPlayer(robot);
		RuleAI->addTank(tankData);
		RuleAI->addControl(Input);
		//
		tank = new Tank();
		tank->readData(tankData);
		Layout->addGraphicUnit(tank);

		file >> x;
	}

	//map
	mapData = new MapData1(myMode.gameStage);
	while (mapData->size() > 4) {
		mapData->deleteBrick(4, 999);
	}
	int count;
	file >> count;
	for (int i = 0; i < count; i++) {
		int left, top, style, health;
		file >> left >> top >> style >> health;
		RECT rect = { left, top, left + 50, top + 50 };
		Brick brick;
		brick.rect = rect;
		brick.style = style;
		brick.health = health;
		mapData->addBrick(brick);
	}
	RuleAI->addMap(mapData);
	map = new Map();
	map->readData(mapData);
	Layout->addGraphicUnit(map);

	Layout->Init();
	RuleAI->setGraph(Layout);

	//gamestart
	file >> level;
	RuleAI->setDifficulty(level);

	return TRUE;
}

BOOLEAN Release() {
	
	//releasedata
	options.clear();
	delete mytkfc;
	delete pctkfc;
	delete RuleAI;
	delete Layout;

	return TRUE;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!InitWindowClass(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"创建窗口失败!", _T("创建窗口"), NULL);
		return 1;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	Release();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GameResult grt=COMEON;
	wfstream file;
	switch (message)
	{
	case WM_CREATE:
		//SetTimer(hWnd,1,20,NULL);
		break;
	case WM_PAINT:
		Layout->RefreshWnd(hWnd);
		Layout->Init();
		Layout->draw();
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			KillTimer(hWnd, 1);
			MessageBox(NULL, L"Pause", L"Pause", MB_OK);
			SetTimer(hWnd, 1, 20, NULL);
		}
		Input = RuleAI->getPlayerInput();
		Input->Input(wParam);
		//RuleAI->Handle();
		//InvalidateRect(hWnd,NULL,FALSE);
		break;
	case WM_KEYUP:
		if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT)
			Input->Keep();
		//RuleAI->Handle();
		//InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		//flash
		
		for(int i=0;i<options.size();i++)
			options[i]->CoolDown();
		
		if((grt = RuleAI->Handle()) != COMEON){
			KillTimer(hWnd,1);
			InvalidateRect(hWnd,NULL,FALSE);
			if(grt==WINNER)
			   MessageBox(NULL,L"WINNER",L"GAME OVER",MB_OK);
			else
			   MessageBox(NULL,L"LOSER",L"GAME OVER",MB_OK);
		    //SendMessage(hWnd,WM_DESTROY,wParam,lParam);
		}
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case GAME_EXIT:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			break;
		case GAME_NEW:
			if (DialogBox(hInst, (LPCWSTR)IDD_DIALOG_SelectMode, NULL, SelectModeProc))
			{
				KillTimer(hWnd,1);
				Release();
				InitData(hWnd);
				RuleAI->BeginGame();
				SetTimer(hWnd, 1, 20, NULL);
				InvalidateRect(hWnd,NULL,FALSE);
			}
			else
				;
				
			break;
		case GAME_LOG:
			DialogBox(hInst, (LPCWSTR)IDD_DIALOG_LOGIN, NULL, LogInProc);
			path = L"userfile\\";
			path += username;
			if (path.length() == 9)
				path += L"passenger.txt";
			else
				path += L".tankUser";
			break;
		case GAME_SAVE:
			if (path.length() == 9) {
				path += L"passenger.txt";
				file.open(path, ios::out);
			}
			RuleAI->SaveData(path);
			break;
		case GAME_CONTINUE:
			KillTimer(hWnd, 1);
			if (path.length() == 9)
				path += L"passenger.txt";
			Release();
			ContinueGame(hWnd, path);
			RuleAI->BeginGame();
			SetTimer(hWnd, 1, 20, NULL);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case GAME_ABOUT:
			KillTimer(hWnd, 1);
			MessageBox(NULL, L"TankWar\nDeveloped by\n	Zhang Zhenyu\n	Liu Ziteng\n	Zhang Shuowen\n	Hou Bonan", L"ABOUT", MB_OK);
			SetTimer(hWnd, 1, 20, NULL);
			break;
		case GAME_HELP:
			KillTimer(hWnd, 1);
			MessageBox(NULL, L"Press UP/DOWN/LEFT/RIGHT to move\nPress SPACE to fire\nPress ESC to pause", L"HELP", MB_OK);
			SetTimer(hWnd, 1, 20, NULL);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		Release();
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = L"TankWarApp";
	TCHAR szTitle[] = L"TankWarApp";
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCE(MY_MENU);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return FALSE;
	hWnd = CreateWindowW(
		szWindowClass,
		szTitle,
		WS_CAPTION,
		0, 0,
		1400, 750,//720p gameGraphic
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
		return FALSE;
	//
	hInst = hInstance;
	InitData(hWnd);
	//
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
