/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.30 / 17：16
+
-             修改时间：2017.12.30 / 17：16
+
-             文件名称：roleifo.h
+
-             模块：role.ifo模块，角色的游戏性信息，包括武器信息，人物信息，金钱信息等等
+
-             功能：role.ifo模块的头文件，包括头文件包含，宏定义，结构体定义，函数前向声明
+
*/

#ifndef __ROLE_IFO_H__
#define __ROLE_IFO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 
+
-			包含头文件
+
*/
#include "../../SYS/systc.h"
#include "../WEAPON/weapon.h"

extern HINSTANCE                 g_hinst;

/*
+
-			宏定义
+
*/
// 暂时用常量保存角色游戏性的信息，之后改为本地保存
#define ROLE_INFO LoadRoleInfo()


/*
+
-			结构体定义
+
*/
typedef struct {

	WEAPON_TYPE m_weaponType; // 角色武器种类
	PWEAPON     m_weapon;     // 角色的武器图片信息
	
}ROLE_INFORMATON, * PROLEIFO;

/*
+
-			函数前向声明
+
*/
PROLEIFO
LoadRoleInfo();
// 初始化角色的信息

STATUS
FreeRoleInfo(PROLEIFO);
// 释放PROLEIFO占用的内存资源

#ifdef __cplusplus
}
#endif

#endif // __ROLE_IFO_H__ //
