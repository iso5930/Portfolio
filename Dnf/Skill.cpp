#include "StdAfx.h"
#include "Skill.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "Factory.h"
#include "Player.h"
#include "Monster.h"
#include "InterFace.h"
#include "MonsterHp.h"
#include "Combo.h"
#include "SoundMgr.h"

CSkill::CSkill(void)
{

}

CSkill::~CSkill(void)
{
	Release();
}

void CSkill::Init(void)
{
	switch(m_Skill_Type)
	{
	case SKILL_VOID:
		m_strName = "Void";
		m_tInfo.fCX = 150;
		m_tInfo.fCY = 150;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 9;
		m_SkillFrame.dwFrameTime = 100;
		m_SkillFrame.iRenderFrame = 0;
		break;

	case SKILL_BLACKHOLE:
		m_strName = "BlackHole";
		m_tInfo.fCX = 332;
		m_tInfo.fCY = 332;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 25;
		m_SkillFrame.dwFrameTime = 100;
		m_SkillFrame.iRenderFrame = 0;
		break;

	case SKILL_THUNDER_CALLING:
		m_strName = "Thunder";
		m_tInfo.fCX = 600;
		m_tInfo.fCY = 600;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 8;
		m_SkillFrame.dwFrameTime = 50;
		m_SkillFrame.iRenderFrame = 0;
		CSoundMgr::GetInstance()->PlaySkillSound(L"썬콜tc_lightning.ogg");
		break;

	case SKILL_ICEFIELD:
		m_strName = "IceField";
		m_tInfo.fCX = 507;
		m_tInfo.fCY = 153;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 4;
		m_SkillFrame.dwFrameTime = 300;
		m_SkillFrame.iRenderFrame = 0;
		m_iCount = 0;
		m_iIndex = 0;
		break;

	case SKILL_ICEPALLAT:
		m_strName = "IcePallat";
		m_tInfo.fCX = 306;
		m_tInfo.fCY = 306;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 4;
		m_SkillFrame.iRenderFrame = 0;
		m_SkillFrame.dwFrameTime = 100;
		m_iIndex = 0;
		m_bDeath = false;
		break;

	case SKILL_ELEMENTALSHOWRE:
		m_strName = "Elemental";
		m_tInfo.fCX = 240;
		m_tInfo.fCY = 240;
		m_tInfo.fJumpY = -300;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 11;
		m_SkillFrame.iRenderFrame = 0;
		m_SkillFrame.dwFrameTime = 100;
		break;

	case SKILL_HALLOWEEN_BUSTER:
		m_strName = "Halloween";
		m_tInfo.fCX = 120; 
		m_tInfo.fCY = 120;
		m_tInfo.fJumpY = -400;
		m_SkillFrame.iRenderFrame = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.iEndFrame = 3;
		m_SkillFrame.dwFrameTime = 100;
		m_bDeath = false;
		m_iIndex = 0;
		m_dwFireTime = GetTickCount();
		break;

	case SKILL_RUN:
		m_tInfo.fCX = 80;
		m_tInfo.fCY = 80;
		m_tInfo.fJumpY = 0;
		m_SkillFrame.iRenderFrame = 0;
		m_SkillFrame.iStartFrame = 0;
		m_SkillFrame.dwFrameTime = 80;
		m_SkillFrame.iEndFrame = 5;
		m_dwRunTime = GetTickCount();
		m_dwClearTime = GetTickCount();
		m_bRun = false;
		m_bCreate = true;
		switch(m_ElementType)
		{
		case ELEMENT_FIRE:
			m_strName = "RunFire1";
			break;

		case ELEMENT_ICE:
			m_strName = "RunIce1";
			break;

		case ELEMENT_DARK:
			m_strName = "RunDark1";
			break;

		case ELEMENT_LIGHT:
			m_strName = "RunLight1";
			break;
		}
		break;
	}
	
	m_dwTime = GetTickCount();
	m_iCount = 0;
	m_bSkillTime = false;
	m_HitTime = GetTickCount();
	CObj::Progress();
	m_bStart = false;
}

int CSkill::Progress(void)
{
	FrameMove();
	
	CObj::Progress();
	
	if(m_bSkillTime)
		return 1;

	CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

	switch(m_Skill_Type)
	{
	case SKILL_VOID:
		m_tInfo.fX += m_vecX;
		break;
	case SKILL_ICEFIELD:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(m_iIndex == 0)
				m_iIndex = 1;
			else
				m_iIndex = 0;
			
			if(++m_iCount >= 17)
			{
				m_bSkillTime = true;
			}

			float fX = float(m_tInfo.fX - (rand() % 200 + 40));
			float fY = float(m_tInfo.fY - (rand() % 80 + 200));
			
			CSoundMgr::GetInstance()->PlaySkillSound(L"af_ice_in.ogg");
			CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(fX, fY, SKILL_ICEPALLAT, 0, m_PlayerInfo));
			CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].back();
			((CSkill*)pObj)->SetIndex(m_iIndex);
		}
		break;

	case SKILL_ELEMENTALSHOWRE:
		if(m_tInfo.fJumpY < 0)
			m_tInfo.fJumpY += 30;
		break;

	case SKILL_HALLOWEEN_BUSTER:
		if(m_tInfo.fJumpY < 0)
		{
			m_tInfo.fX += m_vecX;
			m_tInfo.fJumpY += m_vecY;	
		}
		break;
	case SKILL_RUN:
		if(m_bRun)
		{
			if(m_dwRunTime + 20000 < GetTickCount())
			{
				m_dwRunTime = GetTickCount();
				m_bRun = false;
				m_SkillFrame.iRenderFrame = 0;
				switch(m_ElementType)
				{
				case ELEMENT_FIRE:
					m_strName = "RunFire2";
					break;

				case ELEMENT_ICE:
					m_strName = "RunIce2";
					break;

				case ELEMENT_DARK:
					m_strName = "RunDark2";
					break;

				case ELEMENT_LIGHT:
					m_strName = "RunLight2";
					break;
				}
			}
			else
			{
				switch(m_ElementType)
				{
				case ELEMENT_FIRE:
					m_strName = "RunFire3";
					break;

				case ELEMENT_ICE:
					m_strName = "RunIce3";
					break;

				case ELEMENT_DARK:
					m_strName = "RunDark3";
					break;

				case ELEMENT_LIGHT:
					m_strName = "RunLight3";
					break;
				}
			}
		}
		if(m_dwClearTime + 60000 < GetTickCount())
		{
			m_dwClearTime = GetTickCount();
			m_SkillFrame.iRenderFrame = 0;
			m_SkillFrame.iEndFrame = 6;
			m_bRun = false;
			switch(m_ElementType)
			{
			case ELEMENT_FIRE:
				m_strName = "RunFire4";
				break;
			case ELEMENT_ICE:
				m_strName = "RunIce4";
				break;

			case ELEMENT_DARK:
				m_strName = "RunDark4";
				break;

			case ELEMENT_LIGHT:
				m_strName = "RunLight4";
				break;
			}
		}
		break;
	}

	if(m_Skill_Type == SKILL_RUN)
	{
		CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
		INFO* pInfo = pObj->GetInfo();
		switch(m_ElementType)
		{
		case ELEMENT_ICE:
			m_tInfo.fY = (pInfo->fY + 27) + pInfo->fJumpY;
			m_tInfo.fX = pInfo->fX + 49;
			break;

		case ELEMENT_FIRE:
			m_tInfo.fY = (pInfo->fY + 27) + pInfo->fJumpY;
			m_tInfo.fX = pInfo->fX - 47;
			break;

		case ELEMENT_LIGHT:
			m_tInfo.fY = (pInfo->fY + 4) + pInfo->fJumpY;
			m_tInfo.fX = pInfo->fX + 42;
			break;

		case ELEMENT_DARK:
			m_tInfo.fY = (pInfo->fY + 4) + pInfo->fJumpY;
			m_tInfo.fX = pInfo->fX - 40;
			break;
		}
	}

	if(CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty())
		return 0;

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

	
	if(m_Skill_Type == SKILL_HALLOWEEN_BUSTER && m_bDeath)
	{
		if(m_HitTime + 300 < GetTickCount())
		{
			m_HitTime = GetTickCount();
			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = float(m_ShadowCollision.bottom) - float((*iter)->GetShadowCollision().bottom);

				if(fDistY >= 30)
					continue;
				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 400);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CMonster*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}			
		}
	}
	
	if(m_Skill_Type == SKILL_BLACKHOLE)
	{
		for(iter; iter != iter_end; ++iter)
		{
			float fVecX = float(m_tInfo.fX) - float((*iter)->GetInfo()->fX);
			float fVecY = float(m_ShadowCollision.bottom) - float((*iter)->GetShadowCollision().bottom);
			float fDist = sqrt(pow(fVecX, 2) + pow(fVecY, 2));

			if(abs(fDist) >= 150)
				continue;

			fVecX /= fDist;
			fVecY /= fDist;

			(*iter)->GetInfo()->fX += (fVecX * 5.0f) + 1;
			(*iter)->GetInfo()->fY += (fVecY * 5.0f) + 1;
		}
	}

	if(m_Skill_Type == SKILL_THUNDER_CALLING)
	{
		
		iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
		iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

		for(iter; iter != iter_end; ++iter)
		{
			float fVecX = float(m_tInfo.fX + 10) - float((*iter)->GetInfo()->fX);
			float fVecY = float(m_tInfo.fY + 260) - float((*iter)->GetShadowCollision().bottom);

			float fDist = sqrt(pow(fVecX, 2) + pow(fVecY, 2));

			if(abs(fDist) >= 150)
				continue;

			fVecX /= fDist;
			fVecY /= fDist;

			(*iter)->GetInfo()->fX += fVecX * 15.0f; 
			(*iter)->GetInfo()->fY += fVecY * 15.0f;
		}
	}

	iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
	iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

	switch(m_Skill_Type)
	{
	case SKILL_HALLOWEEN_BUSTER:
		if(m_HitTime + 500 < GetTickCount())
		{
			m_HitTime = GetTickCount();

			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = (float(m_Collision.bottom) - float((*iter)->GetShadowCollision().bottom));
				if(fDistY >= 30)
					continue;

				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					//여기서 몬스터의 hp를 깍자
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 200);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}
		}
		break;

	case SKILL_VOID:
		if(m_HitTime + 500 < GetTickCount())
		{
			m_HitTime = GetTickCount();

			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = abs(float(m_ShadowCollision.bottom) - float((*iter)->GetShadowCollision().bottom));

				if(fDistY >= 50)
					continue;

				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 100);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(*(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()));
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}
		}
		break;

	case SKILL_BLACKHOLE:
		if(m_HitTime + 500 < GetTickCount())
		{
			m_HitTime = GetTickCount();
			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = abs(float(m_ShadowCollision.bottom) - float((*iter)->GetShadowCollision().bottom));

				if(fDistY >= 50)
					continue;

				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					//여기서 몬스터의 hp를 깍자
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CMonster*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}
		}
		break;

	case SKILL_THUNDER_CALLING:
		if(m_HitTime + 400 < GetTickCount())
		{
			m_HitTime = GetTickCount();
			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = abs(float(m_tInfo.fY + 260) - float((*iter)->GetShadowCollision().bottom));

				if(fDistY >= 50)
					continue;

				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					//여기서 몬스터의 hp를 깍자
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 500);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}
		}
		break;

	case SKILL_ICEFIELD:
		if(m_HitTime + 400 < GetTickCount())
		{
			m_HitTime = GetTickCount();

			for(iter; iter != iter_end; ++iter)
			{
				if(PtInCircle(m_tInfo.fX, m_tInfo.fY - 1, 507, 153, float((*iter)->GetShadowCollision().left + ((*iter)->GetShadowCollision().right - (*iter)->GetShadowCollision().left)), float((*iter)->GetShadowCollision().bottom)))
				{
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 200);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}	
		}
		break;

	case SKILL_ELEMENTALSHOWRE:
		if(m_HitTime + 500 < GetTickCount())
		{
			m_HitTime = GetTickCount();
			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = abs(m_Collision.bottom - float((*iter)->GetShadowCollision().bottom));

				if(fDistY >= 50)
					continue;

				RECT rcRect;
				if(IntersectRect(&rcRect, &((*iter)->GetCollision()), &m_Collision))
				{
					//여기서 몬스터의 hp를 깍자
					int iAtt = ((CPlayer*)pPlayer)->GetPlayerInfo()->iInt * (rand() % 50 + 150);
					((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
					CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
					((CMonsterHp*)pObj)->SetMonsterHp((*iter));
					pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
					((CCombo*)pObj)->SetComboTime(GetTickCount());
					((CCombo*)pObj)->AddCombo();
					((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					((CMonster*)(*iter))->SetTargetInfo(m_PlayerInfo);
					((CMonster*)(*iter))->SetbHit(true);
				}
			}
		}
		break;
	}
	return 0;
}

bool CSkill::PtInCircle(float _CircleX, float _CircleY, float _CircleWidth, float _CircleHeight, float _CursorX, float _CursorY)
{
	if((_CircleX - _CursorX) * (_CircleX - _CursorX) / (_CircleWidth * _CircleWidth)+ (_CircleY - _CursorY) * (_CircleY - _CursorY) / (_CircleHeight * _CircleHeight) <= 0.25)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CSkill::Render(HDC _hdc)
{

	
	switch(m_Skill_Type)
	{
	case SKILL_HALLOWEEN_BUSTER:
		if(m_vecX >= 0)
		{
			if(m_bDeath)
			{	
				CObj::Progress();
				CImageMgr::GetInstance()->ImageRender(_hdc, "Boom", m_ImageSize, m_SkillFrame.iRenderFrame, 0);
			}
			else
			{
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X - 50, m_ImageSize.Y - 50, 85, 85), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X - 30, m_ImageSize.Y - 30, 90, 90), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X - 10, m_ImageSize.Y - 10,100, 100), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame, 0);
			}
		}
		else
		{
			if(m_bDeath)
			{
				CImageMgr::GetInstance()->ImageRender(_hdc, "Boom", m_ImageSize, m_SkillFrame.iRenderFrame, 0);
			}
			else
			{
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X + 75, m_ImageSize.Y - 50, 85, 85), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X + 55, m_ImageSize.Y - 30, 90, 90), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, "Fire", Rect(m_ImageSize.X + 35, m_ImageSize.Y - 10,100, 100), m_iIndex, 0, 89, 89);
				CImageMgr::GetInstance()->ImageRender(_hdc, "Halloweenleft", m_ImageSize, m_SkillFrame.iRenderFrame, 0);
			}
		}
		break;
	case SKILL_VOID:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame, 0);
		break;

	case SKILL_BLACKHOLE:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame, 0,1,1,1);
		break;

	case SKILL_THUNDER_CALLING:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame, 0);
		break;

	case SKILL_ICEFIELD:	
		CImageMgr::GetInstance()->ImageRender(_hdc, "IceArea", m_ImageSize, 0,0);
		break;

	case SKILL_ICEPALLAT:
		CImageMgr::GetInstance()->ImageRender(_hdc, "IceField", Rect((int)m_tInfo.fX - g_Scroll.x, (int)m_tInfo.fY, (int)m_tInfo.fCX, (int)m_tInfo.fCY), m_SkillFrame.iRenderFrame, m_iIndex, 65,165,247);
		break;
	
	case SKILL_RUN:
		m_ImageSize.X = int(m_tInfo.fX - m_tInfo.fCX / 2) - g_Scroll.x;
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_SkillFrame.iRenderFrame, 0);
		break;

	case SKILL_ELEMENTALSHOWRE:
		switch(m_ElementType)
		{
		case ELEMENT_ICE:
			CImageMgr::GetInstance()->ImageRender(_hdc, "ElementalIce", Rect((int)m_tInfo.fX - g_Scroll.x, (int)m_tInfo.fY + (int)m_tInfo.fJumpY, 240, 240), m_SkillFrame.iRenderFrame, 0, 212, 205, 255);
			break;

		case ELEMENT_DARK:
			CImageMgr::GetInstance()->ImageRender(_hdc, "ElementalDark", Rect((int)m_tInfo.fX - g_Scroll.x, (int)m_tInfo.fY + (int)m_tInfo.fJumpY,240,240), m_SkillFrame.iRenderFrame, 0, 36, 0, 255);
			break;

		case ELEMENT_FIRE:
			CImageMgr::GetInstance()->ImageRender(_hdc, "ElementalFire", Rect((int)m_tInfo.fX - g_Scroll.x, (int)m_tInfo.fY + (int)m_tInfo.fJumpY, 240, 240), m_SkillFrame.iRenderFrame, 0, 255, 99, 79);
			break;

		case ELEMENT_LIGHT:
			CImageMgr::GetInstance()->ImageRender(_hdc, "ElementalLight", Rect((int)m_tInfo.fX - g_Scroll.x, (int)m_tInfo.fY + (int)m_tInfo.fJumpY,240,240), m_SkillFrame.iRenderFrame, 0, 0, 255, 12);
			break;
		}
		break;
	}	

	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x, m_ShadowCollision.bottom);
}

void CSkill::Release(void)
{
	
}
void CSkill::FrameMove(void)
{
	switch(m_Skill_Type)
	{
	case SKILL_RUN:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			
			if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
			{
				if(m_bCreate)
				{
					m_bCreate = false;
					m_SkillFrame.iEndFrame = 11;
					
					switch(m_ElementType)
					{
					case ELEMENT_FIRE:
						m_strName = "RunFire2";
						break;
					case ELEMENT_DARK:
						m_strName = "RunDark2";
						break;
					case ELEMENT_ICE:
						m_strName = "RunIce2";
						break;
					case ELEMENT_LIGHT:
						m_strName = "RunLight2";
						break;
					}
				}

				if(m_strName == "RunFire4" || m_strName == "RunDark4" || m_strName == "RunIce4" || m_strName == "RunLight4")
				{
					m_bSkillTime = true;
					return;
				}

				if(m_bRun)
				{
					m_SkillFrame.iRenderFrame = 2;
				}

				else
				{
					m_SkillFrame.iRenderFrame = m_SkillFrame.iStartFrame;
				}
			}
		}
		break;
	case SKILL_VOID:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillFrame.iRenderFrame > 6 && m_iCount <= 10)
			{
				m_SkillFrame.iRenderFrame = 3;
				++m_iCount;
			}
			if(m_iCount >= 10)
			{
				if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
				{
					m_bSkillTime = true;
				}
			}
		}
		break;
	case SKILL_BLACKHOLE:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillFrame.iRenderFrame > 17 && m_iCount <= 10)
			{
				m_SkillFrame.dwFrameTime = 80;
				m_SkillFrame.iRenderFrame = 10;
				++m_iCount;
			}
			if(m_iCount >= 10)
			{
				if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
				{
					m_bSkillTime = true;
				}
			}
		}
		break;

	case SKILL_THUNDER_CALLING:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
			{
				m_bSkillTime = true;
			}
		}
		break;

	case SKILL_ICEFIELD:
		break;

	case SKILL_ICEPALLAT:
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlaySkillSound(L"af_ice_out.ogg");
				if(m_bDeath == false)
				{
					m_bDeath = true;
					m_SkillFrame.iRenderFrame = 0;
					m_SkillFrame.iEndFrame = 7;
					m_iIndex = 2;
				}
				else if(m_bDeath)
				{
					m_bSkillTime = true;
				}
			}
		}
		break;

	case SKILL_ELEMENTALSHOWRE:
		if(m_tInfo.fJumpY >= 0)
		{
			if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
			{	
				m_dwTime = GetTickCount();

				if(m_bEnd)
				{
					
				}

				if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
				{
					m_bSkillTime = true;
					CSoundMgr::GetInstance()->PlaySkillSound(L"colorless_bomb.ogg");
				}
			}
		}
		break;
	case SKILL_HALLOWEEN_BUSTER:
		if(m_dwFireTime + 100 < GetTickCount())
		{
			m_dwFireTime = GetTickCount();

			if(++m_iIndex > 5)
			{
				m_iIndex = 0;
			}
		}
		if(m_dwTime + m_SkillFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(m_bDeath == false && m_tInfo.fJumpY >= 0)
			{
				m_bDeath = true;
				m_strName = "Boom";
				m_SkillFrame.iRenderFrame = 0;
				m_SkillFrame.iEndFrame = 12;
				//터지는 이펙트로 체인지
				CSoundMgr::GetInstance()->PlaySkillSound(L"colorless_bomb.ogg");
				m_tInfo.fCX = 319;
				m_tInfo.fCY = 319;
				m_SkillFrame.dwFrameTime = 30;
			}
			if(m_bDeath)
			{
				if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
				{
					m_SkillFrame.iRenderFrame = m_SkillFrame.iStartFrame;
					m_bSkillTime = true;
				}
			}
			else
			{
				if(++m_SkillFrame.iRenderFrame > m_SkillFrame.iEndFrame)
				{
					m_SkillFrame.iRenderFrame = m_SkillFrame.iStartFrame;
				}
			}
		}
		break;
	}
}