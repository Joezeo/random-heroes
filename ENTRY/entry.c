/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 12：54
+
-             修改时间：2017.12.27 / 12：54
+
-             文件名称：entry.c
+
-             模块：entry模块，程序主入口，游戏进程逻辑控制，消息队列处理
+
-             功能：entry模块源文件，包括函数定义，逻辑控制，消息处理
+
*/

#include "entry.h"

/*
+
-			全局变量定义区
+
*/
SYS                       g_sys;
HINSTANCE                 g_hinst;

/*
-
+			主函数，程序入口
-
*/
int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	static char szWndClassName[] = "gameWin";

	HWND                  hwnd;
	MSG                   msg;
	WNDCLASS              wndclass;

	g_hinst = hInstance;

	InitSystem(&g_sys);

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szWndClassName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);
		return 0;
	}

	// 由客户区大小获取窗口大小 //
	RECT	rect;
	SetRect(&rect, 0, 0, CLI_WIDTH, CLI_HEIGHT);
	AdjustWindowRect(&rect,
		WS_OVERLAPPEDWINDOW,
		FALSE);

	hwnd = CreateWindow(
		szWndClassName,		            //windows class name
		"Joezeo",			            //windows caption	
		WS_OVERLAPPEDWINDOW,            //windows style
		CW_USEDEFAULT,		            //intial x position
		CW_USEDEFAULT,		            //intial y position
		rect.right - rect.left,		    //intial x size
		rect.bottom - rect.top,		    //intial y size
		NULL,				            //parent wnidow handle
		NULL,				            //window menu handle
		hInstance,			            //program instance handle
		NULL);				            //creation paramenter

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}

/*
+
-			函数定义
+
*/

LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	HDC                            hdc;
	PAINTSTRUCT                    ps;
	RECT                           rect;

	switch (message) {

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}


VOID
InitSystem(PSYS _psys) {

	assert(_psys != NULL);

	_psys->m_cliHeight = CLI_HEIGHT;
	_psys->m_cliWidth  = CLI_WIDTH;

}