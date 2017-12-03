#pragma once

#include "Define.h"
#include "Obj.h"

class CObjMgr
{
private:
	static CObjMgr* m_pInstance;
	OBJ_LIST m_listObj[OBJ_END];

public:
	static CObjMgr*		GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CObjMgr;
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
	OBJ_LIST* GetList(void) { return m_listObj; }

private:
	CObjMgr(void);

public:
	~CObjMgr(void);
};