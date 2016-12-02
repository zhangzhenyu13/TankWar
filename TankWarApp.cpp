#include"TankWarApp.h"

/*

GameSketch : MCV
720p screen utility
GameInput-->GameAIHandle-->GameDraw
in WndProc as
case WM_PAINT, case WM_KEYDOWN
*/

static TankFactory tkfc;
static HINSTANCE hInst;
static Control* Input;
static std::vector<Control*> options;
static Robot* robot;

static TankData* tankData;
static MapData* mapData;
static GameAI* RuleAI;
static GraphicUnit *tank, *map;
static GraphicLayout* Layout;
BOOLEAN InitData(HWND& hWnd) {
	Layout = new GraphicLayout(hWnd, hInst);
	RuleAI = new GameAI();
//map
	mapData = new MapData1();
	RuleAI->addMap(mapData);
	map = new Map();
	map->readData(mapData);
	Layout->addGraphicUnit(map);
//tank	
	RECT rctA={0,300,1200,700};
	for (int i = 0; i < 15; i++) {
		tankData = tkfc.Retrieve(RuleAI->properPos(rctA));
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

//	
	Layout->Init();
	RuleAI->setGraph(Layout);
//gamestart
	RuleAI->BeginGame();

	return TRUE;
}


BOOLEAN Release() {
	
	//releasedata

	delete RuleAI;

	delete Layout;

	return TRUE;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOLEAN CALLBACK SelectModeProc(HWND, UINT, WPARAM, LPARAM);
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
	
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,20,NULL);
		break;
	case WM_PAINT:
		Layout->RefreshWnd(hWnd);
		Layout->Init();
		Layout->draw();
		break;
	case WM_KEYDOWN:
		Input->Input(wParam);
		//RuleAI->Handle();
		//InvalidateRect(hWnd,NULL,FALSE);
		break;
	case WM_KEYUP:
		Input->Keep();
		//RuleAI->Handle();
		//InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		//flash
		
		for(int i=0;i<options.size();i++)
			options[i]->CoolDown();
	//	for(int i=0;i<players.size();i++)
	//		options[i]->Input(players[i]->getNextAct());
		if(RuleAI->Handle()==LOSER){
			MessageBox(NULL,L"GAME OVER",L"TIPS",MB_OK);
		    SendMessage(hWnd,WM_DESTROY,wParam,lParam);
		}
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case GAME_EXIT:
			PostQuitMessage(0);
			KillTimer(hWnd, 1);
			break;
		case GAME_NEW:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SELECTMODE), hWnd, (DLGPROC)SelectModeProc);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
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
		1208, 720,//720p gameGraphic
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

BOOLEAN CALLBACK SelectModeProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			DestroyWindow(hWnd);
			break;
		case IDCANCEL:
			break;
		}
		break;
	case WM_INITDIALOG:
		SetWindowText(hWnd,L"SELECT GAME MODE");
		break;
	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	return TRUE;
}