#pragma once
#include "obj.h"

class CSeria : public CObj
{
private:
	Frame	m_SeriaFrame;
	DWORD	m_dwTime;
	bool    m_bMouseOver;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CSeria(void);
	virtual ~CSeria(void);
};