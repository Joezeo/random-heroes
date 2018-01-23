/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.23 / 20：25
+
-             修改时间：2018.1.23 / 20：25
+
-             文件名称：stage.h
+
-             模块：stage关卡模块，各个关卡的敌人信息(之后会把地图信息也加入进来)
+
-             功能：stage关卡模块头文件，包括头文件的包含，宏定义，函数定义等
+
*/

#ifndef __STAGE_H__
#define __STAGE_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include "../SYS/systc.h"

/*
+
-			宏定义
+
*/

/*
**关卡敌人的数量
*/
#define ENEMY_CNT_STAGE_1 10;


/*
+
-			结构体定义
+
*/
typedef enum {

	one = 1,
	two,
	three,
	four,
	five,

}STAGEIFO;

typedef struct {

	STAGEIFO m_stageIfo;

}STAGE, * PSTAGE;


/*
+
-			函数前向声明
+
*/
PSTAGE
InitStage();
// 初始化stage模块实例

STATUS
FreeStage(PSTAGE);
// 释放stage实例内存资源

#ifdef __cplusplus
}
#endif

#endif // __STAGE_H__ //
