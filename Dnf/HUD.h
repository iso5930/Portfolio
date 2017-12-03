#pragma once
#include "Obj.h"
#include "Item.h"
#include "Skill.h"

class CHUD : public CObj
{
private:
	Rect m_HpSize;
	Rect m_MpSize;
	Rect m_QuickSlot;
	Rect m_SkillQuickSlot;
	RECT m_QuickSlotCollision;
	float m_fHpCurrY;
	float m_fHpCurrHeight;
	float m_fMpCurrY;
	float m_fMpCurrHeight;
	DWORD m_dwClickTime;
	DWORD m_dwChangeTime;
	int m_iQuickSlotIndex;
	bool m_bWindow;
	bool m_bMouseClick;

private:
	vector<CItem*> m_vecQuickSlot;
	vector<CSkill*> m_vecSkillSlot;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void QuickSlotSync(void);
	void HpAndMpSync(void);
	void QuickItemUse(int _iIndex);

public:
	DWORD GetClickTime(void) { return m_dwClickTime; };
	vector<CItem*>* GetQuickSlot(void) { return &m_vecQuickSlot; };
	bool GetWindow(void) { return m_bWindow; };
	void SetWindow(bool _Window) { m_bWindow = _Window; };
	
public:
	CHUD(void);
	virtual ~CHUD(void);
};