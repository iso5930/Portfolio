#pragma once
#include "Scene.h"
#include "BitBmp.h"

class CVillmark : public CScene
{
private:
	CBitBmp m_BackBuffer;
	Frame m_GateFrame;
	DWORD m_dwTime;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void VillMarkLoadData1(void);
	void FrameMove(void);
	
public:
	CVillmark(void);
	virtual ~CVillmark(void);
};