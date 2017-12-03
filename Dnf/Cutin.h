#pragma once
#include "obj.h"

class CCutin : public CObj
{
private:
	bool m_bStart;
	bool m_bEnd;
	Frame m_CutinFrame;
	
	DWORD m_dwTime;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	void FrameMove(void);
	void SetStart(bool _start) { m_bStart = _start; };

public:
	CCutin(void);
	virtual ~CCutin(void);
};