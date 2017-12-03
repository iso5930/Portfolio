#pragma once

class CBitBmp
{
private:
	HDC			m_hdc, m_MemDc;
	HBITMAP		m_bitmap, m_oldbitmap;

public:
	HDC	GetMemDC(void)
	{
		return m_MemDc;
	}

public:
	CBitBmp*	LoadBmp(PTCHAR pFileName);
	void		Release(void);

public:
	CBitBmp(void);
	~CBitBmp(void);
};