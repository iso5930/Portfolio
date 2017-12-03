#include "StdAfx.h"
#include "Boss.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Factory.h"
#include "InterFace.h"
#include "BossSkill.h"
#include "SoundMgr.h"

CBoss::CBoss(void)
	:CMonster("Matacow_LEFT", 400, 300, 576, 462), m_MoveFrame(0, 7, 170), m_HitFrame(0, 1, 100), m_Attack1(0, 7, 100),
	m_Attack2(0, 3, 200), m_Down(0, 2, 100), m_FireFrame(0, 5, 100)
{

}

CBoss::~CBoss(void)
{
	Release();
}

void CBoss::Init(void)
{
	CImageMgr::GetInstance()->LoadBmp("Matacow_LEFT", L"../Image/Monster/matacow_left_last.bmp");
	CImageMgr::GetInstance()->LoadBmp("Matacow_RIGHT", L"../Image/Monster/matacow_right_last.bmp");
	CImageMgr::GetInstance()->LoadBmp("Cow_Super_Left", L"../Image/Monster/super_left.bmp");
	CImageMgr::GetInstance()->LoadBmp("Cow_Super_Right", L"../Image/Monster/super_right.bmp");
	CImageMgr::GetInstance()->LoadImage("MataCowShadow", L"../Image/Monster/Shadow.png");
	CImageMgr::GetInstance()->LoadImage("MataFireLeft", L"../Image/Monster/Skill/Monster_fire_left.png");
	CImageMgr::GetInstance()->LoadImage("MataFireRight", L"../Image/Monster/Skill/Monster_fire_Right.png");
	CImageMgr::GetInstance()->LoadImage("MonsterSkil", L"../Image/Monster/Skill/Monster_light.png");
	CImageMgr::GetInstance()->LoadImage("MonsterCur", L"../Image/Monster/Skill/Monster_Cursor.png");
	m_dwTime = GetTickCount();
	m_MonState = MONSTER_WAKING;

	lstrcpy(m_tMonInfo.szName, L"하이퍼 메카 타우");
	m_tMonInfo.iMaxHp = 5000000;
	m_tMonInfo.iHp = 5000000;
	m_tMonInfo.iAtt = 500;
	m_tMonInfo.iDef = 24750;
	m_tMonInfo.fMoveSpeed = 3.0f;
	m_iRandomPatton = 0;

	m_bSuperArmor = true;

	m_dwRandomTime = GetTickCount();
	m_dwAttTime = GetTickCount();
	m_dwSkillTime = GetTickCount();
	m_dwAttTime2 = GetTickCount();
	m_dwAttTime3 = GetTickCount();
	m_dwCreateTime = GetTickCount();
	m_iCount = 0;
	m_iSkillCount = 0;

	m_bHit = false;
}

void CBoss::SetState(void)
{
	if(m_MonState == MONSTER_ATTACK1 || m_MonState == MONSTER_ATTACK2 || m_MonState == MONSTER_ATTACK3)
		return;

	RECT rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();

	m_MonState = MONSTER_WAKING;

	if(rcPlayer.left > m_ShadowCollision.left)
	{
		m_strName = "Matacow_RIGHT";
	}
	else
	{
		m_strName = "Matacow_LEFT";
	}
}

int CBoss::Progress(void)
{
	CObj::Progress();

	if(m_tMonInfo.iHp <= 0)
		return 1;

	FrameMove();

	SetState();

	if(m_bHit)
	{
		int iA = rand() % 4;
		switch(iA)
		{
		case 0:	
			CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_dmg_01.ogg");
			break;
		case 1:
			CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_dmg_02.ogg");
			break;
		case 2:
			CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_dmg_03.ogg");
			break;
		case 3:
			CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_dmg_04.ogg");
			break;
		}
		m_bHit = false;
	}

	RECT rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();


	if(m_MonState == MONSTER_ATTACK1 || m_MonState == MONSTER_ATTACK2 || m_MonState == MONSTER_ATTACK3)
	{
		float fDist;
		switch(m_MonState)
		{
		case MONSTER_ATTACK1:
			//일반 찍기 공격
			if(m_Attack1.iRenderFrame >= 4)
			{
				fDist = (float)abs(rcPlayer.bottom - m_ShadowCollision.bottom);

				if(fDist <= 20)
				{
					//20 이내에 있다면 히트!!
					CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
					RECT PlayerRect = pPlayer->GetCollision();
				
					RECT rc;

					RECT rcMonster;
					if(m_strName == "Matacow_LEFT")
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
						if(m_dwAttTime + 1000 < GetTickCount())
						{
							m_dwAttTime = GetTickCount();
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
			break;

		case MONSTER_ATTACK2:
			fDist = (float)abs(rcPlayer.bottom - m_ShadowCollision.bottom);

			if(fDist <= 20)
			{
				CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
				RECT PlayerRect = pPlayer->GetCollision();
			
				RECT rc;

				RECT rcFire;

				RECT rcFire2;
				if(m_strName == "Matacow_LEFT")
				{
					rcFire.left = long(m_tInfo.fX - 436);
					rcFire.top = long(m_tInfo.fY - 76);
					rcFire.right = long(m_tInfo.fX - 184);
					rcFire.bottom = long(m_tInfo.fY + 72);

					rcFire2.left = long(m_tInfo.fX - 436);
					rcFire2.top = long(m_tInfo.fY - 28);
					rcFire2.right = long(m_tInfo.fX - 69);
					rcFire2.bottom = long(m_tInfo.fY + 34);
				}
				else
				{
					rcFire.left = long(m_tInfo.fX + 197);
					rcFire.top = long(m_tInfo.fY - 73);
					rcFire.right = long(m_tInfo.fX + 466);
					rcFire.bottom = long(m_tInfo.fY + 79);

					rcFire2.left = long(m_tInfo.fX + 72);
					rcFire2.top = long(m_tInfo.fY - 28);
					rcFire2.right = long(m_tInfo.fX + 466);
					rcFire2.bottom = long(m_tInfo.fY + 34);
				}
				if(IntersectRect(&rc, &PlayerRect, &rcFire) || IntersectRect(&rc, &PlayerRect, &rcFire2))
				{
					if(m_iCount != 2)
					{
						if(m_dwAttTime + 300 < GetTickCount())
						{
							m_dwAttTime = GetTickCount();
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
			break;

		case MONSTER_ATTACK3:
			if(m_strName == "Matacow_LEFT")
			{
				if(m_dwCreateTime + 50 < GetTickCount())
				{
					m_dwCreateTime = GetTickCount();
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX - 30 - (m_iSkillCount * 51), m_tInfo.fY + 128 - (m_iSkillCount * 10)));
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX - 30 - (m_iSkillCount * 51), m_tInfo.fY + 128));
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX - 30 - (m_iSkillCount * 51), m_tInfo.fY + 128 + (m_iSkillCount * 10)));
					++m_iSkillCount;
				}
			}
			else
			{
				if(m_dwCreateTime + 50 < GetTickCount())
				{
					m_dwCreateTime = GetTickCount();
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX + 30 + (m_iSkillCount * 51), m_tInfo.fY + 128 - (m_iSkillCount * 10)));
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX + 30 + (m_iSkillCount * 51), m_tInfo.fY + 128));
					CObjMgr::GetInstance()->GetList()[OBJ_MONSTER_SKILL].push_back(CFactory<CBossSkill>::CreateObj(m_tInfo.fX + 30 + (m_iSkillCount * 51), m_tInfo.fY + 128 + (m_iSkillCount * 10)));
					++m_iSkillCount;
				}
			}
			break;
		}
		return 0;
	}
	
	rcPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision();



	

	float fvecx = float(rcPlayer.left - m_ShadowCollision.left);
	float fvecy = float(rcPlayer.bottom - m_ShadowCollision.bottom);
		
	float fDist = sqrt(pow(fvecx, 2) + pow(fvecy, 2));


	if(m_dwAttTime2 + 5000 < GetTickCount())
	{
		m_dwAttTime2 = GetTickCount();
		//여기서 공격 체인지
		if(fDist <= 100)
		{
			m_MonState = MONSTER_ATTACK1;
			CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_atk_01.ogg");
		}
		else
		{
			int iA = rand() % 2;
			switch(iA)
			{
			case 0:
				m_MonState = MONSTER_ATTACK2;
				CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_atk_02.ogg");
				m_iCount = 0;
				break;
			case 1:	
				m_MonState = MONSTER_ATTACK3;
				CSoundMgr::GetInstance()->PlayMonsterSound(L"hyper_tau_atk_03.ogg");
				m_iSkillCount = 0;
				break;
			}
		}
	}
	else
	{
		int iA = rand() % 2;

		switch(iA)
		{
		case 0:
			RandomPatton();
			break;

		case 1:
			if(fDist >= 2)
			{
				fvecx /= fDist;
				fvecy /= fDist;

				m_tInfo.fX += fvecx * m_tMonInfo.fMoveSpeed;
				m_tInfo.fY += fvecy * m_tMonInfo.fMoveSpeed;
			}
			break;
		}
	}

	CObj::Progress();

	CMonster::TileCheck();

	return 0;
}

bool CBoss::RandomPatton(void)
{	
	if(m_dwRandomTime + 1000 < GetTickCount())
	{
		m_dwRandomTime = GetTickCount();
		m_iRandomPatton = rand() % 8;
		return true;
	}
	switch(m_iRandomPatton)
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
	return false;
}
void CBoss::FrameMove(void)
{
	switch(m_MonState)
	{
	case MONSTER_WAKING:
		if(m_dwTime + m_MoveFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_MoveFrame.iRenderFrame > m_MoveFrame.iEndFrame)
			{
				m_MoveFrame.iRenderFrame = m_MoveFrame.iStartFrame;
			}
		}
		break;

	case MONSTER_HIT:
		if(m_dwTime + m_HitFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_HitFrame.iRenderFrame > m_HitFrame.iEndFrame)
			{
				m_HitFrame.iRenderFrame = m_HitFrame.iStartFrame;
				m_MonState = MONSTER_WAKING;
			}
		}
		break;

	case MONSTER_ATTACK1:
		if(m_dwTime + m_Attack1.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_Attack1.iRenderFrame > m_Attack1.iEndFrame)
			{
				
				m_Attack1.iRenderFrame = m_Attack1.iStartFrame;
				m_MonState = MONSTER_WAKING;
			}
		}
		break;

	case MONSTER_ATTACK2:
		if(m_dwTime + m_Attack2.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_Attack2.iRenderFrame > m_Attack2.iEndFrame)
			{
				if(m_iCount >= 3)
				{
					m_MonState = MONSTER_WAKING;
					m_Attack2.iRenderFrame = m_Attack2.iEndFrame;
				}
				else
				{
					m_Attack2.iRenderFrame = 1;
				}
			}
		}
		if(m_dwSkillTime + m_FireFrame.dwFrameTime < GetTickCount())
		{
			m_dwSkillTime = GetTickCount();
			if(++m_FireFrame.iRenderFrame > m_FireFrame.iEndFrame)
			{
				++m_iCount;
				m_FireFrame.iRenderFrame = m_FireFrame.iStartFrame;
				switch(m_iCount)
				{					
				case 1:
					m_FireFrame.iEndFrame = 7;
					break;
				case 2:
					m_FireFrame.iEndFrame = 5;
					break;
				}
			}
		}
		break;

	case MONSTER_ATTACK3:
		if(m_dwTime + m_Attack2.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_Attack2.iRenderFrame > m_Attack2.iEndFrame)
			{
				if(m_iSkillCount >= 11)
				{
					m_Attack2.iRenderFrame = m_Attack2.iStartFrame;
					m_MonState = MONSTER_WAKING;
					m_iSkillCount = 0;
				}
				else
				{
					m_Attack2.iRenderFrame = 1;
				}
			}
		}
		break;
	}
}

void CBoss::Render(HDC _hdc)
{
	switch(m_MonState)
	{
	case MONSTER_WAKING:
		
		if(m_strName == "Matacow_LEFT")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Left", m_ImageSize, m_MoveFrame.iRenderFrame, 0, 255, 0, 255);
		}
		else
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Right", m_ImageSize, m_MoveFrame.iRenderFrame, 0, 255, 0, 255);
		}
	
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_MoveFrame.iRenderFrame, 0, 255, 0, 255);
		break;

	case MONSTER_HIT:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_HitFrame.iRenderFrame, 2, 255, 0, 255);	
		break;

	case MONSTER_ATTACK1:
		if(m_strName == "Matacow_LEFT")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Left", m_ImageSize, m_Attack1.iRenderFrame, 1, 255, 0, 255);
		}
		else
		{	
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Right", m_ImageSize, m_Attack1.iRenderFrame, 1, 255, 0, 255);
		}
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_Attack1.iRenderFrame, 1, 255, 0, 255);
		break;

	case MONSTER_ATTACK2:
		if(m_strName == "Matacow_LEFT")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Left", m_ImageSize, m_Attack2.iRenderFrame, 5, 255, 0, 255);
		}
		else
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"Cow_Super_Right", m_ImageSize, m_Attack2.iRenderFrame, 5, 255, 0, 255);
		}

		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_Attack2.iRenderFrame, 5, 255, 0, 255);

		if(m_Attack2.iRenderFrame >= 1)
		{
			if(m_strName == "Matacow_LEFT")
			{
				CImageMgr::GetInstance()->ImageRender(_hdc, "MataFireLeft", Rect(int(m_tInfo.fX - 558) - g_Scroll.x , int(m_tInfo.fY - 118), 510 ,231), m_FireFrame.iRenderFrame, m_iCount,243,154);
			}
			else
			{
				CImageMgr::GetInstance()->ImageRender(_hdc, "MataFireRight", Rect(int(m_tInfo.fX + 50) - g_Scroll.x , int(m_tInfo.fY - 119), 510 ,231), m_FireFrame.iRenderFrame, m_iCount,243,154);
			}
		}
		
		break;

	case MONSTER_ATTACK3:
		CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, m_Attack2.iRenderFrame, 5, 255, 0, 255);
		break;


	}
	
	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x, m_ShadowCollision.bottom);
}


void CBoss::Release(void)
{

}