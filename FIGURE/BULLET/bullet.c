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
CreateBullet(POINT);
// 静态函数，生成一个子弹结点


static BOOL
EmptyBullets(const PBULLETS);
// 判断子弹链表是否为空

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
AddBullet(PBULLETS _pbullets, POINT _pos) {

	assert(_pbullets != NULL);

	PBULLET _newBullet = CreateBullet(_pos);

	if (EmptyBullets(_pbullets)) {

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

	PBULLET _tmp   = _pbullets->m_head;

	if (EmptyBullets(_pbullets))
		return OK;

	while (_tmp != NULL) {

		DrawEffect(_hdc, _memDc, _tmp->m_pos, 7);
		_tmp = _tmp->m_next;

	}
	
	return OK;

}
// 画出子弹链表中的子弹


STATUS
BulletsTimerProc(const PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	PBULLET _tmp = _pbullets->m_head;

	while (_tmp != NULL) {

		_tmp->m_pos.x += _pbullets->m_speed;
		_tmp = _tmp->m_next;

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
CreateBullet(POINT _pos) {

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
EmptyBullets(const PBULLETS _pbullets) {

	assert(_pbullets != NULL);

	if (_pbullets->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 判断子弹链表是否为空