#include "StdAfx.h"
#include "MonsterHp.h"
#include "ImageMgr.h"
#include "Monster.h"
#include "Boss.h"
#include "BloodLugaru.h"
#include "CowCaptain.h"


CMonsterHp::CMonsterHp(void)
{
}

CMonsterHp::~CMonsterHp(void)
{
	Release();
}
void CMonsterHp::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("NormalMonHp", L"../Image/Monster/MonsterHp/MonsterHpBarNormal.bmp");
	CImageMgr::GetInstance()->LoadBmp("MonHp1", L"../Image/Monster/MonsterHp/NormalHp.bmp");
	CImageMgr::GetInstance()->LoadBmp("MataCowIcon", L"../Image/Monster/Icon/MataCow.bmp");
	CImageMgr::GetInstance()->LoadBmp("Blood", L"../Image/Monster/Icon/BloodGaru.bmp");
	CImageMgr::GetInstance()->LoadBmp("Cow", L"../Image/Monster/Icon/CowCaptain.bmp");
	m_pObj = NULL;
	m_bShow = false;
	m_HpSize.X = 49;
	m_HpSize.Y = 104;
	m_HpSize.Height = 9;
}

int CMonsterHp::Progress(void)
{
	if(m_pObj == NULL)
	{
		m_bShow = false;
		return 0;
	}

	MonsterInfo* m_pMonster = ((CMonster*)m_pObj)->GetMonInfo();

	if(m_pMonster->iHp <= 0)
	{
		m_pObj = NULL;
		return 0;
	}

	m_bShow = true;

	float fHPPersent =	(float)100 - (((float)m_pMonster->iHp / (float)m_pMonster->iMaxHp) * 100); //전체 체력에 대한 비율 
	
	float fHPPersent2 = (597 * fHPPersent / 100);
		
	m_HpSize.Width = int(597 - fHPPersent2);
		
	return 0;
}

void CMonsterHp::Render(HDC _hdc)
{
	if(m_bShow && m_pObj != NULL)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, "NormalMonHp", Rect(20, 85, 629, 32), 0, 0, 255, 255, 255);
		CImageMgr::GetInstance()->ImageRender(_hdc, "MonHp1", m_HpSize, 0, 0, 255, 255, 255);
		if(typeid(*m_pObj) == typeid(CBoss))
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "MataCowIcon", Rect(22, 89, 24, 24), 0, 0, 255, 255, 255);
		}
		else if(typeid(*m_pObj) == typeid(CBloodLugaru))
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "Blood", Rect(22, 89, 24, 24), 0, 0, 255, 255, 255);
		}
		else if(typeid(*m_pObj) == typeid(CCowCaptain))
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "Cow", Rect(22, 89, 24, 24), 0, 0, 255, 255, 255);
		}
	}
}

void CMonsterHp::Release(void)
{

}