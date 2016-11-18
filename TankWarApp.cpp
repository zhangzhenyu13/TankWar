#include"TankWarApp.h"

/*

GameSketch : MCV
720p screen utility
GameInput-->GameAIHandle-->GameDraw
in WndProc as
case WM_PAINT, case WM_KEYDOWN
*/
ULONG_PTR m_gdiplusToken;

static HINSTANCE hInst;
static Control* Input;
static TankData* tankData;
static MapData* mapData;
static GameAI* RuleAI;
static GraphicUnit *tank, *map;
static GraphicLayout* Layout;
BOOLEAN InitData(HWND& hWnd) {
//M&C Init
	Input = new Control();
	mapData = new MapData1();
	tankData = new TankData();
	RuleAI = new GameAI();
	RuleAI->addMap(mapData);
	RuleAI->addTank(tankData);
	RuleAI->addControl(Input);
//V Init
	Layout = new GraphicLayout(hWnd,hInst);
	tank = new Tank();
	map = new Map();
	tank->readData(tankData);
	map->readData(mapData);
	Layout->addGraphicUnit(map);
	Layout->addGraphicUnit(tank);
	Layout->Init();

	RuleAI->setGraph(Layout);
//
     Gdiplus::GdiplusStartupInput GdiplusStartupInput;
     Gdiplus::GdiplusStartup(&m_gdiplusToken, &GdiplusStartupInput, NULL);
	return TRUE;
}


BOOLEAN Release() {
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	//releasedata
	delete Input;
	delete RuleAI;
	delete mapData;
	delete tankData;
	delete Layout;
	delete tank;
	delete map;
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
		SetTimer(hWnd,1,10,NULL);
		break;
	case WM_PAINT:
		Layout->RefreshWnd(hWnd);
		Layout->Init();
		Layout->draw();
		break;
	case WM_KEYDOWN:
		Input->Input(wParam);
		RuleAI->Handle();
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	case WM_KEYUP:
		Input->keep();
		RuleAI->Handle();
		InvalidateRect(hWnd, NULL, FALSE);
	case WM_TIMER:
		//flash
		RuleAI->Handle(true);
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
		PostQuitMessage(0);
		KillTimer(hWnd,1);
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