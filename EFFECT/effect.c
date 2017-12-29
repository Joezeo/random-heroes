/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.29 / 17：34
+
-             修改时间：2017.12.29 / 17：34
+
-             文件名称：effect.c
+
-             模块：特效模块，特效相关功能
+
-             功能：特效模块头文件，包括函数定义
+
*/

#include "effect.h"

/*
+
-			函数定义
+
*/

PCAPEFF
InitCoordSize() {

	PCAPEFF _pcapeff = (PCAPEFF)malloc(sizeof(CAPTURE_EFFECT));
	if (!_pcapeff)
		exit(OVERFLOW);

	FILE * _file = NULL;
	if (!fopen_s(&_file, "effect.txt", "r"))
		exit(FAILD);

	char _buf[16];
	int  n;

	for (int i = 0; i < 10; i++) {

		fgets(_buf, 16, (FILE *)_file);

		n = 100;
		for (int j = 0; j < 3; j++) {
		
			_pcapeff->m_bmpCoord[i].x += (*(_buf+ j) - 48) * n;
			n /= 10;

		}
		n = 100;
		for (int j = 4; j < 7; j++) {

			_pcapeff->m_bmpCoord[i].y += (*(_buf + j) - 48) * n;
			n /= 10;

		}
		n = 100;
		for (int j = 8; j < 11; j++) {

			_pcapeff->m_bmpSize[i].cx += (*(_buf + j) - 48) * n;
			n /= 10;

		}
		n = 100;
		for (int j = 12; j < 15; j++) {

			_pcapeff->m_bmpSize[i].cy += (*(_buf + j) - 48) * n;
			n /= 10;

		}

	}

	fclose(_file);

	return _pcapeff;

}
// CAPTURE_EFFECT回调函数，用于特效图片截取坐标，尺寸加载