#include"TankWarApp.h"
/*
GameSketch
720p screen utility
GameInput-->GameAIHandle-->GameDraw
in WndProc as
case WM_PAINT, case WM_KEYDOWN
*/

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
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Control*user=new Control;
	Map *mymap;
	Tank* mytank;
	GameAI *App=new GameAI;
	HBRUSH brush = CreateSolidBrush(RGB(100, 100, 100));
	switch (message)
	{

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		//entrance for painting code
		
		mytank = new Tank(hdc);
		mymap = new Map(hdc);
		mymap->draw();
		mytank->draw();
		delete mymap;
		//delete others
		EndPaint(hWnd,&ps);
		break;
	case WM_KEYDOWN:
		//Game input data and handle
		user->move();
		user->fire();
		App->Handle();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);															//调用PostQuitMessage发出WM_QUIT消息
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);						//默认时采用系统消息默认处理函数
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
	wcex.lpszMenuName = NULL;
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
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
