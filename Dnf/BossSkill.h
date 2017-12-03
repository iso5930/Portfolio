#pragma once
#include "obj.h"

class CBossSkill : public CObj
{
private:
	Frame m_CurFrame;
	Frame m_SkillFrame;
	DWORD m_dwTime;
	bool m_bCreate;
	bool m_bDeath;
	bool m_bHit;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void MoveFrame(void);

public:
	CBossSkill(void);
	virtual ~CBossSkill(void);
};