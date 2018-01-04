/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.2 / 20：41
+
-             修改时间：2018.1.2 / 20：41
+
-             文件名称：bullet.h
+
-             模块：子弹模块，子弹用链表保存，子弹相关功能
+
-             功能：子弹模块头文件，包括头文件包含，结构体定义，函数前向声明
+
*/

#ifndef __BULLET_H__
#define __BULLET_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include "../../SYS/systc.h"
#include "../../EFFECT/effect.h" // 从ALL_EFFECTS中截取子弹图像


/*
+
-			宏定义
+
*/
#define BULLET_SPEED 10;

// 角色向前时枪口位置偏移量 //
#define BULLET_FORWARD_INITIAL_POS_OFFSET_X   10 + 32
#define BULLET_FORWARD_INITIAL_POS_OFFSET_Y   7  + 5
// 角色向后时枪口位置偏移量 //
#define BULLET_BACKWARD_INITIAL_POS_OFFSET_X  -41
#define BULLET_BACKWARD_INITIAL_POS_OFFSET_Y  7 + 5


/*
+
-			结构体定义
+
*/
// 子弹结点定义 //
typedef struct NODE {

	POINT m_pos;
	UINT  m_dstance;        // 子弹已经飞行的距离
	BOOL  m_bltMvDirction;  // 子弹飞行方向，TRUE向前，FALSE向后

	struct NODE * m_next;
	struct NODE * m_pre;

}NODE, * PNODE, * PBULLET;

// 子弹链表定义 //
typedef struct {

	PBULLET m_head;
	PBULLET m_tail;

	UINT    m_cnt;          // 子弹链表中拥有的子弹数量
	UINT    m_maxDistance;  // 子弹飞行的最大距离
	UINT    m_speed;        // 子弹飞行的速度

}BULLETS, * PBULLETS;

/*
+
-			函数前向声明
+
*/

PBULLETS
InitBulletslk();
// 初始化子弹链表

STATUS
FreeBulletslk(PBULLETS);
// 释放子弹链表，以及所有子弹结点的内存资源

STATUS
AddBullet(PBULLETS, POINT, BOOL);
// 往子弹链表中添加一个子弹

STATUS
DrawBullets(const PBULLETS, HDC, HDC);
// 画出子弹链表中的子弹

STATUS
BulletsTimerProc(PBULLETS, HWND);
// 关于子弹的计时器进程函数（包括画出子弹位置刷新，位置判定等）

#ifdef __cplusplus
}
#endif

#endif // __BULLET_H__ //