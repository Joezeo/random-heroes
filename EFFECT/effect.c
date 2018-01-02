/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.29 / 17：34
+
-             修改时间：2017.12.30 / 14：47
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

	for (int i = 0; i < CNT_EFFECTS; i++) {

		_pcapeff->m_bmpCoord[i].x = 0;
		_pcapeff->m_bmpCoord[i].y = 0;
		_pcapeff->m_bmpSize[i].cx = 0;
		_pcapeff->m_bmpSize[i].cy = 0;

	}

	FILE * _file = NULL;
	if (fopen_s(&_file, "../EFFECT/effect", "r"))
		exit(FAILD);

	char _buf[17];
	int  n;

	for (int i = 0; fgets(_buf, 17, (FILE *)_file) != NULL; i++) {

		n = 100;
		for (int j = 0; j < 3; j++) {

			_pcapeff->m_bmpCoord[i].x += (*(_buf + j) - 48) * n;
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
// 用于特效图片截取坐标，尺寸加载
// 从EFFECT目录下的effct文件中读取数据


STATUS
DrawEffect(HDC _hdc, HDC _memDc, const POINT _pos, const UINT _effct_id) {

	assert(_hdc != NULL);
	assert(_memDc != NULL);
	assert(_effct_id >= 0 && _effct_id < CNT_EFFECTS);

	HDC       _tmpDc = CreateCompatibleDC(_hdc);

	SelectObject(_tmpDc, ALL_EFFECTS);

	TransparentBlt(_memDc,
		_pos.x, _pos.y,
		(EFF_SIZE + _effct_id)->cx, (EFF_SIZE + _effct_id)->cy,
		_tmpDc,
		(EFF_POS + _effct_id)->x, (EFF_POS + _effct_id)->y,
		(EFF_SIZE + _effct_id)->cx, (EFF_SIZE + _effct_id)->cy,
		RGB(255, 255, 255));

	DeleteDC(_tmpDc);

	return OK;

}
// 根据传入的位置，特效id，画出特效


STATUS
FreeCapEffct(PCAPEFF _pcapeff) {

	assert(_pcapeff != NULL);

	free(_pcapeff);
	_pcapeff = NULL;

	return OK;

}
// 释放PCAPEFF内存资源