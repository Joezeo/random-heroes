/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.2 / 20：41
+
-             修改时间：2018.1.5 / 12：20
+
-             文件名称：bullet.c
+
-             模块：子弹模块，子弹用链表保存，子弹相关功能
+
-             功能：子弹模块源文件，包括函数定义
+
*/

#include "bullet.h"

/*
+
-			静态函数前向声明
+
*/
static PBULLET
__createBullet(POINT, BOOL);
// 静态函数，生成一个子弹结点


static BOOL
__emptyBullets(const PBULLETS);
// 判断子弹链表是否为空


static STATUS
__changeBullets_Pos_Distance(PBULLETS);
// 改变子弹的位置，飞行距离


static PBULLET
__checkBulletsPos(const PBULLETS);
// 检查子弹位置，如果存在已经达到最大飞行距离的子弹，则返回这个子弹结点的位置


static STATUS
__freeBullet(PBULLETS, PBULLET);
// 静态函数，释放此地址的子弹结点的内存资源


static HDC
__loadBulletImage(HDC);
// 加载子弹的图片，存于HDC中，并将其返回


static STATUS
__drawBullet(HDC, HDC, POINT);
// 画出单个子弹






/*
+
-			函数定义
+
*/

PBULLETS
InitBulletslk() {

	PBULLETS _pbullets = (PBULLETS)malloc(sizeof(BULLETS));
	if (!_pbullets)
		exit(OVERFLOWED);

	_pbullets->m_head        = NULL;
	_pbullets->m_tail        = NULL;
	_pbullets->m_cnt         = 0;
	_pbullets->m_maxDistance = CLI_WIDTH;
	_pbullets->m_speed       = BULLET_SPEED;

	return _pbullets;

}
// 初始化子弹链表


STATUS
FreeBulletslk(PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	PBULLET _pre = NULL;
	PBULLET _cur = NULL;

	if (!__emptyBullets(_pbullets)) {

		_cur = _pbullets->m_head;

		while (_cur != NULL) {

			_pre = _cur->m_next;
			__freeBullet(_pbullets, _cur);
			_cur = _pre;

		}

	}

	free(_pbullets);
	_pbullets = NULL;

	return OK;

}
// 释放子弹链表，以及所有子弹结点的内存资源


STATUS
AddBullet(PBULLETS _pbullets, POINT _pos, BOOL _direction) {

	assert(_pbullets != NULL);

	POINT   _initialPos;

	// 子弹初始位置，即角色位置加上枪口位置偏移 //
	if (_direction) {

		_initialPos.x = _pos.x + BULLET_FORWARD_INITIAL_POS_OFFSET_X;
		_initialPos.y = _pos.y + BULLET_FORWARD_INITIAL_POS_OFFSET_Y;

	}
	else {

		_initialPos.x = _pos.x + BULLET_BACKWARD_INITIAL_POS_OFFSET_X;
		_initialPos.y = _pos.y + BULLET_BACKWARD_INITIAL_POS_OFFSET_Y;

	}


	PBULLET _newBullet = __createBullet(_initialPos, _direction);

	if (__emptyBullets(_pbullets)) {

		_pbullets->m_head = _newBullet;
		_pbullets->m_tail = _newBullet;

		goto ending;

	}
	else {

		_pbullets->m_tail->m_next = _newBullet;
		_newBullet->m_pre         = _pbullets->m_tail;
		_pbullets->m_tail         = _newBullet;

		goto ending;

	}

ending:
	_pbullets->m_cnt++;

	return OK;

}
// 往子弹链表中添加一个子弹


STATUS
DrawBullets(const PBULLETS _pbullets, HDC _hdc, HDC _memDc) {

	assert(_pbullets != NULL);
	assert(_hdc != NULL);
	assert(_memDc != NULL);

	if (__emptyBullets(_pbullets))
		return OK;

	int     _result;
	int     _flag = 0;

	HDC     _tmpDc = __loadBulletImage(_hdc);
	
	PBULLET _tmp   = _pbullets->m_head;

	POINT   _centerPt;
	_centerPt.x = 20 / 2;
	_centerPt.y = 8 / 2;

	while (_tmp != NULL) {

		if (!_tmp->m_bltMvDirction) {

			_result = RotateDc(_hdc, 180, _centerPt);
			_flag   = 1;

		}

		__drawBullet(_tmpDc, _memDc, _tmp->m_pos);

		if (_flag) {

			RestoreRotateDc(_hdc, _result);
			_flag = 0;

		}

		_tmp = _tmp->m_next;

	}

	DeleteDC(_tmpDc);
	
	return OK;

}
// 画出子弹链表中的子弹


STATUS
BulletsTimerProc(PBULLETS _pbullets, HWND _hwnd) {

	assert(_pbullets != NULL);

	if (__emptyBullets(_pbullets))
		return OK;

	PBULLET _rec = NULL;

	// 改变子弹的位置，飞行距离 //
	__changeBullets_Pos_Distance(_pbullets);

	// 检查子弹位置 //
	_rec = __checkBulletsPos(_pbullets);

	// 如果_rec!=NULL 释放该结点内存资源 //
	if (_rec != NULL) {

		__freeBullet(_pbullets, _rec);

	}

	// 清空屏幕，重绘，达到动画效果 //
	InvalidateRect(_hwnd, NULL, TRUE);

	return OK;

}
// 关于子弹的计时器进程函数（包括画出子弹位置刷新，位置判定等）





/*
+
-			静态函数定义
+
*/

static PBULLET
__createBullet(POINT _pos, BOOL _direction) {

	PBULLET _pbullet = (PBULLET)malloc(sizeof(NODE));
	if (!_pbullet)
		exit(OVERFLOWED);

	_pbullet->m_pos           = _pos;
	_pbullet->m_dstance       = 0;
	_pbullet->m_bltMvDirction = _direction;
	_pbullet->m_next          = NULL;
	_pbullet->m_pre           = NULL;

	return _pbullet;

}
// 静态函数，生成一个子弹结点


static BOOL
__emptyBullets(const PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	if (_pbullets->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 判断子弹链表是否为空


static STATUS
__changeBullets_Pos_Distance(PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	if (__emptyBullets(_pbullets))
		return OK;

	PBULLET _tmp = _pbullets->m_head;

	while (_tmp != NULL) {

		if(_tmp->m_bltMvDirction)
			_tmp->m_pos.x += _pbullets->m_speed;
		else
			_tmp->m_pos.x -= _pbullets->m_speed;

		_tmp->m_dstance += _pbullets->m_speed;
		_tmp = _tmp->m_next;

	}

	return OK;

}
// 改变子弹的位置，飞行距离


static PBULLET
__checkBulletsPos(const PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	if (__emptyBullets(_pbullets))
		return NULL;

	PBULLET _tmp = _pbullets->m_head;

	while (_tmp != NULL) {

		if (_tmp->m_dstance >= _pbullets->m_maxDistance)
			return _tmp;

		_tmp = _tmp->m_next;

	}

	return NULL;

}
// 检查子弹位置，如果存在已经达到最大飞行距离的子弹，则返回这个子弹结点的位置


static STATUS
__freeBullet(PBULLETS _pbullets, PBULLET _pbullet) {

	assert(_pbullets != NULL);
	assert(_pbullet != NULL);

	if (_pbullets->m_head == _pbullets->m_tail) {

		free(_pbullet);
		_pbullet = NULL;

		_pbullets->m_head = NULL;
		_pbullets->m_tail = NULL;

		goto ending;

	}
	else if (_pbullets->m_head == _pbullet) {

		_pbullets->m_head = _pbullet->m_next;

		free(_pbullet);
		_pbullet = NULL;

		goto ending;

	}

ending:
	_pbullets->m_cnt--;

	return OK;

}
// 静态函数，释放此地址的子弹结点的内存资源


static HDC
__loadBulletImage(HDC _hdc) {

	assert(_hdc != NULL);

	HDC       _memDc   = CreateCompatibleDC(_hdc);
	HBITMAP   _tmpHbmp = CreateCompatibleBitmap(_hdc,
												(EFF_SIZE + 7)->cx, (EFF_SIZE + 7)->cy);

	SelectObject(_memDc, _tmpHbmp);

	POINT  _pos;
	_pos.x = 0;
	_pos.y = 0;

	DrawEffect(_hdc, _memDc, _pos, 7);

	DeleteObject(_tmpHbmp);

	return _memDc;

}
// 加载子弹的图片，存于HDC中，并将其返回


static STATUS
__drawBullet(HDC _tmpDc, HDC _memDc, POINT _pos) {

	assert(_tmpDc != NULL);
	assert(_memDc != NULL);

	TransparentBlt(_memDc,
		_pos.x, _pos.y,
		(EFF_SIZE + 7)->cx, (EFF_SIZE + 7)->cy,
		_tmpDc,
		0, 0,
		(EFF_SIZE + 7)->cx, (EFF_SIZE + 7)->cy,
		RGB(0, 0, 0));

	return OK;

}
// 画出单个子弹