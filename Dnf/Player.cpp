#include "StdAfx.h"
#include "Player.h"
#include "ImageMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Inven.h"
#include "Factory.h"
#include "SceneMgr.h"
#include "Info.h"
#include "SoundMgr.h"
#include "Cutin.h"

CPlayer::CPlayer(void)
	:CObj("PlayerRight",400,450,206,206), m_Waiting(0,3,200), m_Waking(0,9,80), m_Dash(0,3,100), m_Jump(0,8,50), m_DashAttck(8, 16, 100)
	,m_Attck1(0,4,100), m_Attck2(0,4,70), m_Attck3(0,8,70), m_SkillVoidCasting(0,6,100), m_SkillThunderCasting(0, 3, 150), m_SkillMagicCursor(0, 9, 50),
	m_FrameCastingStart(0, 12, 0), m_FrameCastingEnd(0, 9, 0), m_ElementalCasting(0,10,100), m_Hit(0, 2, 150)
{																																					   
	
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Init(void)
{
	m_dwTime = GetTickCount();
	CObjMgr::GetInstance()->GetList()[OBJ_INVEN].push_back(CFactory<CInven>::CreateObj());
	CImageMgr::GetInstance()->LoadImage("PlayerLeft",L"../Image/Player/Left/Player.png");
	//CImageMgr::GetInstance()->LoadBmp("PlayerLeft",L"../Image/Player/Left/Player_Left.bmp");
	CImageMgr::GetInstance()->LoadImage("PlayerRight",L"../Image/Player/Right/Player.png");
	CImageMgr::GetInstance()->LoadImage("PlayerShadow", L"../Image/Player/Shadow.png");
	CImageMgr::GetInstance()->LoadImage("Void", L"../Image/Skill/Void.png");
	CImageMgr::GetInstance()->LoadBmp("BlackHole", L"../Image/Skill/BlackHole.bmp");
	//CImageMgr::GetInstance()->LoadImage("BlackHole", L"../Image/Skill/BlackHole.png");
	CImageMgr::GetInstance()->LoadImage("CutScene", L"../Image/Skill/SkillCutScene.png");

	CImageMgr::GetInstance()->LoadImage("PlayerElementalLeft", L"../Image/Player/Left/PlayerElemental.png");
	CImageMgr::GetInstance()->LoadImage("PlayerElementalRight", L"../Image/Player/Right/PlayerElemental.png");
	
	CImageMgr::GetInstance()->LoadBmp("Inven", L"../Image/UI/Inven.bmp"); 

	CImageMgr::GetInstance()->LoadImage("Boom", L"../Image/Skill/Boom.png");//터지는거

	CImageMgr::GetInstance()->LoadImage("PlayerHitLeft", L"../Image/Player/Left/PlayerHit.png");
	CImageMgr::GetInstance()->LoadImage("PlayerHitRight", L"../Image/Player/Right/PlayerHit.png");
	
	//썬더 콜링
	CImageMgr::GetInstance()->LoadImage("MagicCursor", L"../Image/Skill/MagicCursor.png"); 
	CImageMgr::GetInstance()->LoadImage("MagicCircle", L"../Image/Skill/MagicCircle.png");
	CImageMgr::GetInstance()->LoadImage("PlayerLeftThunder", L"../Image/Player/Left/PlayerThunder.png");
	CImageMgr::GetInstance()->LoadImage("PlayerRightThunder", L"../Image/Player/Right/PlayerThunder.png");
	CImageMgr::GetInstance()->LoadImage("Thunder", L"../Image/Skill/thunderstrike.png");
	
	//캐스팅
	CImageMgr::GetInstance()->LoadBmp("Casting", L"../Image/Skill/Casting.bmp");
	CImageMgr::GetInstance()->LoadImage("CastingEnd", L"../Image/Skill/CastingEnd.png");

	//아크틱
	CImageMgr::GetInstance()->LoadImage("IceArea", L"../Image/Skill/IceArea.png");
	CImageMgr::GetInstance()->LoadBmp("IceField", L"../Image/Skill/IceField.bmp");


	//초월의 룬
	CImageMgr::GetInstance()->LoadImage("RunDark1", L"../Image/Skill/Run/Dark/RunDarkCreate.png");
	CImageMgr::GetInstance()->LoadImage("RunDark2", L"../Image/Skill/Run/Dark/RunDark1.png");
	CImageMgr::GetInstance()->LoadImage("RunDark3", L"../Image/Skill/Run/Dark/RunDark2.png");
	CImageMgr::GetInstance()->LoadImage("RunDark4", L"../Image/Skill/Run/Dark/RunDarkDelete.png");

	CImageMgr::GetInstance()->LoadImage("RunFire1", L"../Image/Skill/Run/Fire/RunFireCreate.png");
	CImageMgr::GetInstance()->LoadImage("RunFire2", L"../Image/Skill/Run/Fire/RunFire1.png");
	CImageMgr::GetInstance()->LoadImage("RunFire3", L"../Image/Skill/Run/Fire/RunFire2.png");
	CImageMgr::GetInstance()->LoadImage("RunFire4", L"../Image/Skill/Run/Fire/RunFireDelete.png");

	CImageMgr::GetInstance()->LoadImage("RunIce1", L"../Image/Skill/Run/Ice/RunIceCreate.png");
	CImageMgr::GetInstance()->LoadImage("RunIce2", L"../Image/Skill/Run/Ice/RunIce1.png");
	CImageMgr::GetInstance()->LoadImage("RunIce3", L"../Image/Skill/Run/Ice/RunIce2.png");
	CImageMgr::GetInstance()->LoadImage("RunIce4", L"../Image/Skill/Run/Ice/RunIceDelete.png");

	CImageMgr::GetInstance()->LoadImage("RunLight1", L"../Image/Skill/Run/Light/RunLightCreate.png");
	CImageMgr::GetInstance()->LoadImage("RunLight2", L"../Image/Skill/Run/Light/RunLight1.png");
	CImageMgr::GetInstance()->LoadImage("RunLight3", L"../Image/Skill/Run/Light/RunLight2.png");
	CImageMgr::GetInstance()->LoadImage("RunLight4", L"../Image/Skill/Run/Light/RunLightDelete.png");
	

	//에스트럴 스톰
	CImageMgr::GetInstance()->LoadBmp("ElementalFire", L"../Image/Skill/ElementalshowerFire.bmp");
	CImageMgr::GetInstance()->LoadBmp("ElementalDark", L"../Image/Skill/ElementalshowerDark.bmp");
	CImageMgr::GetInstance()->LoadBmp("ElementalIce", L"../Image/Skill/ElementalshowerIce.bmp");
	CImageMgr::GetInstance()->LoadBmp("ElementalLight", L"../Image/Skill/ElementalshowerLight.bmp");
	CImageMgr::GetInstance()->LoadImage("Element", L"../Image/Skill/Elementalshower2.png");

	//할로윈 버스터
	CImageMgr::GetInstance()->LoadImage("Halloween", L"../Image/Skill/halloweenbuster1.png");
	//CImageMgr::GetInstance()->LoadImage("Halloween2", L"../Image/Skill/halloweenbuster2.png");
	CImageMgr::GetInstance()->LoadImage("Fire", L"../Image/Skill/Fire.png");
	CImageMgr::GetInstance()->LoadImage("Halloweenleft", L"../Image/Skill/halloweenbuster1_left.png");
	
	m_dwDashTime = GetTickCount();
	m_dwShowInven = GetTickCount();
	m_dwLeftDashTime = GetTickCount();
	m_dwMagicCursorTime = GetTickCount();
	m_PlayerState = PLAYER_WAITING;
	m_bDash = false;
	m_bJump = false;
	m_iDashCount = 0;
	m_tInfo.fJumpY = 0;
	m_tPlayerInfo.iHp = 50000;
	m_tPlayerInfo.iMaxHp = 50000;
	m_tPlayerInfo.iMp = 1000;
	m_tPlayerInfo.iMaxMp = 1000;
	m_tPlayerInfo.iAtt = 100;
	m_tPlayerInfo.iInt = 500;
	m_tPlayerInfo.iDef = 100;
	g_Scroll.x = 0;
	g_Scroll.y = 0;
	m_iSkillCastingCount = 0;
	m_bSkillCastingEnd = false;
	m_bSkillCasting = false;

	m_iLeftDashCount = 0;	
	m_bLeftDash = false;
	m_bJumpMax = false;
	m_bAttck1 = false;
	m_bAttck2 = false;
	m_bThunder = false;
	m_iThunderCount = 0;

	m_CastingStart = false;
	m_CastingEnd = false;
	m_ElementalEnd = false;
	m_bRun = false;

	m_dwCreateTime = GetTickCount();

	m_iRunCount = 0;

	m_bSuperArmor = false;

	//데미지 관련

	CImageMgr::GetInstance()->LoadImage("CriEffect", L"../Image/UI/CriEffect.png");
	CImageMgr::GetInstance()->LoadImage("Critical", L"../Image/UI/Critical.png");
	CImageMgr::GetInstance()->LoadImage("Damage", L"../Image/UI/Damage.png");
}

int CPlayer::Progress(void)
{
	KeyCheck();
	
	SetPlayerState();

	Jump();

	m_iRunCount = 0;

	m_dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(m_bRun)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();

		for(iter; iter != iter_end; ++iter)
		{
			string strName = (*iter)->GetName();

			if(strName == "RunFire3" || strName == "RunIce3" || strName == "RunLight3" || strName == "RunDark3")
			{
				++m_iRunCount;
				if(m_iRunCount >= 4)
					break;
			}
		}
	}

	m_tPlayerInfo.iInt = (m_iRunCount * 150) + 500;
	
	if(m_dwKey & KEY_I)
	{
		if(m_dwShowInven + 100 < GetTickCount())
		{
			m_dwShowInven = GetTickCount();
			CObj* m_pInven = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
			if(((CInven*)m_pInven)->GetShowInven())
			{
				CSoundMgr::GetInstance()->PlayEffect(L"winclose.ogg");
				((CInven*)m_pInven)->SetShowInven(false);
			}
			else
			{
				CSoundMgr::GetInstance()->PlayEffect(L"winshow.ogg");
				((CInven*)m_pInven)->SetShowInven(true);
			}
		}
	}

	if(GetAsyncKeyState('M') & 0x8000)
	{
		if(m_dwShowInven + 100 < GetTickCount())
		{
			m_dwShowInven = GetTickCount();
			CObj* m_pInfo = CObjMgr::GetInstance()->GetList()[OBJ_INFO].front();
			if(((CInfo*)m_pInfo)->GetShowInfo())
			{
				((CInfo*)m_pInfo)->SetShowInfo(false);
			}
			else
			{
				((CInfo*)m_pInfo)->SetShowInfo(true);
			}
		}
	}

	if((m_PlayerState == PLAYER_THNUDER_CALLING_CASTING && m_bSkillCastingEnd) || (m_PlayerState == PLAYER_ELEMENTALSHOWRE_CASTING && m_bSkillCastingEnd))
	{	
		if(PtInCircle(m_tInfo.fX, m_tInfo.fY + 65, 1003, 304, m_tMagicCursor.fX, m_tMagicCursor.fY + 60))
		{
			if(m_dwKey & KEY_LEFT)
			{
				m_tMagicCursor.fX -= 10.0f; 
			}

			if(m_dwKey & KEY_RIGHT)
			{

				m_tMagicCursor.fX += 10.0f;
			}

			if(m_dwKey & KEY_UP)
			{
				m_tMagicCursor.fY -= 10.0f;			
			}
			
			if(m_dwKey & KEY_DOWN)
			{
				m_tMagicCursor.fY += 10.0f;
			}
		}
		else
		{
			if(m_tMagicCursor.fY > m_tInfo.fY)
				m_tMagicCursor.fY -= 5.0f;
			else
				m_tMagicCursor.fY += 5.0f;

			if(m_tMagicCursor.fX > m_tInfo.fX)
				m_tMagicCursor.fX -= 5.0f;
			else
				m_tMagicCursor.fX += 5.0f;
		}
		
		
		g_Scroll.x = long(m_tMagicCursor.fX - WINCX / 2.0f);
		
		CScene* pScene = CSceneMgr::GetInstance()->GetScene();

		if(pScene != NULL)
		{
			if(pScene->GetSceneState() == SCENE_SERIAROOM)
			{
				g_Scroll.x = 0;
			}
			else
			{
				if(g_Scroll.x < 0)
				{
					g_Scroll.x = 0;
				}
				else if(g_Scroll.x > 800)
				{
					g_Scroll.x = 800;
				}
			}
		}
	}

	if(m_iThunderCount >= 4)
	{
		m_iSkillCastingCount = 0;
		m_bSkillCasting = false;
		m_bSkillCastingEnd = false;
		m_bThunder = false;
		m_SkillCastingState = PLAYER_END;
		m_iThunderCount = 0;
		m_bSuperArmor = false;
	}

	if(m_iElementalCount >= 7)
	{
		m_iSkillCastingCount = 0;
		m_bSkillCasting = false;
		m_bSkillCastingEnd = false;
		m_SkillCastingState = PLAYER_END;
		m_iElementalCount = 0;
		m_bSuperArmor = false;
	}

	if(m_bSkillCastingEnd)
	{
		if(m_PlayerState == PLAYER_THNUDER_CALLING_CASTING)
		{
			if(m_dwKey & KEY_X)
			{
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"썬콜.ogg");
				m_bThunder = true;
			}
			if(m_bThunder)
			{
				SkillCasting();
			}
		}
		else
		{
			SkillCasting();
		}
	}
	else
	{
		MoveFrame();
	}

	CObj::Progress();

	return 0;
}
void CPlayer::SetScroll(void)
{
	g_Scroll.x = long(m_tInfo.fX - WINCX / 2.0f);

	CScene* pScene = CSceneMgr::GetInstance()->GetScene();

	if(pScene != NULL)
	{
		if(pScene->GetSceneState() == SCENE_SERIAROOM)
		{
			g_Scroll.x = 0;
		}
		else
		{
			if(g_Scroll.x < 0)
			{
				g_Scroll.x = 0;
			}
			else if(g_Scroll.x > 800)
			{
				g_Scroll.x = 800;
			}
		}
	}
}
void CPlayer::KeyCheck(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(m_bSkillCastingEnd)
		return;

	if(m_PlayerState == PLAYER_HIT)
	{
		SetScroll();
		return;
	}
		

	if(m_PlayerState == PLAYER_DASHATTCK || m_PlayerState == PLAYER_ATTACK1 || m_PlayerState == PLAYER_ATTACK2 || m_PlayerState == PLAYER_ATTACK3)
		return;
	
	if(dwKey & KEY_LEFT)
	{
		if(m_PlayerState == PLAYER_DASH)
		{
			m_tInfo.fX -= 10;
		}
		else
		{
			m_tInfo.fX -= 5;
		}
	}

	if(dwKey & KEY_RIGHT)
	{
		if(m_PlayerState == PLAYER_DASH)
		{
			m_tInfo.fX += 10;
		}
		else
		{
			m_tInfo.fX += 5;
		}
	}

	if(dwKey & KEY_UP)
	{
		if(m_PlayerState == PLAYER_JUMP)
		{
			m_tInfo.fY -= 1;
		}
		else
		{
			m_tInfo.fY -= 5;
		}
		
	}
	
	if(dwKey & KEY_DOWN)
	{
		if(m_PlayerState == PLAYER_JUMP)
		{
			m_tInfo.fY += 1;
		}
		else
			m_tInfo.fY += 5;
	}

	SetScroll();
}

void CPlayer::SetPlayerState(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(m_PlayerState == PLAYER_HIT && m_bSuperArmor == false)
	{
		m_iSkillCastingCount = 0;
		m_bSkillCasting = false;
		m_bSkillCastingEnd = false;
		m_SkillCastingState = PLAYER_END;
		m_iElementalCount = 0;
		m_bSuperArmor = false;
	}

	if(m_PlayerState == PLAYER_HIT ||m_PlayerState == PLAYER_JUMP || m_PlayerState == PLAYER_DASHATTCK || m_PlayerState == PLAYER_ATTACK1 || m_PlayerState == PLAYER_ATTACK2 || m_PlayerState == PLAYER_ATTACK3 || m_PlayerState == PLAYER_RUN_CASTING)
		return;

	if((m_PlayerState == PLAYER_VOIDCASTING && m_bSkillCastingEnd) || (m_PlayerState == PLAYER_BLACKHOLE_CASTING && m_bSkillCastingEnd) || (m_PlayerState == PLAYER_THNUDER_CALLING_CASTING && m_bSkillCastingEnd) 
		|| (m_PlayerState == PLAYER_ICEFIELD_CASTING && m_bSkillCastingEnd) || (m_PlayerState == PLAYER_ELEMENTALSHOWRE_CASTING && m_bSkillCastingEnd)
		|| (m_PlayerState == PLAYER_HALLOWEEN_BUSTER_CASTING && m_bSkillCastingEnd))
		return;

	if((!(m_PlayerState == PLAYER_THNUDER_CALLING_CASTING) && CastingKeyCheck()) && (!(m_PlayerState == PLAYER_BLACKHOLE_CASTING) && CastingKeyCheck())
		&& (!(m_PlayerState == PLAYER_VOIDCASTING) && CastingKeyCheck()) && (!(m_PlayerState == PLAYER_ICEFIELD_CASTING) && CastingKeyCheck())
		 && (!(m_PlayerState == PLAYER_HALLOWEEN_BUSTER_CASTING) && CastingKeyCheck()))
		m_PlayerState = PLAYER_WAITING;

	
	if(!dwKey)
	{
		m_PlayerState = PLAYER_WAITING;

		m_CastingStart = false;
		m_CastingEnd = false;

		if(m_bDash)
		{
			if(m_dwDashTime + 500 < GetTickCount())
			{
				m_iDashCount = 0;
				m_dwDashTime = GetTickCount();
				m_bDash = false;
			}
			++m_iDashCount;
		}

		else if(m_bLeftDash)
		{
			if(m_dwLeftDashTime + 500 < GetTickCount())
			{
				m_iLeftDashCount = 0;
				m_dwLeftDashTime = GetTickCount();
				m_bLeftDash = false;
			}
			++m_iLeftDashCount;
		}

		if(m_bSkillCasting && m_iSkillCastingCount >= 30)
		{
			m_bSkillCastingEnd = true;
			m_iSkillCastingCount = 0;
			switch(m_SkillCastingState)
			{
			case PLAYER_VOIDCASTING:
				m_PlayerState = PLAYER_VOIDCASTING;
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"보이드 발사.ogg");
				break;

			case PLAYER_ICEFIELD_CASTING:
				m_PlayerState = PLAYER_ICEFIELD_CASTING;
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"아크틱 발동.ogg");
				break;

			case PLAYER_BLACKHOLE_CASTING:
				m_PlayerState = PLAYER_BLACKHOLE_CASTING;
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"나할발동.ogg");
				break;

			case PLAYER_THNUDER_CALLING_CASTING:
				m_PlayerState = PLAYER_THNUDER_CALLING_CASTING;
				m_tMagicCursor.fX = m_tInfo.fX;
				m_tMagicCursor.fY = m_tInfo.fY;
				m_tMagicCursor.fJumpY = 0;
				m_tMagicCursor.fCX = 192;
				m_tMagicCursor.fCY = 192;
				m_bSuperArmor = true;
				break;

			case PLAYER_HALLOWEEN_BUSTER_CASTING:
				m_PlayerState = PLAYER_HALLOWEEN_BUSTER_CASTING;
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"wz_magicmissile.ogg");

				if(m_strName == "PlayerLeft")
				{
					m_tMagicCursor.fX = m_tInfo.fX - 300;
				}
				else
				{
					m_tMagicCursor.fX = m_tInfo.fX + 300;
				}
				m_tMagicCursor.fY = m_tInfo.fY;
				m_tMagicCursor.fJumpY = 0;
				m_tMagicCursor.fCX = 192;
				m_tMagicCursor.fCY = 192;
				break;
			}
		}
		else
		{
			m_bSkillCasting = false;
			m_iSkillCastingCount = 0;
			m_SkillCastingState = PLAYER_END;
		}
	}

	if(dwKey & KEY_LEFT)
	{
		m_strName = "PlayerLeft";
		m_PlayerState = PLAYER_WAKING;

		m_bLeftDash = true;

		if(m_iLeftDashCount > 1)
		{
			m_PlayerState = PLAYER_DASH;
		}
	}

	if(dwKey & KEY_RIGHT)
	{
		m_strName = "PlayerRight";
		m_PlayerState = PLAYER_WAKING;
		
		m_bDash = true;

		if(m_iDashCount > 1)
		{
			m_PlayerState = PLAYER_DASH;
		}
	}

	if(dwKey & KEY_UP)
	{
		m_PlayerState = PLAYER_WAKING;

		if(m_iDashCount > 1 || m_iLeftDashCount > 1)
		{
			m_PlayerState = PLAYER_DASH;
		}
	}
	
	if(dwKey & KEY_DOWN)
	{
		m_PlayerState = PLAYER_WAKING;
		if(m_iDashCount > 1 || m_iLeftDashCount > 1)
		{
			m_PlayerState = PLAYER_DASH;
		}
	}

	if(dwKey & KEY_C)
	{
		m_fTime = 0;
		m_bJump = true;
		m_PlayerState = PLAYER_JUMP;
		CSoundMgr::GetInstance()->PlayPlayerEffect(L"wz_jump.ogg");
	}

	if(dwKey & KEY_X)
	{
		if(m_PlayerState == PLAYER_DASH)
		{
			m_PlayerState = PLAYER_DASHATTCK;
		}
		else
		{
			if(m_bAttck1 == false)
			{
				m_bAttck1 = true;

				m_PlayerState = PLAYER_ATTACK1;
			}
		}
	}

	if(dwKey & KEY_S)
	{
		//썬콜
		if(m_bSkillCasting == false)
		{
			m_PlayerState = PLAYER_THNUDER_CALLING_CASTING;
			m_SkillCastingState = PLAYER_THNUDER_CALLING_CASTING;
			m_bSkillCasting = true;
			m_iSkillCastingCount = 0;
			m_CastingStart = true;
		}
		else
		{
			++m_iSkillCastingCount;
			if(m_CastingStart)
			{
				if(++m_FrameCastingStart.iRenderFrame > m_FrameCastingStart.iEndFrame)
				{
					m_FrameCastingStart.iRenderFrame = m_FrameCastingStart.iStartFrame;
				}
			}
			if(m_iSkillCastingCount >= 30)
			{
				if(m_CastingStart)
				{
					m_CastingStart = false;
					m_CastingEnd = true;
				}
			}
		}
	}//썬더 콜링 캐스팅

	if(dwKey & KEY_A)
	{
		m_PlayerState = PLAYER_RUN_CASTING;
		m_SkillCastingState = PLAYER_RUN_CASTING;
		m_CastingEnd = true;
		//플레이어의 상태를 룬 캐스팅으로 바꾸고 
	}

	//에스트럴 스톰
	if(dwKey & KEY_Q)
	{
		if(m_bSkillCasting == false)
		{
			CSoundMgr::GetInstance()->PlayPlayerEffect(L"1각.ogg");
			m_PlayerState = PLAYER_ELEMENTALSHOWRE_CASTING;
			m_SkillCastingState = PLAYER_ELEMENTALSHOWRE_CASTING;
			m_bSkillCastingEnd = true;
			m_iSkillCastingCount = 0;
			m_tMagicCursor.fX = m_tInfo.fX;
			m_tMagicCursor.fY = m_tInfo.fY;
			m_tMagicCursor.fJumpY = 0;
			m_tMagicCursor.fCX = 192;
			m_tMagicCursor.fCY = 192;
			m_iElementalCount = 0;
			m_ElementalEnd = false;
			m_bSuperArmor = true;
			CObjMgr::GetInstance()->GetList()[OBJ_CUTIN].push_back(CFactory<CCutin>::CreateObj());
			CObj* pCutin = CObjMgr::GetInstance()->GetList()[OBJ_CUTIN].back();
			((CCutin*)pCutin)->SetStart(true);
		}
	}

	if(dwKey & KEY_F)
	{
		if(m_bSkillCasting == false)
		{
			CSoundMgr::GetInstance()->PlayPlayerEffect(L"보이드 캐스팅.ogg");
			m_PlayerState = PLAYER_VOIDCASTING;
			m_SkillCastingState = PLAYER_VOIDCASTING;
			m_bSkillCasting = true;
			m_iSkillCastingCount = 0;
			m_CastingStart = true;
		}
		else
		{
			++m_iSkillCastingCount;
			if(m_CastingStart)
			{
				if(++m_FrameCastingStart.iRenderFrame > m_FrameCastingStart.iEndFrame)
				{
					m_FrameCastingStart.iRenderFrame = m_FrameCastingStart.iStartFrame;
				}
			}
			if(m_iSkillCastingCount >= 30)
			{
				if(m_CastingStart)
				{
					m_CastingStart = false;
					m_CastingEnd = true;
				}
			}
		}
	}//보이드

	if(dwKey & KEY_G)
	{
		if(m_bSkillCasting == false)
		{
			CSoundMgr::GetInstance()->PlayPlayerEffect(L"아크틱 시전.ogg");
			m_PlayerState = PLAYER_ICEFIELD_CASTING;
			m_SkillCastingState = PLAYER_ICEFIELD_CASTING;
			m_bSkillCasting = true;
			m_iSkillCastingCount = 0;
			m_CastingStart = true;
		}
		else
		{
			++m_iSkillCastingCount;
			if(m_CastingStart)
			{
				if(++m_FrameCastingStart.iRenderFrame > m_FrameCastingStart.iEndFrame)
				{
					m_FrameCastingStart.iRenderFrame = m_FrameCastingStart.iStartFrame;
				}
			}
			if(m_iSkillCastingCount >= 30)
			{
				if(m_CastingStart)
				{
					m_CastingStart = false;
					m_CastingEnd = true;
				}
			}
		}
	}//아크틱 피스트

	if(dwKey & KEY_H)
	{
		if(m_bSkillCasting == false)
		{
			CSoundMgr::GetInstance()->PlayPlayerEffect(L"나할 캐스팅.ogg");
			m_PlayerState = PLAYER_BLACKHOLE_CASTING;
			m_SkillCastingState = PLAYER_BLACKHOLE_CASTING;
			m_bSkillCasting = true;
			m_iSkillCastingCount = 0;
			m_CastingStart = true;
		}
		else
		{
			++m_iSkillCastingCount;
			if(m_CastingStart)
			{
				if(++m_FrameCastingStart.iRenderFrame > m_FrameCastingStart.iEndFrame)
				{
					m_FrameCastingStart.iRenderFrame = m_FrameCastingStart.iStartFrame;
				}
			}
			if(m_iSkillCastingCount >= 30)
			{
				if(m_CastingStart)
				{
					m_CastingStart = false;
					m_CastingEnd = true;
				}
			}
		}
	}// 나이트 할로우

	if(dwKey & KEY_D)
	{
		if(m_bSkillCasting == false)
		{
			m_PlayerState = PLAYER_HALLOWEEN_BUSTER_CASTING;
			m_SkillCastingState = PLAYER_HALLOWEEN_BUSTER_CASTING;
			m_bSkillCasting = true;
			m_iSkillCastingCount = 0;
			m_CastingStart = true;
			CSoundMgr::GetInstance()->PlayPlayerEffect(L"wz_magicmissile_ready.ogg");
		}
		else
		{
			++m_iSkillCastingCount;
			if(m_CastingStart)
			{
				if(++m_FrameCastingStart.iRenderFrame > m_FrameCastingStart.iEndFrame)
				{
					m_FrameCastingStart.iRenderFrame = m_FrameCastingStart.iStartFrame;
				}
			}
			if(m_iSkillCastingCount >= 30)
			{
				if(m_CastingStart)
				{
					m_CastingStart = false;
					m_CastingEnd = true;
				}
			}
		}
	}//할로윈 버스터
	
}
void CPlayer::CObjProgress(void)
{
	CObj::Progress();
}

void CPlayer::Jump(void)
{
	if(m_bJump == false)
		return;

	if(m_tInfo.fJumpY <= -108)
		m_bJumpMax = true;

	if(m_tInfo.fJumpY > 0)
	{
		m_tInfo.fJumpY = 0;
		m_bJump = false;
		m_bJumpMax = false;
		m_PlayerState = PLAYER_WAITING;
	}
	else
	{
		m_fTime += 0.5f;

		m_tInfo.fJumpY += float(7.0f * -1 + (0.098 * m_fTime * m_fTime) / 2.f);
	}
}

void CPlayer::MoveFrame()
{
	switch(m_PlayerState)
	{
	case PLAYER_HIT:
		if(m_dwTime + m_Hit.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_Hit.iRenderFrame > m_Hit.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"wz_dmg.ogg");
				m_Hit.iRenderFrame = m_Hit.iStartFrame;
				m_PlayerState = PLAYER_WAITING;
			}
		}
		break;
	case PLAYER_WAITING:
		if(m_dwTime + m_Waiting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Waiting.iRenderFrame > m_Waiting.iEndFrame)
			{
				m_Waiting.iRenderFrame = m_Waiting.iStartFrame;
			}
		}
		break;

	case PLAYER_WAKING:
		if(m_dwTime + m_Waking.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Waking.iRenderFrame > m_Waking.iEndFrame)
			{
				m_Waking.iRenderFrame = m_Waking.iStartFrame;
			}
		}
		break;

	case PLAYER_DASH:
		if(m_dwTime + m_Dash.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Dash.iRenderFrame > m_Dash.iEndFrame)
			{
				CSoundMgr::GetInstance()->PlayPlayerEffect(L"dash_move.ogg");
				m_Dash.iRenderFrame = m_Dash.iStartFrame;
			}
		}
		break;

	case PLAYER_JUMP:
		if(m_dwTime + m_Jump.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(m_bJump == true)
			{
				if(m_bJumpMax)
				{
					if(++m_Jump.iRenderFrame > 6)
					{
						m_Jump.iRenderFrame = 4;
					}
				}
				else
				{
					if(++m_Jump.iRenderFrame > 3)
					m_Jump.iRenderFrame = 3;
				}
			}
		}
		break;

	case PLAYER_DASHATTCK:
		if(m_dwTime + m_DashAttck.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_DashAttck.iRenderFrame > m_DashAttck.iEndFrame)
			{
				m_DashAttck.iRenderFrame = m_DashAttck.iStartFrame;
				m_PlayerState = PLAYER_WAITING;
			}
		}
		break;

	case PLAYER_ATTACK1:
		if(m_dwTime + m_Attck1.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Attck1.iRenderFrame > m_Attck1.iEndFrame)
			{
				m_Attck1.iRenderFrame = m_Attck1.iStartFrame;
				if(m_dwKey & KEY_X)
				{
					m_PlayerState = PLAYER_ATTACK2;
				}
				else
				{
					m_bAttck1 = false;
					m_PlayerState = PLAYER_WAITING;
				}
			}
		}
		break;

	case PLAYER_ATTACK2:
		if(m_dwTime + m_Attck2.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Attck2.iRenderFrame > m_Attck2.iEndFrame)
			{
				m_Attck2.iRenderFrame = m_Attck2.iStartFrame;
				if(m_dwKey & KEY_X)
				{
					m_PlayerState = PLAYER_ATTACK3;
				}
				else
				{
					m_bAttck1 = false;
					m_PlayerState = PLAYER_WAITING;
				}
			}
		}
		break;

	case PLAYER_ATTACK3:
		if(m_dwTime + m_Attck3.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_Attck3.iRenderFrame > m_Attck3.iEndFrame)
			{
				m_Attck3.iRenderFrame = m_Attck3.iStartFrame;
				m_bAttck1 = false;
				m_PlayerState = PLAYER_WAITING;
			}
		}
		break;

	case PLAYER_VOIDCASTING:
		if(m_dwTime + m_SkillVoidCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillVoidCasting.iRenderFrame > 2)
			{
				m_SkillVoidCasting.iRenderFrame = 2;
			}
		}
		break;

	case PLAYER_BLACKHOLE_CASTING:
		if(m_dwTime + m_SkillVoidCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillVoidCasting.iRenderFrame > 2)
			{
				m_SkillVoidCasting.iRenderFrame = 2;
			}
		}
		break;

	case PLAYER_ICEFIELD_CASTING:
		if(m_dwTime + m_SkillVoidCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillVoidCasting.iRenderFrame > 2)
			{
				m_SkillVoidCasting.iRenderFrame = 2;
			}
		}
		break;

	case PLAYER_THNUDER_CALLING_CASTING:
		if(m_dwTime + m_SkillThunderCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillThunderCasting.iRenderFrame > 1)
			{
				m_SkillThunderCasting.iRenderFrame = 1;
			}
		}
		break;

	case PLAYER_HALLOWEEN_BUSTER_CASTING:
		if(m_dwTime + m_SkillVoidCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillVoidCasting.iRenderFrame > 2)
			{
				m_SkillVoidCasting.iRenderFrame = 2;
			}
		}
		break;
	case PLAYER_RUN_CASTING:
		if(m_dwTime + m_SkillThunderCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(++m_SkillThunderCasting.iRenderFrame > m_SkillThunderCasting.iEndFrame)
			{
				m_SkillThunderCasting.iRenderFrame = m_SkillThunderCasting.iStartFrame;
				m_PlayerState = PLAYER_WAITING;
				m_SkillCastingState = PLAYER_END;
				if(m_bRun == false)
				{
					m_bRun = true;
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX - 47, m_tInfo.fY + 27, SKILL_RUN, 0, ELEMENT_FIRE, m_tInfo));
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX + 49, m_tInfo.fY + 27, SKILL_RUN, 0, ELEMENT_ICE, m_tInfo));
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX + 42, m_tInfo.fY + 4, SKILL_RUN, 0, ELEMENT_LIGHT, m_tInfo));
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX - 40, m_tInfo.fY + 4, SKILL_RUN, 0, ELEMENT_DARK, m_tInfo));
				}
				else
				{
					list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
					list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
						
					for(iter; iter != iter_end; ++iter)
					{
						string strName = (*iter)->GetName();

						if(strName == "RunLight1" || strName == "RunLight2" || strName == "RunLight3" || strName == "RunLight4" 
							|| strName == "RunDark1" || strName == "RunDark2" || strName == "RunDark3" || strName == "RunDark4"
							|| strName == "RunIce1" || strName == "RunIce2" || strName == "RunIce3" || strName == "RunIce4"
							|| strName == "RunFire1" || strName == "RunFire2" || strName == "RunFire3" || strName == "RunFire4")
						{
							
							((CSkill*)(*iter))->SetDwRunClearTime(GetTickCount());
						}
					}
				}
			}
		}
	}

	if(m_CastingEnd)
	{
		if(++m_FrameCastingEnd.iRenderFrame > m_FrameCastingEnd.iEndFrame)
		{
			m_CastingEnd = false;
			m_FrameCastingEnd.iRenderFrame = m_FrameCastingEnd.iStartFrame;
		}
	}
}
RECT CPlayer::GetCollision(void)
{
	return m_Collision;
}

void CPlayer::Render(HDC _hdc)
{
	//Rectangle(_hdc, m_Collision.left - g_Scroll.x, m_Collision.top, m_Collision.right - g_Scroll.x, m_Collision.bottom);
	//Rectangle(_hdc, m_ShadowCollision.left - g_Scroll.x, m_ShadowCollision.top, m_ShadowCollision.right - g_Scroll.x, m_ShadowCollision.bottom);
	CImageMgr::GetInstance()->ImageRender(_hdc, "PlayerShadow", m_ShadowSize);

	//CImageMgr::GetInstance()->ImageRender(_hdc, "Halloween", Rect(0,0,120,120));
	//CImageMgr::GetInstance()->ImageRender(_hdc, "Halloween2",Rect(0,120,120,120));

	switch(m_PlayerState)
	{
	case PLAYER_HIT:
		if(m_strName == "PlayerLeft")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "PlayerHitLeft", m_ImageSize,m_Hit.iRenderFrame, 0);
		}
		else
		{
			CImageMgr::GetInstance()->ImageRender(_hdc, "PlayerHitRight", m_ImageSize,m_Hit.iRenderFrame, 0);
		}
		break;

	case PLAYER_WAITING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize,m_Waiting.iRenderFrame,m_PlayerState);
		break;

	case PLAYER_WAKING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize,m_Waking.iRenderFrame,m_PlayerState);
		break;

	case PLAYER_DASH:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize,m_Dash.iRenderFrame,m_PlayerState);
		break;

	case PLAYER_JUMP:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize,m_Jump.iRenderFrame,6);
		break;

	case PLAYER_DASHATTCK:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_DashAttck.iRenderFrame, 2);
		break;

	case PLAYER_ATTACK1:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck1.iRenderFrame, 8);
		//CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck1.iRenderFrame, 8,255,0,255);
		break;

	case PLAYER_ATTACK2:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck2.iRenderFrame, 9);
		//CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck2.iRenderFrame, 8,255,0,255);
		break;

	case PLAYER_ATTACK3:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck3.iRenderFrame, 10);
		//CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_Attck3.iRenderFrame, 8,255,0,255);
		break;

	case PLAYER_VOIDCASTING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_SkillVoidCasting.iRenderFrame, 5);
		break;

	case PLAYER_BLACKHOLE_CASTING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_SkillVoidCasting.iRenderFrame, 5);
		break;

	case PLAYER_ICEFIELD_CASTING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_SkillVoidCasting.iRenderFrame, 5);
		break;

	case PLAYER_THNUDER_CALLING_CASTING:
		if(m_strName == "PlayerLeft")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerLeftThunder", m_ImageSize, m_SkillThunderCasting.iRenderFrame, 0);
		}
		else
		{		
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerRightThunder", m_ImageSize, m_SkillThunderCasting.iRenderFrame, 0);
		}
		if(m_bSkillCastingEnd)
		{
			Rect rcMagicSize(int(m_tInfo.fX - 500) - g_Scroll.x, int(m_tInfo.fY - 80), 1003, 304);
			CImageMgr::GetInstance()->ImageRender(_hdc, "MagicCircle", rcMagicSize);
			Rect rcMagicCursor(int(m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - g_Scroll.x, int(m_tMagicCursor.fY - m_tMagicCursor.fCY / 2) + 60, (int)m_tMagicCursor.fCX, (int)m_tMagicCursor.fCY);
			CImageMgr::GetInstance()->ImageRender(_hdc, "MagicCursor", rcMagicCursor,m_SkillMagicCursor.iRenderFrame,0);
		}
		break;

	case PLAYER_RUN_CASTING:
		if(m_strName == "PlayerLeft")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerLeftThunder", m_ImageSize, m_SkillThunderCasting.iRenderFrame, 0);
		}
		else
		{		
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerRightThunder", m_ImageSize, m_SkillThunderCasting.iRenderFrame, 0);
		}
		break;

	case PLAYER_HALLOWEEN_BUSTER_CASTING:
		CImageMgr::GetInstance()->ImageRender(_hdc,m_strName, m_ImageSize, m_SkillVoidCasting.iRenderFrame, 5);

		if(m_bSkillCastingEnd)
		{
			Rect rcMagicCursor(int(m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - g_Scroll.x, int(m_tMagicCursor.fY - m_tMagicCursor.fCY / 2) + 60, (int)m_tMagicCursor.fCX, (int)m_tMagicCursor.fCY);
			CImageMgr::GetInstance()->ImageRender(_hdc, "MagicCursor", rcMagicCursor,m_SkillMagicCursor.iRenderFrame,0);
		}
		break;

	case PLAYER_ELEMENTALSHOWRE_CASTING:
		if(m_strName == "PlayerLeft")
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerElementalLeft", m_ImageSize, m_ElementalCasting.iRenderFrame, 0);
		}
		else
		{
			CImageMgr::GetInstance()->ImageRender(_hdc,"PlayerElementalRight", m_ImageSize, m_ElementalCasting.iRenderFrame, 0);
		}
		if(m_bSkillCastingEnd)
		{
			Rect rcMagicSize(int(m_tInfo.fX - 500) - g_Scroll.x, int(m_tInfo.fY - 80), 1003, 304);
			CImageMgr::GetInstance()->ImageRender(_hdc, "MagicCircle", rcMagicSize);
			Rect rcMagicCursor(int(m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - g_Scroll.x, int(m_tMagicCursor.fY - m_tMagicCursor.fCY / 2) + 60, (int)m_tMagicCursor.fCX, (int)m_tMagicCursor.fCY);
			CImageMgr::GetInstance()->ImageRender(_hdc, "MagicCursor", rcMagicCursor,m_SkillMagicCursor.iRenderFrame,0);
			if(m_iElementalCount >= 6 && m_ElementalEnd == false)
			{
				//float fX = (rcMagicCursor.X + 20) - float(rand() % 70);
				//float fY = rcMagicCursor.Y - float(rand() % 20 + 100);
				
				eELEMENT_TYPE ElementalType = eELEMENT_TYPE(rand() % 4);
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(float((m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - 20), float(rcMagicCursor.Y - 110), SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));

				ElementalType = eELEMENT_TYPE(rand() % 4);
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(float((m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - 70), float(rcMagicCursor.Y - 115), SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));

				ElementalType = eELEMENT_TYPE(rand() % 4);
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(float((m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) + 30), float(rcMagicCursor.Y - 130), SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));

				ElementalType = eELEMENT_TYPE(rand() % 4);
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(float((m_tMagicCursor.fX - m_tMagicCursor.fCX / 2)), float(rcMagicCursor.Y - 150), SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));

				ElementalType = eELEMENT_TYPE(rand() % 4);
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(float((m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) - 40), float(rcMagicCursor.Y - 130), SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));
				m_ElementalEnd = true;
			}
			else if(m_ElementalEnd == false)
			{
				float fX = (m_tMagicCursor.fX - m_tMagicCursor.fCX / 2) + 20 - float(rand() % 70);
				float fY = rcMagicCursor.Y - float(rand() % 20 + 100);
				if(m_dwCreateTime + 100 < GetTickCount())
				{
					m_dwCreateTime = GetTickCount();
					eELEMENT_TYPE ElementalType = eELEMENT_TYPE(rand() % 4);
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(fX, fY, SKILL_ELEMENTALSHOWRE,0,ElementalType, m_tInfo));
				}
			}
		}
		break;
	}

	if(m_CastingStart)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, "Casting", Rect(int((m_tInfo.fX - 75) - g_Scroll.x), (int)m_tInfo.fY - 115, 150, 150), m_FrameCastingStart.iRenderFrame, 0, 0, 0, 0);
	}
	else if(m_CastingEnd)
	{
		CImageMgr::GetInstance()->ImageRender(_hdc, "CastingEnd", Rect(int((m_tInfo.fX - 85) - g_Scroll.x), (int)m_tInfo.fY - 125, 172, 172), m_FrameCastingEnd.iRenderFrame, 0);
	}
		
	//아크틱 마법진

	/*static int iA = -300;
	iA += 10;
	CImageMgr::GetInstance()->ImageRender(_hdc, "CutScene", Rect(0,311,321,289));
	*/
	//각성 컷신

}

void CPlayer::Release(void)
{
	
}

void CPlayer::SkillCasting(void)
{

	switch(m_SkillCastingState)
	{
	case PLAYER_VOIDCASTING:
		if(m_dwTime + 20 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillVoidCasting.iRenderFrame > m_SkillVoidCasting.iEndFrame)
			{
				m_SkillVoidCasting.iRenderFrame = m_SkillVoidCasting.iStartFrame;
				m_iSkillCastingCount = 0;
				m_bSkillCasting = false;
				m_bSkillCastingEnd = false;
				m_SkillCastingState = PLAYER_END;
				if(m_strName == "PlayerLeft")
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX - 100, m_tInfo.fY, SKILL_VOID, -1, m_tInfo));
				}
				else
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX + 100, m_tInfo.fY, SKILL_VOID, 1, m_tInfo));
				}

				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
					
				for(iter; iter != iter_end; ++iter)
				{
					string strName = (*iter)->GetName();

					if(strName == "RunDark1" || strName == "RunDark2" || strName == "RunDark3")
					{
						((CSkill*)(*iter))->SetRun(true);
						((CSkill*)(*iter))->SetDwRunTime(GetTickCount());
						break;
					}
				}
			}
		}
		break;

	case PLAYER_BLACKHOLE_CASTING:
		if(m_dwTime + 20 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillVoidCasting.iRenderFrame > m_SkillVoidCasting.iEndFrame)
			{
				m_SkillVoidCasting.iRenderFrame = m_SkillVoidCasting.iStartFrame;
				m_iSkillCastingCount = 0;
				m_bSkillCasting = false;
				m_bSkillCastingEnd = false;
				m_SkillCastingState = PLAYER_END;
				if(m_strName == "PlayerLeft")
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX - 300, m_tInfo.fY, SKILL_BLACKHOLE, 0, m_tInfo));
				}

				else
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX + 300, m_tInfo.fY, SKILL_BLACKHOLE, 0, m_tInfo));
				}

				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
					
				for(iter; iter != iter_end; ++iter)
				{
					string strName = (*iter)->GetName();

					if(strName == "RunDark1" || strName == "RunDark2" || strName == "RunDark3")
					{
						((CSkill*)(*iter))->SetRun(true);
						((CSkill*)(*iter))->SetDwRunTime(GetTickCount());
						break;
					}
				}
			}
		}
		break;

	case PLAYER_HALLOWEEN_BUSTER_CASTING:
		if(m_dwMagicCursorTime + 20 < GetTickCount())
		{
			m_dwMagicCursorTime = GetTickCount();
			if(++m_SkillMagicCursor.iRenderFrame > m_SkillMagicCursor.iEndFrame)
			{
				m_SkillMagicCursor.iRenderFrame = m_SkillMagicCursor.iStartFrame;
			}
		}
		if(m_dwTime + m_SkillVoidCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillVoidCasting.iRenderFrame > m_SkillVoidCasting.iEndFrame)
			{
				m_SkillVoidCasting.iRenderFrame = m_SkillVoidCasting.iStartFrame;
				m_iSkillCastingCount = 0;
				m_bSkillCasting = false;
				m_bSkillCastingEnd = false;
				m_SkillCastingState = PLAYER_END;
				//여기서 할로윈 생성. 하자!!
				if(m_strName == "PlayerLeft")
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tMagicCursor.fX + 483, m_tMagicCursor.fY + 43, SKILL_HALLOWEEN_BUSTER, -18, +15, m_tInfo));
				}
				else
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tMagicCursor.fX - 483, m_tMagicCursor.fY + 43, SKILL_HALLOWEEN_BUSTER, +18, +15, m_tInfo));
				}

				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
					
				for(iter; iter != iter_end; ++iter)
				{
					string strName = (*iter)->GetName();

					if(strName == "RunFire1" || strName == "RunFire2" || strName == "RunFire3")
					{
						((CSkill*)(*iter))->SetRun(true);
						((CSkill*)(*iter))->SetDwRunTime(GetTickCount());
						break;
					}
				}
			}
		}
		break;

	case PLAYER_THNUDER_CALLING_CASTING:
		if(m_dwMagicCursorTime + m_SkillMagicCursor.dwFrameTime < GetTickCount())
		{
			m_dwMagicCursorTime = GetTickCount();
			if(++m_SkillMagicCursor.iRenderFrame > m_SkillMagicCursor.iEndFrame)
			{
				m_SkillMagicCursor.iRenderFrame = m_SkillMagicCursor.iStartFrame;
			}
		}
		if(m_dwTime + m_SkillThunderCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillThunderCasting.iRenderFrame > m_SkillThunderCasting.iEndFrame)
			{	
				++m_iThunderCount;
				m_SkillThunderCasting.iRenderFrame = 1;
				m_SkillMagicCursor.iRenderFrame = m_SkillMagicCursor.iStartFrame;
				m_bThunder = false;
				CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tMagicCursor.fX - 10, m_tMagicCursor.fY - 200, SKILL_THUNDER_CALLING, 0, m_tInfo));
				
				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
					
				for(iter; iter != iter_end; ++iter)
				{
					string strName = (*iter)->GetName();

					if(strName == "RunLight1" || strName == "RunLight2" || strName == "RunLight3")
					{
						((CSkill*)(*iter))->SetRun(true);
						((CSkill*)(*iter))->SetDwRunTime(GetTickCount());
						break;
					}
				}
			}
		}
		break;
		
	case PLAYER_ICEFIELD_CASTING:
		if(m_dwTime + 20 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_SkillVoidCasting.iRenderFrame > m_SkillVoidCasting.iEndFrame)
			{
				m_SkillVoidCasting.iRenderFrame = m_SkillVoidCasting.iStartFrame;
				m_iSkillCastingCount = 0;
				m_bSkillCasting = false;
				m_bSkillCastingEnd = false;
				m_SkillCastingState = PLAYER_END;
				if(m_strName == "PlayerLeft")
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX - 300, m_tInfo.fY + 80, SKILL_ICEFIELD, -0, m_tInfo));
				}
				else
				{
					CObjMgr::GetInstance()->GetList()[OBJ_SKILL].push_back(CFactory<CSkill>::CreateObj(m_tInfo.fX + 300, m_tInfo.fY + 80, SKILL_ICEFIELD, 0, m_tInfo));
				}

				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();
					
				for(iter; iter != iter_end; ++iter)
				{
					string strName = (*iter)->GetName();

					if(strName == "RunIce1" || strName == "RunIce2" || strName == "RunIce3")
					{
						((CSkill*)(*iter))->SetRun(true);
						((CSkill*)(*iter))->SetDwRunTime(GetTickCount());
						break;
					}
				}
			}
		}
		break;

	case PLAYER_ELEMENTALSHOWRE_CASTING:
		if(m_dwMagicCursorTime + m_SkillMagicCursor.dwFrameTime < GetTickCount())
		{
			m_dwMagicCursorTime = GetTickCount();
			if(++m_SkillMagicCursor.iRenderFrame > m_SkillMagicCursor.iEndFrame)
			{
				m_SkillMagicCursor.iRenderFrame = m_SkillMagicCursor.iStartFrame;
			}
		}
		if(m_dwTime + m_ElementalCasting.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_ElementalCasting.iRenderFrame > m_ElementalCasting.iEndFrame)
			{
				++m_iElementalCount;
				m_ElementalCasting.iRenderFrame = m_ElementalCasting.iStartFrame;
			}
		}
		break;
	}
}


bool CPlayer::PtInCircle(float _MagicX, float _MagicY, float _MagicWidth, float _MagicHeight, float _CursorX, float _CursorY)
{
	if((_MagicX - _CursorX) * (_MagicX - _CursorX) / (_MagicWidth * _MagicWidth)+ (_MagicY - _CursorY) * (_MagicY - _CursorY) / (_MagicHeight * _MagicHeight) <= 0.25)
	{
		return true;
	}
	return false;
}
bool CPlayer::CastingKeyCheck(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!(dwKey & KEY_UP) && !(dwKey & KEY_DOWN) && !(dwKey & KEY_LEFT) && !(dwKey & KEY_RIGHT))
	{
		return true;
	}
	else
		return false;
}