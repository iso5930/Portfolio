#pragma once
#include "Obj.h"

class CCollisionMgr
{
private:
	static CCollisionMgr* m_pInstance;

public:
	static CCollisionMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CCollisionMgr;

		return m_pInstance;
	}

	static void DestroyInstance(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	CObj* m_pPlayer;
	list<CObj*>* m_pMonsterList;
	vector<TILE*>* m_vecTile;
	DWORD m_dwHitTime;

public:
	void SetMonsterList(list<CObj*>* _pMonsterList) { m_pMonsterList = _pMonsterList; };
	void SetPlayer(CObj* _Player){ m_pPlayer = _Player; }
	void SetTile(vector<TILE*>* _vecTile) { m_vecTile = _vecTile; }
		
public:
	bool RectToRect(RECT _Rect, RECT _Rect2);

public:
	int Progress(void);
	void Init(void);


public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};