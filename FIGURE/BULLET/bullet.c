/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.2 / 20：41
+
-             修改时间：2018.1.2 / 20：41
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
__createBullet(POINT);
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






/*
+
-			函数定义
+
*/

PBULLETS
InitBulletslk() {

	PBULLETS _pbullets = (PBULLETS)malloc(sizeof(BULLETS));
	if (!_pbullets)
		exit(OVERFLOW);

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

	return OK;

}
// 释放子弹链表，以及所有子弹结点的内存资源


STATUS
AddBullet(PBULLETS _pbullets, POINT _pos) {

	assert(_pbullets != NULL);

	PBULLET _newBullet = __createBullet(_pos);

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
	
	PBULLET _tmp = _pbullets->m_head;

	POINT   _initialPos;
	
	while (_tmp != NULL) {

		_initialPos.x = _tmp->m_pos.x + BULLET_INITIAL_POS_OFFSET_X;
		_initialPos.y = _tmp->m_pos.y + BULLET_INITIAL_POS_OFFSET_Y;

		DrawEffect(_hdc, _memDc, _initialPos, 7);
		_tmp = _tmp->m_next;

	}
	
	return OK;

}
// 画出子弹链表中的子弹


STATUS
BulletsTimerProc(PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	PBULLET _rec = NULL;

	// 改变子弹的位置，飞行距离 //
	__changeBullets_Pos_Distance(_pbullets);

	// 检查子弹位置 //
	_rec = __checkBulletsPos(_pbullets);

	// 如果_rec!=NULL 释放该结点内存资源 //
	if (_rec != NULL) {

		__freeBullet(_pbullets, _rec);

	}

	return OK;

}
// 关于子弹的计时器进程函数（包括画出子弹位置刷新，位置判定等）





/*
+
-			静态函数定义
+
*/

static PBULLET
__createBullet(POINT _pos) {

	PBULLET _pbullet = (PBULLET)malloc(sizeof(NODE));
	if (!_pbullet)
		exit(OVERFLOW);

	_pbullet->m_pos     = _pos;
	_pbullet->m_dstance = 0;
	_pbullet->m_next    = NULL;
	_pbullet->m_pre     = NULL;

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

		_tmp->m_pos.x += _pbullets->m_speed;
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