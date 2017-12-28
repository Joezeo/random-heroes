/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.28 / 15：40
+
-             修改时间：2017.12.28 / 15：40
+
-             文件名称：mapifo.c
+
-             模块：map模块，地图的编辑，加载，绘制
+
-             功能：map模块源文件，包括函数定义
+
*/

#include "mapifo.h"

/*
+
-			静态函数前向声明
+
*/
static STATUS
__LoadFloor(HDC, HDC, HINSTANCE);
// 地图加载地砖



/*
+
-			函数定义
+
*/

PMAP
InitMap(HINSTANCE _hins, HWND _hwnd) {

	PMAP _pmap = (PMAP)malloc(sizeof(MAP));
	if (!_pmap)
		exit(OVERFLOW);

	HDC _hdc = GetDC(_hwnd);

	_pmap->m_hbmp[0]  = LoadBitmap(_hins, MAKEINTRESOURCE(IDB_CHAPTER_1));
	_pmap->m_hbmp[1]  = LoadBitmap(_hins, MAKEINTRESOURCE(IDB_CHAPTER_1_RETURN));
	_pmap->m_memDc = CreateCompatibleDC(_hdc);

	ReleaseDC(_hwnd, _hdc);

	return _pmap;

}
// 初始化MAP实例


STATUS
FreeMap(PMAP _pmap) {

	assert(_pmap != NULL);

	free(_pmap);
	_pmap = NULL;

	return OK;
	
}
// 释放MAP实例内存资源


STATUS
LoadMap(PMAP _pmap, HWND _hwnd, HINSTANCE _hins) {

	assert(_pmap != NULL);
	assert(_hwnd != NULL);

	HDC                     _hdc;
	HDC                     _tmpDc;
	HBITMAP                 _tmpHbmp;
	BITMAP                  _bmp;
	SHORT                   _index;

	_hdc = GetDC(_hwnd);
	_tmpDc = CreateCompatibleDC(_hdc);
	_tmpHbmp = CreateCompatibleBitmap(_hdc, 3 * CLI_WIDTH, CLI_HEIGHT);

	SelectObject(_pmap->m_memDc, _tmpHbmp);

	GetObject(_pmap->m_hbmp[0], sizeof(BITMAP), &_bmp);

	for (int i = 0; i < 3; i++) {

		if (i % 2 != 0)
			_index = 1;
		else
			_index = 0;

		SelectObject(_tmpDc, _pmap->m_hbmp[_index]);

		TransparentBlt(_pmap->m_memDc,
			i * (CLI_WIDTH), 0,
			CLI_WIDTH, CLI_HEIGHT - 32,
			_tmpDc,
			0, 0, // 源位置
			_bmp.bmWidth, _bmp.bmHeight,
			SRCCOPY);

	}

	__LoadFloor(_hdc, _pmap->m_memDc, _hins);

	ReleaseDC(_hwnd, _hdc);
	DeleteDC(_tmpDc);
	DeleteObject(_tmpHbmp);

	return OK;

}
// 编辑地图存入MAP实例的memDc中


STATUS
DrawMap(PMAP _pmap, PIMAGE _pimage, HWND _hwnd) {

	assert(_pmap != NULL);
	assert(_pimage != NULL);
	assert(_hwnd != NULL);

	HDC                 _hdc;
	HDC                 _tmpDc;

	_hdc     = GetDC(_hwnd);
	_tmpDc   = CreateCompatibleDC(_hdc);

	SelectObject(_pimage->m_memDc, _pimage->m_hBmp);

	SelectObject(_tmpDc, _pmap->m_hbmp);

	BitBlt(_pimage->m_memDc,
		0, 0,
		3 * CLI_WIDTH, CLI_HEIGHT,
		_pmap->m_memDc,
		0, 0,
		SRCCOPY);

	ReleaseDC(_hwnd, _hdc);
	DeleteDC(_tmpDc);

	return OK;


}
// 加载地图，从map实例绘入image实例


/*
+
-			静态函数定义
+
*/
static STATUS
__LoadFloor(HDC _hdc, HDC _memDc, HINSTANCE _hins) {

	HBITMAP _total = LoadBitmap(_hins, MAKEINTRESOURCE(IDB_ITEMS_SHEETS));
	HDC     _tmpDc = CreateCompatibleDC(_hdc);

	SelectObject(_tmpDc, _total);

	for (int i = 0; i < 60; i++) {
		
		BitBlt(_memDc,
			i * 32, CLI_HEIGHT - 32,
			32, 32,
			_tmpDc,
			0, 0,
			SRCCOPY);

	}
	return OK;

}
// 地图加载地砖