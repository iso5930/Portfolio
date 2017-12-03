#pragma once
#include "obj.h"

class CMonster : public CObj
{
protected:
	MonsterInfo m_tMonInfo;
	eMONSTER_STATE m_MonState;
	INFO m_tTargetInfo;
	bool m_bHit;
	bool m_bSuperArmor;

public:
	void SetbHit(bool _Hit) { m_bHit = _Hit; };
	eMONSTER_STATE GetMonState() { return m_MonState; }; 
	MonsterInfo* GetMonInfo(){ return &m_tMonInfo; };
	void SetMonState(eMONSTER_STATE _MonState) 
	{
		if(m_bSuperArmor == false)
		{
			m_MonState = _MonState; 
		}
	};

public:
	virtual void Init(void)		;
	virtual int Progress(void)	;
	virtual void Render(HDC _hdc)	;
	virtual void Release(void)	;

public:
	void TileCheck(void);
	void SetTargetInfo(INFO _tInfo){ m_tTargetInfo = _tInfo; };
	bool CowCaptain(void);
	bool GetSuperArmor(void) { return m_bSuperArmor; };

public:
	CMonster(void);
	CMonster(string strName, float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CMonster(void);
};