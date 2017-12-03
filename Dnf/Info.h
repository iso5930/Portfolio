#pragma once
#include "obj.h"

class CInfo : public CObj
{
private:
	vector<CItem*>* m_vecEquip;
	PlayerInfo* m_pPlayerInfo;
	bool m_bShowInfo;
	DWORD m_dwClickTime;
	float m_fDragX;
	RECT m_MoveCollision;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void SetShowInfo(bool _Info) { m_bShowInfo = _Info; };
	bool GetShowInfo(void) { return m_bShowInfo; };
	void CollisionSync(void);

public:
	CInfo(void);
	virtual ~CInfo(void);
};