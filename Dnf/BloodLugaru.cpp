#include "StdAfx.h"
#include "BloodLugaru.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Factory.h"
#include "InterFace.h"
#include "SoundMgr.h"

CBloodLugaru::CBloodLugaru(void)
	:CMonster("Blood_Left", 400, 300, 151, 125), m_WakingFrame(0, 4, 100), 
	m_AttFrame1(0, 4, 100), m_AttFrame2(0, 4, 100), m_AttFrame3(0, 3, 200),
	m_HitFrame(0, 1, 200), m_DownFrame(2, 5, 500)
{

}

CBloodLugaru::~CBloodLugaru(void)
{
	Release();
}

void CBloodLugaru::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("Blood_Left", L"../Image/Monster/Blood_left.bmp");
	CImageMgr::GetInstance()->LoadBmp("Blood_Right", L"../Image/Monster/Blood_Right.bmp");

	m_dwTime = GetTickCount();
	m_dwTargetTime = GetTickCount();
	m_dwHitTime = GetTickCount();
	m_iCount = 0;
	
	m_MonState = MONSTER_WAITING;

	lstrcpy(m_tMonInfo.szName, L"블러드가루");
	m_tMonInfo.iMaxHp = 1000000;
	m_tMonInfo.iHp = 1000000;
	m_tMonInfo.iAtt = 10;
	m_tMonInfo.iDef = 24750;
	m_tMonInfo.fMoveSpeed = 3.0f;
	m_tInfo.fJumpY = 0;
	m_fTime = 0;
	m_bJump = false;

	m_dwAttTime1 = GetTickCount();
	m_dwAttTime2 = GetTickCount();
	m_dwAttTime3 = GetTickCount();

	m_dwRandomTime = GetTickCount();
	m_iRandom = rand() % 8;

	m_bSuperArmor = false;

}

int CBloodLugaru::Progress(void)
{
	CObj::Progress();

	if(m_tMonInfo.iHp <= 0)
		return 1;

	if(m_MonState == MONSTER_TEST)
		return 0;

	rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();
	CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

	FrameMove();

	if(m_MonState == MONSTER_HIT || m_MonState == MONSTER_DOWN)
		return 0;

	Jump();

	if(m_MonState == MONSTER_ATTACK1)
	{	
		float fDist = float(rcPlayer.bottom - m_ShadowCollision.bottom);

		if(abs(fDist) <= 20)
		{
			RECT PlayerRect = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetCollision();
		
			RECT rc;

			RECT rcMonster;

			if(m_strName == "Blood_Left")
			{
				rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
				rcMonster.top = m_Collision.top;
				rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 56;
				rcMonster.bottom = m_Collision.bottom;
			}
			else
			{
				rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 50;
				rcMonster.top = m_Collision.top;
				rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
				rcMonster.bottom = m_Collision.bottom;
			}
			
			if(IntersectRect(&rc, &PlayerRect, &rcMonster))
			{
				if(m_dwHitTime + 200 < GetTickCount())
				{
					m_dwHitTime = GetTickCount();
					((CPlayer*)pPlayer)->GetPlayerInfo()->iHp -= m_tMonInfo.iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj(pPlayer->GetInfo()->fX, pPlayer->GetInfo()->fY, m_tMonInfo.iAtt, false));
				}
				if(((CPlayer*)pPlayer)->GetSuperArmor() == false)
				{
					((CPlayer*)pPlayer)->SetPlayerState(PLAYER_HIT);
				}
			}
		}
	}

	if(m_MonState == MONSTER_ATTACK3)
	{
		//여기선 몬스터랑 붙었을때 이닫ㅇ
		float fDist = float(rcPlayer.bottom - m_ShadowCollision.bottom);

		if(abs(fDist) <= 20)
		{
			if(m_dwHitTime + 800 < GetTickCount())
			{
				m_dwHitTime = GetTickCount();
				((CPlayer*)pPlayer)->GetPlayerInfo()->iHp -= m_tMonInfo.iAtt;
				CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj(pPlayer->GetInfo()->fX, pPlayer->GetInfo()->fY, m_tMonInfo.iAtt, false));
			}
			if(((CPlayer*)pPlayer)->GetSuperArmor() == false)
			{
				((CPlayer*)pPlayer)->SetPlayerState(PLAYER_HIT);
			}
			m_bJump = false;
		}
		else
		{
			m_MonState = MONSTER_WAITING;
			m_bJump = true;
		}
	}

	if(m_MonState == MONSTER_ATTACK2)
	{
		//여기서 만약 충돌을 했다면 

		float fDist = float(rcPlayer.bottom - m_ShadowCollision.bottom);

		if(abs(fDist) <= 20)
		{
			RECT PlayerRect = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetCollision();
		
			RECT rc;
			if(IntersectRect(&rc, &PlayerRect, &m_Collision))
			{
				((CPlayer*)pPlayer)->GetPlayerInfo()->iHp -= m_tMonInfo.iAtt;
				if(((CPlayer*)pPlayer)->GetSuperArmor() == false)
				{
					((CPlayer*)pPlayer)->SetPlayerState(PLAYER_HIT);
				}
				if(m_dwAttTime2 + 1500 < GetTickCount())
				{
					m_dwAttTime2 = GetTickCount();
					m_MonState = MONSTER_ATTACK3;
				}
			}
		}		
	}

	if(m_bJump)
		return 0;

	if(m_MonState == MONSTER_ATTACK1 || m_MonState == MONSTER_ATTACK2 || m_MonState == MONSTER_ATTACK3)
		return 0;

	if(rcPlayer.left > m_ShadowCollision.left)
	{
		m_strName = "Blood_Right";
	}
	else
	{
		m_strName = "Blood_Left";
	}

	float fVecX = float(rcPlayer.left - m_ShadowCollision.left);
	float fVecY = float(rcPlayer.bottom - m_ShadowCollision.bottom);

	float fDist = sqrt(pow(fVecX, 2) + pow(fVecY, 2));

	if(fDist >= 200)
	{
		m_MonState = MONSTER_WAKING;

		if(m_dwRandomTime + 3000 < GetTickCount())
		{
			m_dwRandomTime = GetTickCount();
			m_iRandom = rand() % 8;
		}
		switch(m_iRandom)
		{
		case 0:
			m_tInfo.fX += 0;
			m_tInfo.fY += m_tMonInfo.fMoveSpeed;
			break; //하단

		case 1:
			m_tInfo.fX += 0;
			m_tInfo.fY -= m_tMonInfo.fMoveSpeed;//상단
			break;
			
		case 2:
			m_tInfo.fX += m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY -= 0;
			break;

		case 3:
			m_tInfo.fX -= m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY -= 0;
			break;

		case 4:
			m_tInfo.fX -= m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY -= m_tMonInfo.fMoveSpeed;
			break;

		case 5:
			m_tInfo.fX += m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY -= m_tMonInfo.fMoveSpeed;
			break;

		case 6:
			m_tInfo.fX += m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY += m_tMonInfo.fMoveSpeed;
			break;

		case 7:
			m_tInfo.fX -= m_tMonInfo.fMoveSpeed;//오른쪽전진
			m_tInfo.fY += m_tMonInfo.fMoveSpeed;
			break;
		}
	}
	else
	{
		if(fDist <= 100)
		{
			if(m_dwTargetTime + 2000 < GetTickCount())
			{
				m_dwTargetTime = GetTickCount();
				m_MonState = MONSTER_ATTACK1;
			}
			else if(m_dwAttTime1 + 2500 < GetTickCount())
			{
				m_dwTargetTime = GetTickCount();
				m_dwAttTime1 = GetTickCount();
				m_MonState = MONSTER_ATTACK2;
				m_bJump = true;
				m_fTime = 0;
			}
		}
		else
		{
			m_MonState = MONSTER_WAKING;

			fVecX /= fDist;
			fVecY /= fDist;

			m_tInfo.fX += fVecX * m_tMonInfo.fMoveSpeed;
			m_tInfo.fY += fVecY * m_tMonInfo.fMoveSpeed;
		}	
	}

	CMonster::TileCheck();

	return 0;
}

void CBloodLugaru::Jump(void)
{
	if(m_bJump == false)
		return;

	if(m_tInfo.fJumpY > 0)
	{
		m_tInfo.fJumpY = 0;
		m_bJump = false;
		m_MonState = MONSTER_WAITING;
	}
	else
	{
		if(m_strName == "Blood_Right")
		{
			m_tInfo.fX += 2.0f;
		}
		else
		{
			m_tInfo.fX -= 2.0f;
		}
		
		m_fTime += 1.0f;
		m_tInfo.fJumpY += float(5.0f * -1 + (0.098 * m_fTime * m_fTime) / 2.f);
	}
}

void CBloodLugaru::FrameMove(void)
{
	switch(m_MonState)
	{
	case MONSTER_WAKING:
		if(m_dwTime + m_WakingFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_WakingFrame.iRenderFrame > m_WakingFrame.iEndFrame)
			{
				m_WakingFrame.iRenderFrame = m_WakingFrame.iStartFrame;
			}
		}
		break;
	case MONSTER_ATTACK1:
		if(m_dwTime + m_AttFrame1.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_AttFrame1.iRenderFrame > m_AttFrame1.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlayMonsterSound(L"fox_atk.ogg");
				m_AttFrame1.iRenderFrame = m_AttFrame1.iStartFrame;
				m_MonState = MONSTER_WAITING;
			}
		}
		break;

	case MONSTER_ATTACK2:
		if(m_dwTime + m_AttFrame2.dwFrameTime < GetTickCount())
		{

			m_dwTime = GetTickCount();
			if(++m_AttFrame2.iRenderFrame > m_AttFrame2.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlayMonsterSound(L"fox_comm.ogg");
				m_AttFrame2.iRenderFrame = m_AttFrame2.iStartFrame;
			}
		}
		break;

	case MONSTER_ATTACK3:
		if(m_dwTime + m_AttFrame3.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_AttFrame3.iRenderFrame > m_AttFrame3.iEndFrame)
			{
				++m_iCount;
				CSoundMgr::GetInstance()->PlayMonsterSound(L"fox_bite.ogg");
				m_AttFrame3.iRenderFrame = m_AttFrame3.iStartFrame + 1;
				if(m_iCount >= 2)
				{
					m_AttFrame3.iRenderFrame = m_AttFrame3.iStartFrame;
					m_MonState = MONSTER_WAITING;
					m_dwAttTime1 = GetTickCount();
					m_dwAttTime2 = GetTickCount();
					m_bJump = true;
					m_iCount = 0;
				}
			}
		}
		break;

	case MONSTER_HIT:
		if(m_dwTime + m_HitFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_HitFrame.iRenderFrame > m_HitFrame.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlayMonsterSound(L"bloodgaru_dmg_02.ogg");
				m_HitFrame.iRenderFrame = m_HitFrame.iStartFrame;
				m_MonState = MONSTER_WAITING;
			}
		}
		break;

	case MONSTER_DOWN:
		if(m_dwTime + m_DownFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_DownFrame.iRenderFrame > m_DownFrame.iEndFrame)
			{
				m_DownFrame.iRenderFrame = m_DownFrame.iStartFrame;
				m_MonState = MONSTER_WAITING;
			}
		}
		break;
	}
}

void CBloodLugaru::Render(HDC _hdc)
{	
	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x, m_ShadowCollision.bottom);
	switch(m_MonState)
	{
	case MONSTER_WAITING:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, 0, 0, 255, 255, 255);
		break;

	case MONSTER_WAKING:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_WakingFrame.iRenderFrame, 1, 255, 255, 255);
		break;

	case MONSTER_HIT:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_HitFrame.iRenderFrame, 5, 255, 255, 255);
		break;

	case MONSTER_DOWN:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_DownFrame.iRenderFrame, 5, 255, 255, 255);
		break;

	case MONSTER_ATTACK1:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame1.iRenderFrame, 2, 255, 255, 255);
		break;

	case MONSTER_ATTACK2:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame2.iRenderFrame, 3, 255, 255, 255);
		break;

	case MONSTER_ATTACK3:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame3.iRenderFrame, 4, 255, 255, 255);
		break;
	}
}

void CBloodLugaru::Release(void)
{

}