#include "StdAfx.h"
#include "Mouse.h"
#include "Define.h"

POINT	CMouse::m_ptMouse;

void CMouse::SetMousePos(void)
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hwnd, &m_ptMouse);
}

POINT CMouse::GetMousePos(void)
{
	return m_ptMouse;
}