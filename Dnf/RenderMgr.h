#pragma once
#include "Obj.h"

class CRenderMgr
{
private:
	static CRenderMgr* m_pInstance;

public:
	static CRenderMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CRenderMgr;

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

private:
	multimap<DWORD, CObj*> m_mapUI;
	multimap<float, CObj*> m_mapObj;

public:
	void RenderObj(HDC _hdc);
	void RenderUI(HDC _hdc);
	void AddObj(CObj* _pObj);
	void AddUI(CObj* _pUI);
	void ObjClear(void);

private:
	CRenderMgr(void);

public:
	~CRenderMgr(void);
};