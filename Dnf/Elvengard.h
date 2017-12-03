#pragma once
#include "scene.h"
#include "BitBmp.h"

class CElvengard : public CScene
{
private:
	//vector<TILE*> m_vecTile;
	CBitBmp m_BackBuffer;
	DWORD m_dwTime;
	bool m_bTile;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void ElvenLoadData(void);
	void TileRender(void);

public:
	CElvengard(void);
	virtual ~CElvengard(void);
};