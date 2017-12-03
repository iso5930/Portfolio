#ifndef _CONSTANT_H_
#define _CONSTANT_H_

extern HWND g_hwnd;
extern POINT g_Scroll;

const int WINCX = 800;
const int WINCY = 600;

const int ITEMCX = 28;
const int ITEMCY = 28;

const int INVEN_X = 8;
const int INVEN_Y = 7;

const int TILECX = 50;
const int TILECY = 50;

const int SERIA_TILE_X = 16;
const int SERIA_TILE_Y = 12;

const DWORD KEY_LEFT	= 0x00000001;
const DWORD KEY_RIGHT	= 0x00000002;
const DWORD KEY_UP		= 0x00000004;
const DWORD KEY_DOWN	= 0x00000008;
const DWORD KEY_SPACE	= 0x00000010;
const DWORD KEY_RBUTTON	= 0x00000020;
const DWORD KEY_LBUTTON	= 0x00000040;

//스킬 공격 점프
const DWORD KEY_Z		= 0x00000080;
const DWORD KEY_X		= 0x00000100;
const DWORD KEY_C		= 0x00000200;

//단축키
const DWORD KEY_I		= 0x00000400;
const DWORD KEY_M		= 0x00000800;
const DWORD KEY_K		= 0x00001000;

const DWORD KEY_A		= 0x00002000;
const DWORD KEY_S		= 0x00004000;
const DWORD KEY_D		= 0x00008000;
const DWORD KEY_F		= 0x00010000;
const DWORD KEY_G		= 0x00020000;
const DWORD KEY_H		= 0x00040000;
//스킬 단축키

const DWORD KEY_1		= 0x00080000;
const DWORD KEY_2		= 0x00100000;
const DWORD KEY_3		= 0x00200000;
const DWORD KEY_4		= 0x00400000;
const DWORD KEY_5		= 0x00800000;
const DWORD KEY_6		= 0x01000000;
//퀵슬롯 단축키

//추가 슬롯
const DWORD	KEY_Q       = 0x02000000;

const DWORD RUN_FIRE	= 0x00000001;
const DWORD RUN_DARK	= 0x00000002;
const DWORD RUN_ICE		= 0x00000004;
const DWORD RUN_LIGHT	= 0x00000008;

#endif