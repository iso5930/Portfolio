#pragma once
#include "obj.h"
#include "Item.h"
#include "ImageMgr.h"
#include "ObjMgr.h"

class CStore : public CObj
{
private:
	ITEM_VECTOR m_vecStore;
	RECT m_MoveCollision;
	RECT m_ItemBuyCollision;
	RECT m_ExitCollision;
	bool m_bShowStore;
	float m_fDragX;
	DWORD dwBuyTime;
	bool m_bWindow;
	DWORD m_dwClickTime;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	bool GetShowStore(void) { return m_bShowStore; };
	void SetShowStore(bool _ShowStore) { m_bShowStore = _ShowStore; }
	bool GetWindow(void) { return m_bWindow; };
	void SetWindow(bool _Window) { m_bWindow = _Window; };
	DWORD GetClickTime(void) { return m_dwClickTime; };
	RECT GetBuyCollision(void) { return m_ItemBuyCollision; }

public:
	void SetCollision(void);

public:
	CStore(void);
	virtual ~CStore(void);
};