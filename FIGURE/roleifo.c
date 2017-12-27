/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 15：21
+
-             修改时间：2017.12.27 / 15：21
+
-             文件名称：roleifo.c
+
-             模块：role模块，关于游戏角色的模块，包括角色的控制，绘制，状态等
+
-             功能：role模块源文件，包括函数定义
+
*/

#include "roleifo.h"

/*
+
-			函数定义
+
*/

PROLE
InitRole(HINSTANCE _hins) {

	PROLE _prole = (PROLE)malloc(sizeof(ROLE));

	if (!_prole)
		exit(OVERFLOW);

	BITMAP            _bmp;

	_prole->m_hbmp   = LoadBitmap(_hins, MAKEINTRESOURCE(IDB_REAL_ROLE_BAN));
	_prole->m_status = 0;
	_prole->m_index = 0;
	_prole->m_speed = 5;
	
	GetObject(_prole->m_hbmp, sizeof(BITMAP), &_bmp);
	_prole->m_size.cx = (_bmp.bmWidth) / 3;
	_prole->m_size.cy = _bmp.bmHeight / 3;

	_prole->m_pos.x = 0;
	_prole->m_pos.y = CLI_HEIGHT - _prole->m_size.cy;

	return _prole;

}
// 初始化ROLE结构体实例


STATUS
FreeRole(PROLE _prole) {

	assert(_prole != NULL);

	free(_prole);

	return OK;

}
// 释放ROLE实例资源


STATUS
DrawRole(const HWND _hwnd, const PROLE _prole) {

	assert(_hwnd != NULL);
	assert(_prole != NULL);

	HDC               _memDc;
	HDC               _winDc;
	HDC               _tmpDc;
	HBITMAP           _tmpHbm;

	_winDc  = GetDC(_hwnd);
	_memDc  = CreateCompatibleDC(_winDc);
	_tmpDc  = CreateCompatibleDC(_winDc);
	_tmpHbm = CreateCompatibleBitmap(_winDc, _prole->m_size.cx, _prole->m_size.cy);

	SelectObject(_memDc, _tmpHbm);

	SelectObject(_tmpDc, _prole->m_hbmp);

	TransparentBlt(_memDc,
		0, 0,
		_prole->m_size.cx, _prole->m_size.cy,
		_tmpDc,
		(_prole->m_size.cx)*(_prole->m_index),	// 横向裁剪
		(_prole->m_size.cy)*(_prole->m_status), // 竖向裁剪
		_prole->m_size.cx, _prole->m_size.cy,
		RGB(0, 0, 0));

	BitBlt(_winDc,
		_prole->m_pos.x, _prole->m_pos.y,
		_prole->m_size.cx, _prole->m_size.cy,
		_memDc,
		0, 0,
		SRCCOPY);

	ReleaseDC(_hwnd, _winDc);
	DeleteDC(_tmpDc);
	DeleteDC(_memDc);
	DeleteObject(_tmpHbm);

	return OK;

}
// 画出角色


STATUS
MoveRole(PROLE _prole, WPARAM _wParam) {

	assert(_prole != NULL);

	switch (_wParam) {

	case VK_LEFT:

		_prole->m_pos.x -= _prole->m_speed;

		break;

	case VK_RIGHT:

		_prole->m_pos.x += _prole->m_speed;

		break;

	}

	_prole->m_index++;

	if (_prole->m_index == 3) {

		_prole->m_index = 0;

	}

}
// 角色移动