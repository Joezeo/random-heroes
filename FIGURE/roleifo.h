/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 15：21
+
-             修改时间：2017.12.27 / 15：21
+
-             文件名称：roleifo.h
+
-             模块：role模块，关于游戏角色的模块，包括角色的控制，绘制，状态等
+
-             功能：role模块头文件，包括结构体定义，头文件包含，函数前向声明，宏定义
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
#include "../SYS/systc.h"
#include "../IMAGE/image.h"


/*
+
-			结构体定义
+
*/

typedef struct {

	HBITMAP m_hbmp;        // 角色的图像
	UINT    m_status;      // 角色移动状态（0，1，2分别代表行走，落下，起跳）
	UINT    m_index;       // 用于角色移动状态下，裁剪人物图像(0，1，2三种状态)
	UINT    m_speed;       // 角色移动速度
	UINT    m_keyDownCnt;  // 按键次数，辅助改变角色的图像
	UINT    m_maxHeight;   // 角色最大跳跃高度
	UINT    m_curHeight;   // 角色当前跳跃高度
	BOOL    m_highStatus;  // 跳跃后是否达到最大高度
	SIZE    m_size;        // 角色大小
	POINT   m_pos;         // 角色位置
	RECT    m_rectClean;   // 调用InvalidateRect函数时，需要清屏的图像区域

}ROLE, * PROLE;

/*
+
-			函数前向声明
+
*/

PROLE
InitRole(HINSTANCE);
// 初始化ROLE结构体实例

STATUS
FreeRole(PROLE);
// 释放ROLE实例资源

STATUS
DrawRole(const HWND, const PROLE, PIMAGE);
// 画出角色

STATUS
ControlRole(PROLE, WPARAM, HWND, PSYS);
// 角色控制，移动跳跃

STATUS
RoleJumpProc(PROLE, HWND);
// 角色跳跃过程控制


#ifdef __cplusplus
}
#endif

#endif // __ROLE_IFO_H__ //
