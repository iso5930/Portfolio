#include "StdAfx.h"
#include "MyButton.h"
#include "ImageMgr.h"
#include "Mouse.h"

CMyButton::CMyButton(void)
{

}

CMyButton::CMyButton(string strName, float _fX, float _fY, float _fCX, float _fCY)
	:CObj(strName,_fX,_fY,_fCX,_fCY), m_iImage(0), m_ImageSize(int(_fX - _fCX / 2), int(_fY - _fCY / 2), (int)_fCX, (int)_fCY)
{
	
}

CMyButton::~CMyButton(void)
{

}

void CMyButton::Init(void)
{

}

int CMyButton::Progress(void)
{
	POINT	ptMouse = CMouse::GetMousePos();

	if(PtInRect( &GetRect(), ptMouse ))
	{
		m_iImage = 1;

		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(m_strName == "Start")
			{
				return 1;
			}
			else if(m_strName == "Edit")
			{
				return 2;
			}
			else
			{
				DestroyWindow(g_hwnd);
			}
		}
	}
	else
		m_iImage = 0;

	return 0;
}

void CMyButton::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(_hdc,m_strName,m_ImageSize,m_iImage,0);
}

void CMyButton::Release(void)
{

}