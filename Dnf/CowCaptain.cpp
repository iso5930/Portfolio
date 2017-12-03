#include "StdAfx.h"
#include "CowCaptain.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Factory.h"
#include "InterFace.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CCowCaptain::CCowCaptain(void)
	:CMonster("Cow_Left", 400, 300, 382, 420), m_WakingFrame(0, 7, 100), 
	m_AttFrame1(0, 7, 100), m_AttFrame2(0, 6, 100), m_AttFrame3(0, 3, 200),
	m_HitFrame(0, 1, 100), m_DownFrame(0, 3, 100), m_StunFrame(0, 1, 100)
{

}

CCowCaptain::~CCowCaptain(void)
{
	Release();
}
void CCowCaptain::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("Cow_Left", L"../Image/Monster/Cow_left.bmp");
	CImageMgr::GetInstance()->LoadBmp("Cow_Right", L"../Image/Monster/Cow_right.bmp");
	

	m_MonState = MONSTER_WAKING;

	m_dwTime = GetTickCount();
	m_dwRandomTime = GetTickCount();
	m_dwHitTime = GetTickCount();

	lstrcpy(m_tMonInfo.szName, L"타우 캡틴");
	m_tMonInfo.iMaxHp = 2000000;
	m_tMonInfo.iHp = 2000000;
	m_tMonInfo.iAtt = 10;
	m_tMonInfo.iDef = 24750;
	m_tMonInfo.fMoveSpeed = 3.0f;
	m_tInfo.fJumpY = 0;
	m_iRandom = 0;
	m_dwAttTime = GetTickCount();
	m_dwRandomTime2 = GetTickCount();
	m_dwStunTime = GetTickCount();
	m_bRandom = false;
	m_Rush = false;
	m_bSuperArmor = false;
}

int CCowCaptain::Progress(void)
{
	CObj::Progress();

	if(m_tMonInfo.iHp <= 0)
		return 1;

	SetState();

	MoveFrame();

	if(m_MonState == MONSTER_STUN)
		return 0;

	if(m_MonState == MONSTER_ATTACK2)
	{
		if(m_strName == "Cow_Left")
		{
			m_tInfo.fX -= 17.0f;
		}
		else
		{
			m_tInfo.fX += 17.0f;
		}

		CMonster::TileCheck();

		RECT rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();

		float fDist = (float)abs(rcPlayer.bottom - m_ShadowCollision.bottom);

		if(fDist <= 20)
		{
			//20 이내에 있다면 히트!!
			CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
			RECT PlayerRect = pPlayer->GetCollision();
		
			RECT rc;

			RECT rcMonster;

			if(m_strName == "Cow_Left")
			{
				rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 130;
				rcMonster.top = m_Collision.top;
				rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 130;
				rcMonster.bottom = m_Collision.bottom;
			}
			else
			{
				rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 130;
				rcMonster.top = m_Collision.top;
				rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 130;
				rcMonster.bottom = m_Collision.bottom;
			}
			if(IntersectRect(&rc, &PlayerRect, &rcMonster))
			{
				if(m_dwHitTime + 400 < GetTickCount())
				{
					m_dwHitTime = GetTickCount();
					((CPlayer*)pPlayer)->GetPlayerInfo()->iHp -= m_tMonInfo.iAtt;
					CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj(pPlayer->GetInfo()->fX, pPlayer->GetInfo()->fY, m_tMonInfo.iAtt, false));
				}
				if(((CPlayer*)pPlayer)->GetSuperArmor() == false)
				{
					((CPlayer*)pPlayer)->SetPlayerState(PLAYER_HIT);
					if(m_strName == "Cow_Left")
					{
						pPlayer->SetPos(m_tInfo.fX - 10 , pPlayer->GetInfo()->fY);
					}
					else
					{
						pPlayer->SetPos(m_tInfo.fX + 10 , pPlayer->GetInfo()->fY);
					}
				}
			}
		}
		return 0;
	}

	RECT rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();

	if(m_MonState == MONSTER_ATTACK1)
	{
		if(m_AttFrame1.iRenderFrame >= 4)
		{
			float fDist = (float)abs(rcPlayer.bottom - m_ShadowCollision.bottom);

			if(fDist <= 20)
			{
				//20 이내에 있다면 히트!!
				CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
				RECT PlayerRect = pPlayer->GetCollision();
			
				RECT rc;

				RECT rcMonster;

				if(m_strName == "Cow_Left")
				{
					rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
					rcMonster.top = m_Collision.top;
					rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 137;
					rcMonster.bottom = m_Collision.bottom;
				}
				else
				{
					rcMonster.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 137;
					rcMonster.top = m_Collision.top;
					rcMonster.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
					rcMonster.bottom = m_Collision.bottom;
				}
				if(IntersectRect(&rc, &PlayerRect, &rcMonster))
				{
					if(m_dwHitTime + 400 < GetTickCount())
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
	}

	if(m_MonState != MONSTER_ATTACK1)
	{
		if((rcPlayer.left + ((rcPlayer.right - rcPlayer.left) / 2) > m_tInfo.fX))
		{
			m_strName = "Cow_Right";
		}
		else
		{
			m_strName = "Cow_Left";
		}
	}

	if(m_dwRandomTime2 + 1500 < GetTickCount())
	{
		m_dwRandomTime2 = GetTickCount();
		
		if(m_bRandom == false)
		{
			m_bRandom = true;
		}
		else
		{
			m_bRandom = false;
		}
	}
	
	if(m_MonState == MONSTER_WAKING)
	{
		//몬스터의 상태가 워킹일때 
		//몬스터와 나의 거리를 재고 일정 거리에 접근하게되면 다가와서 공격을 한다.!!
		float fVecX = float(rcPlayer.left - m_ShadowCollision.left);
		float fVecY = float(rcPlayer.bottom - m_ShadowCollision.bottom);

		float fDist = sqrt(pow(fVecX, 2) + pow(fVecY, 2));//일단 거리를 먼저 재고나서 

		if(fDist >= 300)
		{
			//일정거리 이상일때
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
			if(m_bRandom)
			{
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
			else if(fDist <= 90 && fVecY <= 3)
			{
				if(m_dwAttTime + 1500 < GetTickCount())
				{
					m_dwAttTime = GetTickCount();
					m_MonState = MONSTER_ATTACK1;
				}
				else
				{
					m_MonState = MONSTER_WAKING;
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
	}

	CMonster::TileCheck();

	return 0;
}

void CCowCaptain::SetState(void)
{
	//cout << "몬스터 타겟 : " << m_tTargetInfo.fX << " / " << m_tTargetInfo.fY << endl;

	if(m_MonState == MONSTER_HIT)
	{
		float fDistX = abs(m_tTargetInfo.fX - m_tInfo.fX);

		//cout << "거리 : " << fDistX << endl;

		if(fDistX >= 150)
		{
			m_MonState = MONSTER_ATTACK2;
			m_Rush = true;
		}
	}

	if(m_Rush)
	{
		m_MonState = MONSTER_ATTACK2;
		return;
	}

	if(m_MonState == MONSTER_ATTACK1 || m_MonState == MONSTER_HIT || m_MonState == MONSTER_ATTACK2 || m_MonState == MONSTER_STUN)
		return;

	m_MonState = MONSTER_WAKING;	//기본값
}

void CCowCaptain::MoveFrame(void)
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
				CSoundMgr::GetInstance()->PlayMonsterSound(L"tau_axeswing.ogg");
				m_AttFrame1.iRenderFrame = m_AttFrame1.iStartFrame;
				m_MonState = MONSTER_WAKING;
			}
		}
		break;

	case MONSTER_ATTACK2:
		if(m_dwTime + m_AttFrame2.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			CSoundMgr::GetInstance()->PlayMonsterSound(L"tau_rush.ogg");
			if(CMonster::CowCaptain())
			{
				m_AttFrame2.iRenderFrame = m_AttFrame2.iStartFrame;
				m_MonState = MONSTER_STUN;
				m_dwStunTime = GetTickCount();
				m_Rush = false;
			}
			if(++m_AttFrame2.iRenderFrame > 5)
			{
				if(!CMonster::CowCaptain())
				{
					m_AttFrame2.iRenderFrame = 1;
				}
			}
		}
		break;

	case MONSTER_ATTACK3:
		if(m_dwTime + m_AttFrame3.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_AttFrame3.iRenderFrame > m_AttFrame3.iEndFrame)
			{
				m_AttFrame3.iRenderFrame = m_AttFrame3.iStartFrame;

			}
		}
		break;

	case MONSTER_HIT:
		if(m_dwTime + m_HitFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			
			if(++m_HitFrame.iRenderFrame > m_HitFrame.iEndFrame)
			{
				
				int iA = rand() % 3;
				switch(iA)
				{
				case 0:
					CSoundMgr::GetInstance()->PlayMonsterSound(L"captain_tau_dmg_01.ogg");
					break;
				case 1:
					CSoundMgr::GetInstance()->PlayMonsterSound(L"captain_tau_dmg_02.ogg");
					break;
				case 2:
					CSoundMgr::GetInstance()->PlayMonsterSound(L"captain_tau_dmg_03.ogg");
					break;
				}
				m_HitFrame.iRenderFrame = m_HitFrame.iStartFrame;
				m_MonState = MONSTER_WAKING;
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
			}
		}
		break;

	case MONSTER_STUN:
		if(m_dwTime + m_StunFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_StunFrame.iRenderFrame > m_StunFrame.iEndFrame)
			{
				if(m_dwStunTime + 1500 < GetTickCount())
				{
					m_dwStunTime = GetTickCount();
					m_StunFrame.iRenderFrame = m_StunFrame.iStartFrame;
					m_MonState = MONSTER_WAKING;
				}
				else
				{
					m_StunFrame.iRenderFrame = 1;
				}
			}
		}
		break;
	}
}

void CCowCaptain::Render(HDC _hdc)
{
	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x, m_ShadowCollision.bottom);

	switch(m_MonState)
	{
	case MONSTER_WAKING:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_WakingFrame.iRenderFrame, 0, 255, 0, 255);
		break;

	case MONSTER_HIT:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_HitFrame.iRenderFrame, 2, 255, 0, 255);
		break;

	case MONSTER_DOWN:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_DownFrame.iRenderFrame, 3, 255, 0, 255);
		break;

	case MONSTER_ATTACK1:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame1.iRenderFrame, 1, 255, 0, 255);
		break;

	case MONSTER_ATTACK2:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame2.iRenderFrame, 4, 255, 0, 255);
		break;

	case MONSTER_ATTACK3:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_AttFrame3.iRenderFrame, 5, 255, 0, 255);
		break;

	case MONSTER_STUN:	
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_StunFrame.iRenderFrame, 2, 255, 0, 255);
		break;
	}
}

void CCowCaptain::Release(void)
{

}
