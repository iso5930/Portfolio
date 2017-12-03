#pragma once

#include "Define.h"
#include "BitBmp.h"

class CMainGame
{
private:
	HDC m_hdc;
	DWORD m_dwTime;
	TCHAR	m_szFps[128];
	int m_iFps;

public:
	void Init(void);
	int Progress(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};