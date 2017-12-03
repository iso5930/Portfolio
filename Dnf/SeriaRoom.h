#pragma once
#include "scene.h"
#include "BitBmp.h"

class CSeriaRoom : public CScene
{
private:
	CBitBmp m_BackBuffer;
	Rect	m_ImageSize;
	bool    m_bTile;
	DWORD	m_dwTime;
	//vector<TILE*> m_vecTile;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void LoadData(void);
	void TileRender(void);

public:
	CSeriaRoom(void);
	virtual ~CSeriaRoom(void);
};