#include "StdAfx.h"
#include "InterFace.h"
#include "ImageMgr.h"

CInterFace::CInterFace(void)
{
}

CInterFace::~CInterFace(void)
{
	Release();
}

void CInterFace::Init(void)
{
	m_iSize = 0;

	int iDamage = m_iDamage;

	while(iDamage > 0)
	{
		iDamage /= 10;
		++m_iSize;
	}

	for(int i = 1; i <= m_iSize; ++i)
	{
		iDamage = m_iDamage;
		int res = int(iDamage / pow(10.0f, m_iSize - i));
		m_vecDamage.push_back(res % 10);
	}

	m_dwTime = GetTickCount();
	m_Frame.iStartFrame = 0;
	m_Frame.iRenderFrame = 0;
	m_Frame.iEndFrame = 3;
	m_Frame.dwFrameTime = 200;
}

int CInterFace::Progress(void)
{
	--m_tInfo.fY;
	if(m_dwTime + m_Frame.dwFrameTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if(++m_Frame.iRenderFrame > m_Frame.iEndFrame)
		{
			return 1;
		}
	}
	return 0;
}

void CInterFace::Render(HDC _hdc)
{
	for(size_t i = 0; i < m_vecDamage.size(); ++i)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc,"Damage",Rect(int(m_tInfo.fX - g_Scroll.x) + i * 11, int(m_tInfo.fY), 17, 17), m_vecDamage[i], m_Frame.iRenderFrame);
	}
}

void CInterFace::Release(void)
{

}