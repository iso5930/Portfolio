#pragma once
#include "monster.h"

class CBloodLugaru : public CMonster
{
private:
	DWORD m_dwTime;
	DWORD m_dwTargetTime;
	DWORD m_dwAttTime1;
	DWORD m_dwAttTime2;
	DWORD m_dwAttTime3;
	DWORD m_dwHitTime;
	DWORD m_dwRandomTime;
	int m_iRandom;
	RECT rcPlayer;
	int m_iCount;

	float m_fTime;
	bool m_bJump;

private:
	Frame m_WakingFrame;
	Frame m_AttFrame1;
	Frame m_AttFrame2;
	Frame m_AttFrame3;
	Frame m_HitFrame;
	Frame m_DownFrame;

public:
	void FrameMove(void);
	void Jump(void);

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CBloodLugaru(void);
	virtual ~CBloodLugaru(void);
};