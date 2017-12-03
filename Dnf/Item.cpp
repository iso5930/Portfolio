#include "StdAfx.h"
#include "Item.h"
#include "ObjMgr.h"
#include "ImageMgr.h"

CItem::CItem(void)
{
	
}

CItem::CItem(string _strName, float _fx, float _fy, float _fcx, float _fcy, bool _Store)
{
	m_strName = _strName;
	m_tInfo.fX = _fx;
	m_tInfo.fY = _fy;
	m_tInfo.fCX = _fcx;
	m_tInfo.fCY = _fcy;
	m_bStoreItem = _Store;
}

CItem::~CItem(void)
{
	Release();
}

void CItem::Init(void)
{
	m_bShowInfo = false;
}

int CItem::Progress(void)
{

	return 0;
}

void CItem::Render(HDC _hdc)
{

	m_ImageSize.X = (int)m_tInfo.fX;
	m_ImageSize.Y = (int)m_tInfo.fY;
	m_ImageSize.Width = ITEMCX;
	m_ImageSize.Height= ITEMCY;

	CImageMgr::GetInstance()->ImageRender(_hdc,"Item", m_ImageSize, m_eType, m_eRare, 255, 0, 255);

	if(m_bShowInfo)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, "MouseOver", m_ImageSize, 0, 0, 255, 0, 255);
	}
	
	m_bShowInfo = false;
}

void CItem::Release(void)
{

}