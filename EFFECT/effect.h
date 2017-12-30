/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.29 / 17：34
+
-             修改时间：2017.12.30 / 14：47
+
-             文件名称：effect.h
+
-             模块：特效模块，特效相关功能
+
-             功能：特效模块头文件，包括头文件包含，宏定义，结构体定义，函数前向声明
+
*/

#ifndef __EFFECT_H__
#define __EFFECT_H__

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
extern HINSTANCE                 g_hinst;

// HBITMAP
#define ALL_EFFECTS LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_EFFECTS))

// PCAPEFF
#define P_CAP_EFFECT InitCoordSize()
#define EFF_SIZE P_CAP_EFFECT->m_bmpSize
#define EFF_POS  P_CAP_EFFECT->m_bmpCoord

// 特效图片数量
#define CNT_EFFECTS 34


/*
+
-			结构体定义
+
*/

typedef struct {

	// 所有图都在一张bmp图上，这两个数组用于截取特效
	POINT        m_bmpCoord[CNT_EFFECTS];
	SIZE         m_bmpSize[CNT_EFFECTS];

}CAPTURE_EFFECT, * PCAPEFF;

/*
+
-			函数前向声明
+
*/
PCAPEFF
InitCoordSize();
// 用于特效图片截取坐标，尺寸加载
// 从EFFECT目录下的effct文件中读取数据

STATUS
FreeCapEffct(PCAPEFF);
// 释放PCAPEFF内存资源

STATUS
DrawEffect(HDC, HDC, const POINT, const UINT);
// 根据传入的位置，特效id，画出特效

#ifdef __cplusplus
}
#endif

#endif // __EFFECT_H__ //
