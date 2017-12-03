#include "StdAfx.h"
#include "Combo.h"
#include "ImageMgr.h"

CCombo::CCombo(void)
	:CObj("Combo",700,300,37,37)
{ 

}

CCombo::~CCombo(void)
{
	Release();
}
void CCombo::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("Combo",L"../Image/UI/HitCombo.bmp");
	CImageMgr::GetInstance()->LoadBmp("ComboFont", L"../Image/UI/ComboFont.bmp");

	m_dwComboTime = GetTickCount();

	m_iCombo = 0;
}

int CCombo::Progress(void)
{
	m_iSize = 0;

	if(m_iCombo == 0)
		return 0;

	if(m_dwComboTime + 1000 < GetTickCount())
	{
		m_dwComboTime = GetTickCount();
		m_iCombo = 0;
	}

	int iCombo = m_iCombo;

	while(iCombo > 0)
	{
		iCombo /= 10;
		++m_iSize;
	}

	for(int i = m_iSize; i > 0; --i)
	{
		iCombo = m_iCombo;
		int res = int(iCombo / pow(10.0f, m_iSize - i));
		m_vecCombo.push_back(res % 10);
	}

	return 0;
}

void CCombo::Render(HDC _hdc)
{
	if(m_iCombo > 0)
	{
		for(size_t i = 0; i < m_vecCombo.size(); ++i)
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "Combo", Rect(730, int(m_tInfo.fY + 5), 70, 25), 0, 0, 0, 0, 0);
			CImageMgr::GetInstance()->ImageRender(_hdc, "ComboFont", Rect(690 - i * 36, (int)m_tInfo.fY, 36, 37), m_vecCombo[i], 0,0,0,0);
		}
	}
	m_vecCombo.clear();
}

void CCombo::Release(void)
{

}