#pragma once
#include "scene.h"
#include "BitBmp.h"

class CMyEdit :	public CScene
{
private:
	CBitBmp m_BackBuffer;
	vector<TILE*> m_vecTile;
	Rect m_TileSize;
	int m_iOption;
	POINT				m_ptScroll;
	eEDIT_TYPE m_eEditType;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void ElvenEdit();
	void VillMarkEdit1();
	void VillMarkEdit2();
	void BossRoomEdit();

public:
	void SaveData();
	void LoadData();
	void ElvenSaveData();
	void ElvenLoadData();
	void VillMarkSaveData1();
	void VillMarkLoadData1();
	void VillMarkSaveData2();
	void VillMarkLoadData2();
	void BossRoomLoadData();
	void BossRoomSaveData();

public:
	CMyEdit(void);
	virtual ~CMyEdit(void);
};