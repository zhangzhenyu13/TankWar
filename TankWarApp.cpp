#include"TankWarApp.h"
#include"resource.h"
/*
GameSketch
720p screen utility
GameInput-->GameAIHandle-->GameDraw
in WndProc as
case WM_PAINT, case WM_KEYDOWN
*/
static HINSTANCE hInst;
static Control* myInput;
static GameData* myTankData;
static GameData* myData;
static GameAI* myAI;

BOOLEAN InitData(HWND& hWnd) {
	myData = new MapData1();
	myTankData = new TankData();
	return TRUE;
}

BOOLEAN InitControl(HWND& hWnd) {

	return TRUE;
}
BOOLEAN Release() {

	delete myInput;
	delete myAI;
	delete myData;
	return TRUE;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOLEAN CALLBACK MYDlg(HWND, UINT, WPARAM, LPARAM);
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
	
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;

	myInput = new Control;
	Tank myTank(hInst,hWnd);
	Map myMap(hInst,hWnd);
	myMap.readData(*myData);
	myTank.readData(*myTankData);
	
	TankData* mytankdata = myTank.getData();


	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,1,NULL);
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);

		//myMap.draw();
		myTank.draw();
		if(mytankdata->getfireflag()) {
			int *pos = mytankdata->getfirepos();
			switch (mytankdata->getfiredirect())
			{
			case 'u':
				mytankdata->writeposfire(pos[0],pos[1]-5);
				break;
			case 'l':
				mytankdata->writeposfire(pos[0]-5,pos[1]);
				break;
			case 'r':
				mytankdata->writeposfire(pos[0]+5,pos[1]);
				break;
			case 'd':
				mytankdata->writeposfire(pos[0],pos[1]+5);
				break;
			default:
				break;
			}
		}
		
		EndPaint(hWnd,&ps);
		break;
	case WM_KEYDOWN:
		//Game input data and handle
		//DialogBoxW(hInst,MAKEINTRESOURCE(MY_DIALOG),hWnd,(DLGPROC)MYDlg);

		//press direction key to move
		myInput->move(wParam, mytankdata);
		//press SPACE to fire
		if(wParam == VK_SPACE)
			myInput->fire(mytankdata);
		InvalidateRect(hWnd,NULL,1);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,1);
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
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCE(MY_MENU);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return FALSE;
	hWnd = CreateWindowW(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
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

	InitControl(hWnd);

	//
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

BOOLEAN CALLBACK MYDlg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	}
	
	return TRUE;
}