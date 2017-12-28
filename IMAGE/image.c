/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.27 / 22：33
+
-             修改时间：2017.12.27 / 22：33
+
-             文件名称：image.c
+
-             模块：image模块，所有模块的图像都先绘入IMAGE实例的memDc中,再通过DrawImage画出
+
-             功能：image模块头文件，包括函数定义
+
*/
#include "image.h"

/*
+
-			函数定义
+
*/

PIMAGE
InitImage(HWND _hwnd) {

	PIMAGE _pimage = (PIMAGE)malloc(sizeof(IMAGE));
	if (!_pimage)
		exit(OVERFLOW);

	HDC _hdc = GetDC(_hwnd);

	_pimage->m_memDc        = CreateCompatibleDC(_hdc);
	_pimage->m_hBmp         = CreateCompatibleBitmap(_hdc, 3 * CLI_WIDTH, CLI_HEIGHT);
	_pimage->m_drawLocation = 0;

	ReleaseDC(_hwnd, _hdc);

	return _pimage;

}
// 初始化IMAGE实例


STATUS
FreeImage(PIMAGE _pimage) {

	assert(_pimage != NULL);

	DeleteObject(_pimage->m_hBmp);
	DeleteDC(_pimage->m_memDc);

	free(_pimage);
	_pimage = NULL;

	return OK;

}
// 释放PIMAGE实例资源


STATUS
DrawImage(const PIMAGE _pimage, HWND _hwnd) {

	HDC                  _hdc;

	_hdc = GetDC(_hwnd);

	BitBlt(_hdc,
		0, 0,
		CLI_WIDTH, CLI_HEIGHT,
		_pimage->m_memDc,
		_pimage->m_drawLocation, 0,
		SRCCOPY);

	ReleaseDC(_hwnd, _hdc);

	return OK;

}
// 画出IMAGE实例中保存的图像
