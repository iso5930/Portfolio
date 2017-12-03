#pragma once

#include "Scene.h"
#include "Define.h"

class CSceneMgr
{
private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;
	SCENE_STATE				m_eType;
	bool					m_bChangeScene;

public:
	static CSceneMgr*		GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSceneMgr;
		}
		return m_pInstance;
	}

	static void DestroyInstance(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

public:
	void Init(void);
	int Progress(void);
	void Render(HDC _hdc);
	void Release(void);

public:
	void SetScene(SCENE_STATE eState);
	void ChangeScene(SCENE_STATE eState);
	CScene* GetScene(void) { return m_pScene; };

private:
	CSceneMgr(void);

public:
	~CSceneMgr(void);
};