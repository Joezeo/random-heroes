/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.30 / 17：16
+
-             修改时间：2017.12.30 / 17：16
+
-             文件名称：roleifo.c
+
-             模块：role.ifo模块，角色的游戏性信息，包括武器信息，人物信息，金钱信息等等
+
-             功能：role.ifo模块源文件，包括函数的定义
+
*/

#include "roleifo.h"

/*
+
-			函数定义
+
*/

PROLEIFO
LoadRoleInfo() {

	PROLEIFO _proleifo = (PROLEIFO)malloc(sizeof(ROLE_INFORMATON));
	if (!_proleifo)
		exit(OVERFLOW);

	_proleifo->m_weaponType = WEAPON_9MM;
	_proleifo->m_weapon = LoadWeapon(g_hinst, _proleifo->m_weaponType);

	return _proleifo;

}
// 初始化角色的信息


STATUS
FreeRoleInfo(PROLEIFO _proleifo) {

	assert(_proleifo != NULL);

	free(_proleifo);
	_proleifo = NULL;

	return OK;

}
// 释放PROLEIFO占用的内存资源