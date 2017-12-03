#include "StdAfx.h"
#include "RenderMgr.h"
#include "Inven.h"
#include "Store.h"
#include "HUD.h"

CRenderMgr* CRenderMgr::m_pInstance = NULL;

CRenderMgr::CRenderMgr(void)
{

}

CRenderMgr::~CRenderMgr(void)
{

}

void CRenderMgr::RenderObj(HDC _hdc)
{
	multimap<float, CObj*>::iterator iter = m_mapObj.begin();
	multimap<float, CObj*>::iterator iter_end = m_mapObj.end();

	for(iter; iter != iter_end; ++iter)
	{
		iter->second->Render(_hdc);
	}
}

void CRenderMgr::RenderUI(HDC _hdc)
{
	multimap<DWORD, CObj*>::iterator iter = m_mapUI.begin();
	multimap<DWORD, CObj*>::iterator iter_end = m_mapUI.end();

	for(iter; iter != iter_end; ++iter)
	{
		iter->second->Render(_hdc);
	}
}

void CRenderMgr::AddObj(CObj* _pObj)
{
	m_mapObj.insert( make_pair( (float)_pObj->GetShadowCollision().bottom, _pObj) );
}

void CRenderMgr::AddUI(CObj* _pUI)
{
	if(typeid(*_pUI) == typeid(CInven))
	{
		m_mapUI.insert( make_pair( ((CInven*)_pUI)->GetClickTime(), _pUI ) );
	}
	else if(typeid(*_pUI) == typeid(CStore))
	{
		m_mapUI.insert( make_pair( ((CStore*)_pUI)->GetClickTime(), _pUI ) );
	}	
	else
	{
		m_mapUI.insert( make_pair( ((CHUD*)_pUI)->GetClickTime(), _pUI) );
	}
}

void CRenderMgr::ObjClear(void)
{
	m_mapUI.clear();
	m_mapObj.clear();
}