#include "StdAfx.h"
#include "KeyMgr.h"
#include "Define.h"

CKeyMgr*	CKeyMgr::m_pInstance = NULL;

CKeyMgr::CKeyMgr(void)
	:m_dwKey(0)
{

}

CKeyMgr::~CKeyMgr(void)
{

}

void CKeyMgr::SetKeyState(void)
{
	m_dwKey = 0;

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dwKey |= KEY_RIGHT;
	}

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dwKey |= KEY_LEFT;
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000)	
	{
		m_dwKey |= KEY_UP;
	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)	
	{
		m_dwKey |= KEY_DOWN;
	}

	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_dwKey |= KEY_SPACE;
	}

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_dwKey |= KEY_RBUTTON;
	}

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_dwKey |= KEY_LBUTTON;
	}

	if(GetAsyncKeyState('Z') & 0x8000)
	{
		m_dwKey |= KEY_Z;
	}

	if(GetAsyncKeyState('X') & 0x8000)
	{
		m_dwKey |= KEY_X;
	}

	if(GetAsyncKeyState('C') & 0x8000)
	{
		m_dwKey |= KEY_C;
	}

	if(GetAsyncKeyState('I') & 0x8000)
	{
		m_dwKey |= KEY_I;
	}

	if(GetAsyncKeyState('M') & 0x8000)
	{
		m_dwKey |= KEY_M;
	}

	if(GetAsyncKeyState('A') & 0x8000)
	{
		m_dwKey |= KEY_A;
	}

	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_dwKey |= KEY_S;
	}

	if(GetAsyncKeyState('D') & 0x8000)
	{
		m_dwKey |= KEY_D;
	}

	if(GetAsyncKeyState('F') & 0x8000)
	{
		m_dwKey |= KEY_F;
	}

	if(GetAsyncKeyState('G') & 0x8000)
	{
		m_dwKey |= KEY_G;
	}

	if(GetAsyncKeyState('H') & 0x8000)
	{
		m_dwKey |= KEY_H;
	}

	if(GetAsyncKeyState('Q') & 0x8000)
	{
		m_dwKey |= KEY_Q;
	}

	if(GetAsyncKeyState('1') & 0x8000)
	{
		m_dwKey |= KEY_1;
	}

	if(GetAsyncKeyState('2') & 0x8000)
	{
		m_dwKey |= KEY_2;
	}

	if(GetAsyncKeyState('3') & 0x8000)
	{
		m_dwKey |= KEY_3;
	}

	if(GetAsyncKeyState('4') & 0x8000)
	{
		m_dwKey |= KEY_4;
	}

	if(GetAsyncKeyState('5') & 0x8000)
	{
		m_dwKey |= KEY_5;
	}

	if(GetAsyncKeyState('6') & 0x8000)
	{
		m_dwKey |= KEY_6;
	}


}
DWORD CKeyMgr::GetKeyState(void)
{
	return m_dwKey;
}