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

	HDC     m_memDc;         // 所有模块的图像都先绘入IMAGE实例的memDc中

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
