/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 22：33
+
-             修改时间：2017.12.27 / 22：33
+
-             文件名称：image.h
+
-             模块：image模块，所有模块的图像都先绘入IMAGE实例的memDc中,再通过DrawImage画出
+
-             功能：image模块头文件，包括结构体定义，头文件包含，函数前向声明
+
*/
#ifndef __IMAGE_H__
#define __IMAGE_H__

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
-			结构体定义
+
*/
typedef struct {

	HDC     m_memDc;         // 所有模块的图像都先绘入IMAGE实例的memDc中,再通过DrawImage画出

}IMAGE, * PIMAGE;

/*
+
-			函数前向声明
+
*/

PIMAGE
InitImage(HWND);
// 初始化IMAGE实例

STATUS
FreeImage(PIMAGE);
// 释放PIMAGE实例资源

STATUS
DrawImage(const PIMAGE, HWND);
// 画出IMAGE实例中保存的图像

#ifdef __cplusplus
}
#endif

#endif // __IMAGE_H__ //
