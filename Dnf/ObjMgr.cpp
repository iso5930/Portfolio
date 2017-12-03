#include "StdAfx.h"
#include "ObjMgr.h"
#include "RenderMgr.h"

CObjMgr* CObjMgr::m_pInstance = NULL;

CObjMgr::CObjMgr(void)
{

}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::Init(void)
{
	
}

int CObjMgr::Progress(void)
{
	for(int i = 0; i < OBJ_PLAYER; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end;)
		{
			if((*iter)->Progress() == 1)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for(int i = OBJ_PLAYER; i < OBJ_INVEN; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end;)
		{
			if((*iter)->Progress() == 1)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
			{
				CRenderMgr::GetInstance()->AddObj(*iter);
				++iter;
			}
		}
	}
	for(int i = OBJ_INVEN; i < OBJ_INTERFACE; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Progress();

			CRenderMgr::GetInstance()->AddUI(*iter);
		}
	}

	for(int i = OBJ_INTERFACE; i < OBJ_END; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end;)
		{
			if((*iter)->Progress() == 1)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;			
		}
	}
	return 0;
}

void CObjMgr::Render(HDC _hdc)
{
	for(int i = 0; i < OBJ_PLAYER; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}

	CRenderMgr::GetInstance()->RenderObj(_hdc);

	CRenderMgr::GetInstance()->RenderUI(_hdc);

	CRenderMgr::GetInstance()->ObjClear();

	for(int i = OBJ_INTERFACE; i < OBJ_END; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
	//여기서 랜더 매니저가 순서대로 뿌려주면 끝!
}

void CObjMgr::Release(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		OBJ_ITER iter = m_listObj[i].begin();
		OBJ_ITER iter_end = m_listObj[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			SAFE_DELETE((*iter));
		}
		m_listObj[i].clear();
	}
}