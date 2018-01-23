/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.23 / 19：56
+
-             修改时间：2018.1.23 / 19：56
+
-             文件名称：enemy.c
+
-             模块：enemy敌人模块，游戏敌人相关功能
+
-             功能：敌人模块源文件，包括函数的定义，静态函数声明及定义
+
*/
#include "enemy.h"

PENEMY
GetEnemy(POINT _enemyPos) {

	PENEMY _penemy = (PENEMY)malloc(sizeof(ENEMY));
	if (!_penemy)
		exit(OVERFLOWED);

	_penemy->m_enemyPos = _enemyPos;

	/*
	**暂时未导入敌人的图像
	*/

	return _penemy;

}
// 初始化敌人，通过位置数据生成敌人


STATUS
FreeEnemy(PENEMY _penemy) {

	assert(_penemy != NULL);

	free(_penemy);
	_penemy = NULL;

	return OK;

}
// 释放敌人实例所占用内存，释放资源


STATUS
GetEnemyPosIfo() {


	return OK;

}
// 从本地文件中获取敌人的位置信息