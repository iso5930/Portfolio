#include "StdAfx.h"
#include "Cutin.h"
#include "ImageMgr.h"
CCutin::CCutin(void)
	:m_CutinFrame(0, 30, 50)
{

}

CCutin::~CCutin(void)
{
	Release();
}


void CCutin::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("CUTIN", L"../Image/Cutin.bmp");
	m_bStart = false;
	m_bEnd = false;
	m_dwTime = GetTickCount();
}

int CCutin::Progress(void)
{
	if(m_bStart == false)
		return 0;
	if(m_bEnd)
		return 1;

	FrameMove();

	return 0;
}

void CCutin::Render(HDC _hdc)
{
	if(m_bStart)
	{
		HDC dcTemp = CreateCompatibleDC(GetDC(g_hwnd));
		HBITMAP		hBitMap = CreateCompatibleBitmap(GetDC(g_hwnd),800,600);

		HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitMap);

		BitBlt(dcTemp,0,0,800,600,_hdc,0,0,SRCCOPY);

		BLENDFUNCTION	tFunction;
		tFunction.BlendOp = AC_SRC_OVER;
		tFunction.BlendFlags = 0;
		tFunction.SourceConstantAlpha = 200; //Åõ¸íµµ
		tFunction.AlphaFormat = 0;

		CImageMgr::GetInstance()->ImageRender(dcTemp, "CUTIN", Rect(0,0,800,600),m_CutinFrame.iRenderFrame,0,123,123,123);

		AlphaBlend(_hdc, 0, 0, 800, 600, dcTemp,0,0,800,600,tFunction);
	}
}

void CCutin::Release(void)
{

}

void CCutin::FrameMove()
{
	if(m_dwTime + m_CutinFrame.dwFrameTime < GetTickCount())
	{
		m_dwTime = GetTickCount();
		if(++m_CutinFrame.iRenderFrame > m_CutinFrame.iEndFrame)
		{
			m_bEnd = true;
		}
	}
}