#pragma once
#include "scene.h"
#include "BitBmp.h"

class CBossRoom : public CScene
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
	void BossRoomLoadData(void);
	void FrameMove(void);

public:
	CBossRoom(void);
	virtual ~CBossRoom(void);
};