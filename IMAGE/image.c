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

	_pimage->m_memDc = CreateCompatibleDC(_hdc);

	ReleaseDC(_hwnd, _hdc);

	return _pimage;

}
// 初始化IMAGE实例


STATUS
FreeImage(PIMAGE _pimage) {

	assert(_pimage != NULL);

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
		0, 0,
		SRCCOPY);

	ReleaseDC(_hwnd, _hdc);

	return OK;

}
// 画出IMAGE实例中保存的图像
