#pragma once

class CMouse abstract
{
private:
	static	POINT		m_ptMouse;

public:
	static void		SetMousePos(void);
	static POINT	GetMousePos(void);
};