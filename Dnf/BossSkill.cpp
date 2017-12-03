#include "StdAfx.h"
#include "BossSkill.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "InterFace.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Factory.h"
#include "InterFace.h"
#include "SoundMgr.h"

CBossSkill::CBossSkill(void)
:m_CurFrame(0, 5, 100), m_SkillFrame(0, 9, 50)
{

}

CBossSkill::~CBossSkill(void)
{
	Release();
}

void CBossSkill::Init(void)
{
	m_strName = "MonsterSkil";
	m_dwTime = GetTickCount();
	m_bCreate = false;
	m_bDeath = false;
	m_bHit = false;
	m_tInfo.fCX = 64;
	m_tInfo.fCY = 64;
	m_tInfo.fJumpY = 0;

	m_ShadowCollision.left = long(m_tInfo.fX - 22);
	m_ShadowCollision.top = long(m_tInfo.fY - 10);
	m_ShadowCollision.right = long(m_tInfo.fX + 22);
	m_ShadowCollision.bottom = long(m_tInfo.fY + 10);
}

int CBossSkill::Progress(void)
{
	MoveFrame();

	CObj::Progress();

	if(m_bCreate)
	{
		//이때 번개가 생성되었다는것!
		RECT rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();
		RECT rc;
		if(IntersectRect(&rc, &rcPlayer, &m_ShadowCollision))
		{
			if(m_bHit == false)
			{
				//한번만 들어올수있게 
				m_bHit = true;
				CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

				//플레이어의 체력을 깍고 슈아가 아니라면 데미지만.
				int iAtt = (rand() % 50) + 300;
				((CPlayer*)pPlayer)->GetPlayerInfo()->iHp -= iAtt;
				CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj(pPlayer->GetInfo()->fX, pPlayer->GetInfo()->fY, iAtt, false));
				if(((CPlayer*)pPlayer)->GetSuperArmor() == false)
				{
					((CPlayer*)pPlayer)->SetPlayerState(PLAYER_HIT);
				}
			}
		}
	}

	if(m_bDeath)
	{
		return 1;
	}
	return 0;
}

void CBossSkill::Render(HDC _hdc)
{
	if(m_bCreate == false)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, "MonsterCur", m_ImageSize, m_CurFrame.iRenderFrame, 0);
	}
	else
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame,0);
	}

	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x,m_ShadowCollision.bottom );
}

void CBossSkill::Release(void)
{

}
void CBossSkill::MoveFrame(void)
{
	if(m_bCreate == false)
	{
		if(m_dwTime + m_CurFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_CurFrame.iRenderFrame > m_CurFrame.iEndFrame)
			{
				m_bCreate = true;
				m_tInfo.fY = m_tInfo.fY - 235;
				m_tInfo.fCX = 100;
				m_tInfo.fCY = 470;
				CSoundMgr::GetInstance()->PlayMonsterSkillSound(L"썬콜tc_lightning.ogg");
			}
		}
	}
	else
	{
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
			{
				m_bDeath = true;
			}
		}
	}
}