#pragma once

#include "Obj.h"

class CItem : public CObj
{
private:
	ItemInfo m_tItemInfo;
	eITEM_TYPE m_eType;
	eITEM_RARE m_eRare;
	bool m_bStoreItem;
	bool m_bShowInfo;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	eITEM_TYPE GetItemType(void) { return m_eType; };
	eITEM_RARE GetItemRare(void) { return m_eRare; };
	ItemInfo* GetItemInfo(void) { return &m_tItemInfo; };
	bool GetShowInfo(void) { return m_bShowInfo; };
	bool GetStoreItem(void) { return m_bStoreItem; };

	void SetItemType(eITEM_TYPE _eType) { m_eType = _eType; };
	void SetItemRare(eITEM_RARE _Rare) { m_eRare = _Rare; }
	void SetItemInfo(ItemInfo _tInfo) { m_tItemInfo = _tInfo; };
	void SetShowInfo(bool _ShowInfo) { m_bShowInfo = _ShowInfo; };
	void SetStoreItem(bool _Store) { m_bStoreItem = _Store; };

public:
	CItem(void);
	CItem(string _strName, float _fx, float _fy, float _fcx, float _fcy, bool _Store = false);
	virtual ~CItem(void);
};