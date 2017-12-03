#pragma once

#include "Define.h"

class CScene
{
private:
	SCENE_STATE m_eSceneState;

protected:
	vector<TILE*> m_vecTile;

public:
	SCENE_STATE GetSceneState(void) { return m_eSceneState; };
	void SetSceneState(SCENE_STATE _eState) { m_eSceneState = _eState; };

public:
	virtual void Init(void)		PURE;
	virtual int Progress(void)	PURE;
	virtual void Render(HDC _hdc)	PURE;
	virtual void Release(void)	PURE;

public:
	vector<TILE*>* GetTile(void) { return &m_vecTile; };

public:
	CScene(void);
	virtual ~CScene(void);
};