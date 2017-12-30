/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.28 / 22：26
+
-             修改时间：2017.12.30 / 14：45
+
-             文件名称：weapon.c
+
-             模块：武器模块，武器相关功能，信息
+
-             功能：武器模块头文件，包括函数定义
+
*/

#include "weapon.h"

PWEAPON
LoadWeapon(HINSTANCE _hins, WEAPON_TYPE _type) {

	PWEAPON _pweapon = (PWEAPON)malloc(sizeof(WEAPON));
	if (!_pweapon)
		exit(OVERFLOW);

	_pweapon->m_weaponHbmp_forward  = LoadBitmap(_hins, MAKEINTRESOURCE(_type));
	_pweapon->m_weaponHbmp_backward = LoadBitmap(_hins, MAKEINTRESOURCE(_type + 1));

	return _pweapon;

}
// 初始化WEAPON实例


STATUS
FreeWeapon(PWEAPON _pweapon) {

	assert(_pweapon != NULL);

	free(_pweapon);
	_pweapon = NULL;

	return OK;

}
// 释放武器内存资源


STATUS
DrawWeapon(PWEAPON _pweapon, HDC _hdc, HDC _memDc,
	POINT _rolePos, BOOL _mvDirection) {

	assert(_pweapon != NULL);
	assert(_hdc != NULL);
	assert(_memDc != NULL);

	HDC            _tmpDc;
	BITMAP         _bmp;
	POINT          _weaponPos;

	_tmpDc = CreateCompatibleDC(_hdc);

	if (_mvDirection) {

		_weaponPos.x = _rolePos.x + FORWARD_WEAPON_X_OFFSET;
		_weaponPos.y = _rolePos.y + FORWARD_WEAPON_Y_OFFSET;

		SelectObject(_tmpDc, _pweapon->m_weaponHbmp_forward);

	}
	else {

		_weaponPos.x = _rolePos.x + BACKWARD_WEAPON_X_OFFSET;
		_weaponPos.y = _rolePos.y + BACKWARD_WEAPON_Y_OFFSER;

		SelectObject(_tmpDc, _pweapon->m_weaponHbmp_backward);

	}

	GetObject(_pweapon->m_weaponHbmp_forward, sizeof(BITMAP), &_bmp);

	TransparentBlt(_memDc,
		_weaponPos.x, _weaponPos.y,
		_bmp.bmWidth, _bmp.bmHeight,
		_tmpDc,
		0, 0,
		_bmp.bmWidth, _bmp.bmHeight,
		RGB(255, 255, 255));

	DeleteDC(_tmpDc);

	return OK;

}
// 根据角色所在位置画出武器
