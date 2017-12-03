#pragma once
#include "monster.h"

class CCowCaptain : public CMonster
{
private:
	DWORD m_dwAttTime;
	DWORD m_dwTime;
	DWORD m_dwRandomTime;
	DWORD m_dwHitTime;
	DWORD m_dwRandomTime2;
	DWORD m_dwStunTime;
	int m_iRandom;
	bool m_bRandom;
	bool m_Rush;


private:
	Frame m_WakingFrame;
	Frame m_AttFrame1;
	Frame m_AttFrame2;
	Frame m_AttFrame3;
	Frame m_HitFrame;
	Frame m_DownFrame;
	Frame m_StunFrame;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void MoveFrame(void);
	void SetState(void);
	void HitMonster(eMONSTER_STATE _state);

public:
	CCowCaptain(void);
	virtual ~CCowCaptain(void);
};