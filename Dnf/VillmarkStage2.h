#pragma once
#include "scene.h"
#include "BitBmp.h"

class CVillmarkStage2 : public CScene
{
private:
	CBitBmp m_BackBuffer;
	DWORD m_dwTime;
	Frame m_GateFrame;

public:
	void MapLoad(void);
	void FrameMove(void);

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CVillmarkStage2(void);
	virtual ~CVillmarkStage2(void);
};