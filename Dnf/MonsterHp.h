#pragma once
#include "obj.h"

class CMonsterHp : public CObj
{
private:
	CObj* m_pObj;
	bool m_bShow;
	Rect m_HpSize;

public:
	void SetMonsterHp(CObj* _pMon) { m_pObj = _pMon; };
	
public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMonsterHp(void);
	virtual ~CMonsterHp(void);
};