/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.23 / 20：25
+
-             修改时间：2018.1.23 / 20：25
+
-             文件名称：stage.c
+
-             模块：stage关卡模块，各个关卡的敌人信息(之后会把地图信息也加入进来)
+
-             功能：stage关卡模块源文件，包括函数的定义，以及静态函数的定义
+
*/

#include "stage.h"

PSTAGE
InitStage() {

	PSTAGE _pstage = (PSTAGE)malloc(sizeof(STAGE));
	if (!_pstage)
		exit(OVERFLOWED);

	_pstage->m_stageIfo = one;

	return _pstage;

}
// 初始化stage模块实例


STATUS
FreeStage(PSTAGE _pstage) {

	assert(_pstage != NULL);

	free(_pstage);
	_pstage = NULL;

	return OK;

}
// 释放stage实例内存资源