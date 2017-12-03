#include "StdAfx.h"
#include "Info.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Item.h"
#include "Inven.h"
#include "ImageMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
CInfo::CInfo(void)
	:CObj("Info", 190, 120, 266, 214)
{

}

CInfo::~CInfo(void)
{
	Release();
}

void CInfo::Init(void)
{
	CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

	m_pPlayerInfo = ((CPlayer*)pObj)->GetPlayerInfo();

	pObj = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();

	m_vecEquip = ((CInven*)pObj)->GetEqip();

	//장비창과 플레이어 정보 연결
	CImageMgr::GetInstance()->LoadBmp("Info", L"../Image/Player/Info.bmp");

	m_bShowInfo = false;
	m_dwClickTime = GetTickCount();
}

int CInfo::Progress(void)
{
	if(m_bShowInfo == false)
		return 0;

	CObj::Progress();

	CollisionSync();

	POINT ptMouse = CMouse::GetMousePos();

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!dwKey)
	{
		m_fDragX = abs(ptMouse.x - m_tInfo.fX);
	}

	if(PtInRect(&m_MoveCollision,ptMouse))
	{
		if(dwKey & KEY_LBUTTON)
		{
			m_dwClickTime = GetTickCount();
			if(m_tInfo.fX > ptMouse.x)
			{
				m_tInfo.fX = ptMouse.x + m_fDragX;
			}
			else
			{
				m_tInfo.fX = ptMouse.x - m_fDragX;
			}
			m_tInfo.fY = float(ptMouse.y) + 97;
		}
	}
	return 0;
}

void CInfo::Render(HDC _hdc)
{
	if(m_bShowInfo == false)
		return;

	CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize,0,0,255,0,255);
	//Rectangle(_hdc,m_MoveCollision.left, m_MoveCollision.top, m_MoveCollision.right, m_MoveCollision.bottom);

	TCHAR szPlayerHp[128] = L"";

	wsprintf(szPlayerHp,L"%d", m_pPlayerInfo->iHp);

	TextOut(_hdc, int(m_tInfo.fX - 30), int(m_tInfo.fY + 35), szPlayerHp, lstrlen(szPlayerHp));

	TCHAR szPlayerInt[128] = L"";

	wsprintf(szPlayerInt,L"%d", m_pPlayerInfo->iInt);

	TextOut(_hdc, int(m_tInfo.fX - 35), int(m_tInfo.fY + 62), szPlayerInt, lstrlen(szPlayerInt));

}

void CInfo::Release(void)
{
	
}

void CInfo::CollisionSync(void)
{
	m_MoveCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
	m_MoveCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2);
	m_MoveCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
	m_MoveCollision.bottom = long((m_tInfo.fY - m_tInfo.fCY / 2) + 30);
}