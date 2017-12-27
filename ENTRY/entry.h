/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 12：54
+
-             修改时间：2017.12.27 / 12：54
+
-             文件名称：entry.h
+
-             模块：entry模块，程序主入口，游戏进程逻辑控制，消息队列处理
+
-             功能：entry模块头文件，包括宏定义，结构体定义，函数前向声明
+
*/

#ifndef __ENTRY_H__
#define __ENTRY_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
+
-			头文件包含
+
*/
#include <windows.h>
#include <assert.h>
#include "../RandomHeroes/resource.h"


/*
+
-			宏定义
+
*/

#define CLI_HEIGHT 384		// 客户区高度
#define CLI_WIDTH  640		// 客户区宽度


/*
+
-			结构体定义
+
*/
typedef struct {

	UINT    m_cliHeight;
	UINT    m_cliWidth;

}SYSTEM, SYS, * PSYS;


/*
+
-			函数前向定义
+
*/

LRESULT CALLBACK 
WndProc(HWND, UINT, WPARAM, LPARAM);
// gameWin 窗口消息处理函数

VOID
InitSystem(PSYS);
// 初始化结构体 SYSTEM

#ifdef __cplusplus
}
#endif

#endif // __ENTRY_H__ //
