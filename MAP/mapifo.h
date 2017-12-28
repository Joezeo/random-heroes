/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.28 / 15：40
+
-             修改时间：2017.12.28 / 15：40
+
-             文件名称：mapifo.h
+
-             模块：map模块，地图的编辑，加载，绘制。
+
-             功能：map模块头文件，包括头文件包含，宏定义，函数前向声明
+
*/

#ifndef __MAP_IFO_H__
#define __MAP_IFO_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include "../SYS/systc.h"
#include "../IMAGE/image.h"

/*
+
-			结构体定义
+
*/
typedef struct {

	HBITMAP       m_hbmp[2];    // 地图源Bmp图像
	HDC	          m_memDc;		// 地图整体绘制完毕放入memDc中，在通过DrawMap绘入Image模块

}MAP, * PMAP;

/*
+
-			函数前向声明
+
*/

PMAP
InitMap(HINSTANCE, HWND);
// 初始化MAP实例

STATUS
FreeMap(PMAP);
// 释放MAP实例内存资源

STATUS
LoadMap(PMAP, HWND);
// 编辑地图存入MAP实例的memDc中

STATUS
DrawMap(PMAP, PIMAGE, HWND);
// 加载地图，从map实例绘入image实例

#ifdef __cplusplus
}
#endif

#endif // __MAP_IFO_H__ //