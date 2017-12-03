#pragma once
#include "scene.h"

class CLogo : public CScene
{
private:
	HWND	m_hVideo;
	DWORD   m_dwTime;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CLogo(void);
	virtual ~CLogo(void);
};