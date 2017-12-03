#pragma once
#include "monster.h"

class CBoss : public CMonster
{
private:
	Frame m_HitFrame;
	Frame m_MoveFrame;
	Frame m_Attack1;
	Frame m_Attack2;
	Frame m_Down;
	Frame m_FireFrame;
	
private:
	DWORD m_dwTime;
	DWORD m_dwRandomTime;
	DWORD m_dwAttTime;
	DWORD m_dwAttTime2;
	DWORD m_dwSkillTime;
	DWORD m_dwAttTime3;
	DWORD m_dwCreateTime;
	
private:	
	bool m_bStateChange;
	
	int m_iRandomPatton;
	int m_iCount;
	int m_iSkillCount;

public:
	void FrameMove(void);
	void SetState(void);
	bool RandomPatton(void);
	

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CBoss(void);
	virtual ~CBoss(void);
};