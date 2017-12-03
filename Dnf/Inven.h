#pragma once
#include "obj.h"
#include "Item.h"

class CInven : public CObj
{
private:
	ITEM_VECTOR m_vecInven;
	ITEM_VECTOR m_vecEquip;
	RECT m_InvenCollision;
	RECT m_EquipCollision;
	RECT m_MoveCollision;
	RECT m_ExitCollision;
	bool m_bShowInven;
	float m_fDistX;
	int m_iIndex;
	int m_iEquitIndex;
	bool m_MouseClick;
	bool m_bItemSwap;
	DWORD m_dwEqipTime;
	bool m_bEquip;
	bool m_bWindow;
	DWORD m_dwClickTime;
	

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void ItemInfoSync(void);
	void AddItem(CItem* _Item);

public:
	void SetShowInven(bool _bInven) { m_bShowInven = _bInven; };
	bool GetShowInven(void){ return m_bShowInven; };
	ITEM_VECTOR* GetInven(void) { return &m_vecInven; };
	bool GetWindow(void) { return m_bWindow; };
	void SetWindow(bool _Window) { m_bWindow = _Window; };
	DWORD GetClickTime(void) { return m_dwClickTime; };
	ITEM_VECTOR* GetEqip(void) { return &m_vecEquip; };
	void SetMouseClick(bool _Mouse) { m_MouseClick = _Mouse; };

public:
	CInven(void);
	virtual ~CInven(void);
};