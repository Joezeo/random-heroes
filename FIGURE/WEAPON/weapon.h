/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.28 / 22：26
+
-             修改时间：2017.12.30 / 14：46
+
-             文件名称：weapon.h
+
-             模块：武器模块，武器相关功能，信息
+
-             功能：武器模块头文件，包括头文件包含，宏定义，函数定义等等
+
*/

#ifndef __WEAPON_H__
#define __WEAPON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 
+
-			包含头文件
+
*/
#include "../../SYS/systc.h"


/*
+
-			结构体定义
+
*/
typedef enum {

	WEAPON_9MM = 110,

}WEAPON_TYPE;

typedef struct {

	HBITMAP     m_weaponHbmp;

}WEAPON, * PWEAPON;

/*
+
-			函数前向声明
+
*/
PWEAPON
InitWeapon(HINSTANCE, WEAPON_TYPE);
// 初始化WEAPON实例

STATUS
FreeWeapon(PWEAPON);
// 释放武器内存资源

STATUS
DrawWeapon(PWEAPON, HDC, HDC, POINT);
// 根据角色所在位置画出武器


#ifdef __cplusplus
}
#endif

#endif // __WEAPON_H__ //