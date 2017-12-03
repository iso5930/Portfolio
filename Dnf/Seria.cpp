#include "StdAfx.h"
#include "Seria.h"
#include "ImageMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Store.h"
#include "SoundMgr.h"


CSeria::CSeria(void)
	: CObj("Seria", 400, 330, 160, 160), m_SeriaFrame(0,32,150)
{
	
}

CSeria::~CSeria(void)
{

}

void CSeria::Init(void)
{
	CImageMgr::GetInstance()->LoadImage("Seria", L"../Image/NPC/Seria.png");
	m_dwTime = GetTickCount();
	m_bMouseOver = false;
}

int CSeria::Progress(void)
{
	CObj::Progress();

	if(m_dwTime + m_SeriaFrame.dwFrameTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if(++m_SeriaFrame.iRenderFrame > m_SeriaFrame.iEndFrame)
		{
			m_SeriaFrame.iRenderFrame = m_SeriaFrame.iStartFrame;
		}
	}	
	POINT ptMouse = CMouse::GetMousePos();
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(PtInRect(&m_Collision,ptMouse))
	{
		m_bMouseOver = true;
		if(dwKey & KEY_LBUTTON)
		{
			CSoundMgr::GetInstance()->PlayNPCSound(L"seria_amb_01.ogg");
			CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
			((CStore*)pObj)->SetShowStore(true);
		}
	}
	else
		m_bMouseOver = false;
		
	return 0;
}

void CSeria::Render(HDC _hdc)
{
	//Rectangle(_hdc, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);
	if(m_bMouseOver)
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SeriaFrame.iRenderFrame, m_bMouseOver);
	CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SeriaFrame.iRenderFrame, 0);

}

void CSeria::Release(void)
{
	
}