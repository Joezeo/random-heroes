/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.23 / 19：56
+
-             修改时间：2018.1.23 / 19：56
+
-             文件名称：enemy.h
+
-             模块：enemy敌人模块，游戏敌人相关功能
+
-             功能：敌人模块头文件，包括头文件包含，宏定义，函数前向声明等
+
*/
#ifndef __ENEMY_H__
#define __ENEMY_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include "../SYS/systc.h"
#include "../RandomHeroes/resource.h"


/*
+
-			结构体定义
+
*/

typedef struct {

	/*
	**敌人的位置数据从本地文件中进行保存
	*/
	POINT   m_enemyPos;
	HBITMAP m_enemyHbmp;

}ENEMY, * PENEMY;


/*
+
-			函数前向声明
+
*/
PENEMY
GetEnemy(POINT);
// 初始化敌人，通过位置数据生成敌人

STATUS
FreeEnemy(PENEMY);
// 释放敌人实例所占用内存，释放资源

STATUS
GetEnemyPosIfo();
// 从本地文件中获取敌人的位置信息


#ifdef __cplusplus
}
#endif

#endif // __ENEMY_H__ //