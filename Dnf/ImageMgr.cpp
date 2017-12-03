#include "StdAfx.h"
#include "ImageMgr.h"
#include "Define.h"

CImageMgr* CImageMgr::m_pInstance = NULL;

CImageMgr::CImageMgr(void)
	:graphics(GetDC(g_hwnd))
{
	
}

CImageMgr::~CImageMgr(void)
{
	Release();
}	

void CImageMgr::Init()
{
	GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput,NULL);
}

int CImageMgr::Progress()
{
	return 0;
}

void CImageMgr::Render()
{
	
}

void CImageMgr::Release()
{
	map<string,Image*>::iterator iter = m_ImageMap.begin();
	map<string,Image*>::iterator iter_end = m_ImageMap.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE((iter->second));
	}
	m_ImageMap.clear();


	map<string,CBitBmp*>::iterator iter2 = m_BmpMap.begin();
	map<string,CBitBmp*>::iterator iter_end2 = m_BmpMap.end();

	for(iter2; iter2 != iter_end2; ++iter2)
	{
		SAFE_DELETE((iter2->second));
	}
	
	m_BmpMap.clear();

	GdiplusShutdown(m_GdiplusToken);
}