/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 15：18
+
-             修改时间：2017.12.27 / 15：18
+
-             文件名称：systc.c
+
-             模块：system模块，游戏主系统功能，状态码定义，所有文件都需包括此模块
+
-             功能：system模块头文件，包括函数定义
+
*/
#include "systc.h"

STATUS
InitSystem(PSYS _psys) {

	assert(_psys != NULL);

	_psys->m_cliHeight = CLI_HEIGHT;
	_psys->m_cliWidth = CLI_WIDTH;

	return OK;

}