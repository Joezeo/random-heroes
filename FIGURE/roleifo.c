/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 15：21
+
-             修改时间：2017.12.28 / 14：08
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
-			静态函数前向声明
+
*/

static STATUS
__moveRole(PROLE, WPARAM, HWND);
// 按键控制角色移动,跳跃

static STATUS
__JumpRole(PROLE);
// 角色跳跃开始

static STATUS
__HighRole(PROLE);
// 角色跳跃处于最高处的状态

static STATUS
__FallRole(PROLE);
// 判断角色跳跃完成

static STATUS
__MoveInertia(PROLE);
// 如果角色跳跃之前处于正在移动状态则产生向前的惯性移动

static STATUS
__RoleMvStatusChange(PROLE, WPARAM);
// 按键抬起时，改变角色的移动状态


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

	_prole->m_hbmp        = LoadBitmap(_hins, MAKEINTRESOURCE(IDB_REAL_ROLE_BAN));
	_prole->m_status      = 0;
	_prole->m_index       = 0;
	_prole->m_speed       = 5;
	_prole->m_keyDownCnt  = 0;
	_prole->m_maxHeight   = 15;
	_prole->m_curHeight   = 0;
	_prole->m_highStatus  = FALSE;
	_prole->m_moveStatus  = FALSE;
	_prole->m_mvDirection = TRUE;
	
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
DrawRole(const HWND _hwnd, const PROLE _prole, PIMAGE _pimage) {

	assert(_hwnd != NULL);
	assert(_prole != NULL);
	assert(_pimage != NULL);

	HDC               _winDc;
	HDC               _tmpDc;
	HBITMAP           _tmpHbm;

	_winDc = GetDC(_hwnd);

	_tmpDc = CreateCompatibleDC(_winDc);
	_tmpHbm = CreateCompatibleBitmap(_winDc, CLI_WIDTH, CLI_HEIGHT);

	SelectObject(_pimage->m_memDc, _tmpHbm);

	SelectObject(_tmpDc, _prole->m_hbmp);

	TransparentBlt(_pimage->m_memDc,
		_prole->m_pos.x, _prole->m_pos.y,
		_prole->m_size.cx, _prole->m_size.cy,
		_tmpDc,
		(_prole->m_size.cx)*(_prole->m_index),	// 横向裁剪
		(_prole->m_size.cy)*(_prole->m_status), // 竖向裁剪
		_prole->m_size.cx, _prole->m_size.cy,
		RGB(255, 255, 255));

	ReleaseDC(_hwnd, _winDc);
	DeleteDC(_tmpDc);
	DeleteObject(_tmpHbm);

	return OK;

}
// 画出角色


STATUS
ControlRole(PROLE _prole, WPARAM _wParam, HWND _hwnd, PSYS _psys) {

	assert(_prole != NULL);
	assert(_hwnd != NULL);
	assert(_psys != NULL);

	if(_prole->m_highStatus == 0)
		_prole->m_keyDownCnt++;

	__moveRole(_prole, _wParam, _hwnd);

	return OK;

}
// 角色控制，移动跳跃


STATUS
UnControlRole(PROLE _prole, WPARAM _wParam) {

	assert(_prole != NULL);

	__RoleMvStatusChange(_prole, _wParam);

	return OK;

}
// 按键抬起，角色不受控制时的状态


STATUS
RoleJumpProc(PROLE _prole, HWND _hwnd) {

	assert(_prole != NULL);
	assert(_hwnd != NULL);

	if (_prole->m_status == 0)
		return OK;

	__MoveInertia(_prole);

	// 跳跃后没有达到最大高度
	if (!(_prole->m_highStatus) && _prole->m_status == 2) {

		if (_prole->m_curHeight < 2)
			_prole->m_index = 0;
		else
			_prole->m_index = 1;

		_prole->m_pos.y -= 10;
		_prole->m_curHeight += 1;

	}
	if (_prole->m_curHeight == _prole->m_maxHeight && _prole->m_status == 2) {

		__HighRole(_prole);

	}
	else if (_prole->m_highStatus) {

		__FallRole(_prole);

	}

	InvalidateRect(_hwnd, NULL, TRUE);

	return OK;

}
// 角色跳跃过程，此函数由Timer计时器控制


/*
+
-			静态函数定义
+
*/

static STATUS
__moveRole(PROLE _prole, WPARAM _wParam, HWND _hwnd) {

	assert(_prole != NULL);

	switch (_wParam) {

	case VK_LEFT: // 左为向后走

		if (_prole->m_status != 0)
			break;
		if (!(_prole->m_moveStatus))
			_prole->m_moveStatus = TRUE;
		if (_prole->m_mvDirection)
			_prole->m_mvDirection = FALSE;

		_prole->m_pos.x -= _prole->m_speed;

		InvalidateRect(_hwnd, NULL, TRUE);

		break;

	case VK_RIGHT: // 右为向前走

		if (_prole->m_status != 0)
			break;
		if (!(_prole->m_moveStatus))
			_prole->m_moveStatus = TRUE;
		if (!(_prole->m_mvDirection))
			_prole->m_mvDirection = TRUE;

		_prole->m_pos.x += _prole->m_speed;

		InvalidateRect(_hwnd, NULL, TRUE);

		break;

	case VK_UP:

		if(_prole->m_status != 1)
			__JumpRole(_prole);

		break;

	}

	if (_prole->m_keyDownCnt >= 5 && _prole->m_status == 0) {

		_prole->m_index++;
		_prole->m_keyDownCnt = 0;

	}

	if (_prole->m_index == 3) {

		_prole->m_index = 0;

	}

	return OK;

}
// 按键控制角色移动,跳跃

static STATUS
__JumpRole(PROLE _prole) {

	assert(_prole != NULL);

	_prole->m_status = 2; // 切换角色为起跳状态
	_prole->m_index  = 0;

	return OK;

}
// 角色跳跃开始

static STATUS
__HighRole(PROLE _prole) {

	assert(_prole != NULL);

	_prole->m_index      = 2;
	_prole->m_highStatus = TRUE;
	_prole->m_status = 1;
	
	return OK;

}
// 角色跳跃处于最高处的状态

static STATUS
__FallRole(PROLE _prole) {

	assert(_prole != NULL);

	if (_prole->m_curHeight > 3)
		_prole->m_index = 0;
	else if (_prole->m_curHeight > 2)
		_prole->m_index = 1;
	else
		_prole->m_index = 2;

	_prole->m_pos.y += 10;
	_prole->m_curHeight -= 1;

	if (_prole->m_curHeight == 0) {

		_prole->m_status     = 0;
		_prole->m_index      = 0;
		_prole->m_highStatus = FALSE;
		_prole->m_moveStatus = FALSE;

	}

	return OK;

}
// 判断角色跳跃完成

static STATUS
__MoveInertia(PROLE _prole) {

	assert(_prole != NULL);

	if (!(_prole->m_moveStatus)) {

		return OK;

	}

	if (_prole->m_mvDirection)
		_prole->m_pos.x += _prole->m_speed;
	else
		_prole->m_pos.x -= _prole->m_speed;

	return OK;

}
// 如果角色跳跃之前处于正在移动状态则产生向前的惯性移动

static STATUS
__RoleMvStatusChange(PROLE _prole, WPARAM _wparam) {

	assert(_prole != NULL);

	if (_prole->m_status != 0)
		return OK;

	switch (_wparam) {

	case VK_LEFT:

		// 此处没有 break;

	case VK_RIGHT:

		_prole->m_moveStatus = FALSE;

		break;

	}

	return OK;

}
// 按键抬起时，改变角色的移动状态
