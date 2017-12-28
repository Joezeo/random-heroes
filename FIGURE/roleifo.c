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
__RoleMvStatusChange(PROLE, WPARAM, HWND);
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
	_prole->m_fmapRefresh = FALSE;
	_prole->m_bmapRefresh = FALSE;
	_prole->m_fmapEnd     = FALSE;
	_prole->m_bmapEnd     = TRUE;
	
	GetObject(_prole->m_hbmp, sizeof(BITMAP), &_bmp);
	_prole->m_size.cx = (_bmp.bmWidth) / 3;
	_prole->m_size.cy = _bmp.bmHeight / 3;

	_prole->m_pos.x = 0;
	_prole->m_pos.y = CLI_HEIGHT - _prole->m_size.cy;

	_prole->m_clientPos.x = 0;
	_prole->m_clientPos.y = CLI_HEIGHT - _prole->m_size.cy;

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

	/*------------------------------------------------------------------------------*/

	// 如果角色到达了地图刷新处，并且没有越界更新_pimage的m_drawLocation属性
	// 地图位置向前移动
	if (_prole->m_fmapRefresh && _pimage->m_drawLocation < 2 * CLI_WIDTH
		&& _prole->m_moveStatus)
		_pimage->m_drawLocation += _prole->m_speed;
	if (_prole->m_bmapRefresh && _pimage->m_drawLocation > 0
		&& _prole->m_moveStatus)
		_pimage->m_drawLocation -= _prole->m_speed;


	// 如果地图达到前方边界，m_fmapEnd = TRUE
	if (_pimage->m_drawLocation == 2 * CLI_WIDTH)
		_prole->m_fmapEnd = TRUE;
	else
		_prole->m_fmapEnd = FALSE;

	// 如果地图达到后方边界，m_bmapEnd = TRUE
	if(_pimage->m_drawLocation == 0)
		_prole->m_bmapEnd = TRUE;
	else
		_prole->m_bmapEnd = FALSE;

	/*------------------------------------------------------------------------------*/


	_winDc = GetDC(_hwnd);

	_tmpDc = CreateCompatibleDC(_winDc);

	SelectObject(_pimage->m_memDc, _pimage->m_hBmp);

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

	return OK;

}
// 画出角色


STATUS
ControlRole(PROLE _prole, WPARAM _wParam, HWND _hwnd) {

	assert(_prole != NULL);
	assert(_hwnd != NULL);

	if(_prole->m_highStatus == 0)
		_prole->m_keyDownCnt++;

	__moveRole(_prole, _wParam, _hwnd);

	return OK;

}
// 角色控制，移动跳跃


STATUS
UnControlRole(PROLE _prole, WPARAM _wParam, HWND _hwnd) {

	assert(_prole != NULL);

	__RoleMvStatusChange(_prole, _wParam, _hwnd);

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

		__JumpRole(_prole);

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

		// 角色在跳跃状态按方向键无效
		if (_prole->m_status != 0)
			break;

		// 如果角色的移动状态不为TRUE，在按下按键后就为TRUE
		if (!(_prole->m_moveStatus))
			_prole->m_moveStatus = TRUE;

		// 如果角色移动方向为向前，按下左键则改变为向后
		if (_prole->m_mvDirection)
			_prole->m_mvDirection = FALSE;

		// 如果角色向后走，并且达到了前方地图刷新点，则转换其为FALSE
		if (_prole->m_fmapRefresh)
			_prole->m_fmapRefresh = FALSE;

		// 到达后地图刷新点的条件
		if (_prole->m_clientPos.x <= CLI_WIDTH / 4) {

			_prole->m_bmapRefresh = TRUE;

		}	

		if (_prole->m_pos.x > 0) {

			_prole->m_pos.x -= _prole->m_speed;

			// 如果角色没到达地图刷新点，或者地图到达后方尽头，并且m_clientPos.x > 0
			// 这时才改变角色的客户区坐标
			if ( !(_prole->m_bmapRefresh) 
				|| (_prole->m_clientPos.x > 0 && _prole->m_bmapEnd))
				_prole->m_clientPos.x -= _prole->m_speed;

		}
			
		InvalidateRect(_hwnd, NULL, TRUE);

		break;

	case VK_RIGHT: // 右为向前走

		// 角色在跳跃状态按方向键无效
		if (_prole->m_status != 0)
			break;

		// 如果角色的移动状态不为TRUE，在按下按键后就为TRUE
		if (!(_prole->m_moveStatus))
			_prole->m_moveStatus = TRUE;

		// 如果角色移动方向为向后，按下左键则改变为向前
		if (!(_prole->m_mvDirection))
			_prole->m_mvDirection = TRUE;

		// 如果角色向前走，并且达到了后方地图刷新点，则转换其为FALSE
		if (_prole->m_bmapRefresh)
			_prole->m_bmapRefresh = FALSE;

		// 到达前地图刷新点的条件
		if (_prole->m_clientPos.x >= CLI_WIDTH / 4 * 3) {

			_prole->m_fmapRefresh = TRUE;

		}
			
		if (_prole->m_pos.x <= 3 * CLI_WIDTH - _prole->m_size.cx) {

			_prole->m_pos.x += _prole->m_speed;

			// 如果角色没到达地图刷新点，或者地图到达前方方尽头，并且m_clientPos.x < CLI_WIDTH
			// 这时才改变角色的客户区坐标
			if (!(_prole->m_fmapRefresh)
				|| (_prole->m_clientPos.x < CLI_WIDTH && _prole->m_fmapEnd))
				_prole->m_clientPos.x += _prole->m_speed;

		}

		InvalidateRect(_hwnd, NULL, TRUE);

		break;

	case VK_UP:

		if (_prole->m_status != 1) {

			_prole->m_status = 2; // 切换角色为起跳状态
			_prole->m_index = 0;

		}

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

	if (_prole->m_curHeight < 2)
		_prole->m_index = 0;
	else
		_prole->m_index = 1;

	_prole->m_pos.y -= 10;
	_prole->m_curHeight += 1;

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

	if (_prole->m_mvDirection 
		&& _prole->m_pos.x <= 3 * CLI_WIDTH - _prole->m_size.cx) {

		_prole->m_pos.x += _prole->m_speed;

		// 如果角色没到达地图刷新点，或者地图到达前方方尽头，并且m_clientPos.x < CLI_WIDTH
		// 这时才改变角色的客户区坐标
		if (!(_prole->m_fmapRefresh)
			|| (_prole->m_clientPos.x < CLI_WIDTH && _prole->m_fmapEnd))
			_prole->m_clientPos.x += _prole->m_speed;

	}	
	else if (!(_prole->m_mvDirection)
		&& _prole->m_pos.x > 0) {

		_prole->m_pos.x -= _prole->m_speed;

		// 如果角色没到达地图刷新点，或者地图到达后方尽头，并且m_clientPos.x > 0
		// 这时才改变角色的客户区坐标
		if (!(_prole->m_bmapRefresh)
			|| (_prole->m_clientPos.x > 0 && _prole->m_bmapEnd))
			_prole->m_clientPos.x -= _prole->m_speed;
	}
		

	return OK;

}
// 如果角色跳跃之前处于正在移动状态则产生向前的惯性移动

static STATUS
__RoleMvStatusChange(PROLE _prole, WPARAM _wparam, HWND _hwnd) {

	assert(_prole != NULL);

	if (_prole->m_status != 0)
		return OK;

	switch (_wparam) {

	case VK_LEFT:

		// 此处没有 break;

	case VK_RIGHT:

		_prole->m_moveStatus = FALSE;
		_prole->m_index      = 0; // 按键抬起时，改变人物图像为0

		InvalidateRect(_hwnd, NULL, TRUE);

		break;

	}

	return OK;

}
// 按键抬起时，改变角色的移动状态
