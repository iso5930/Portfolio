#include "StdAfx.h"
#include "Elvengard.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Factory.h"
#include "Boss.h"
#include "MonsterHp.h"
#include "SoundMgr.h"
#include "BloodLugaru.h"

CElvengard::CElvengard(void)
{

}

CElvengard::~CElvengard(void)
{
	Release();
}

void CElvengard::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	//CImageMgr::GetInstance()->LoadBmp("Villmark1", L"../Image/Map/Vilmark1.bmp");
	CImageMgr::GetInstance()->LoadBmp("Elvengard", L"../Image/Map/Elvengard.bmp");
	ElvenLoadData();
	CCollisionMgr::GetInstance()->SetTile(&m_vecTile);
	m_dwTime = GetTickCount();
	CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fX = 860;
	CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fY = 300;
	m_bTile = false;
	CSoundMgr::GetInstance()->PlayBGM(L"ElvenGard.mp3");

	//여기부터는 테스트용 
	//CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].push_back(CFactory<CBloodLugaru>::CreateObj(600,400));	
	//이거 나중에 지울거 test용 몬스터

	if(CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].empty())
	{
		CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].push_back(CFactory<CMonsterHp>::CreateObj());
	}	
}

int CElvengard::Progress(void)
{
	CObjMgr::GetInstance()->Progress();

	CCollisionMgr::GetInstance()->Progress();

	if(GetAsyncKeyState('R') & 0x8000)
	{
		if(m_dwTime + 500 < GetTickCount())
		{
			m_dwTime = GetTickCount();

			if(m_bTile)
				m_bTile = false;
			else
				m_bTile = true;
		}
	}

	if(GetAsyncKeyState('P') & 0x8000)
	{
		CSceneMgr::GetInstance()->ChangeScene(SCENE_MENU);
	}

	CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

	RECT rcPlayer = ((CPlayer*)pPlayer)->GetCollision();

	for(int i = 144; i < 145; ++i)
	{
		RECT rcSource = { long(m_vecTile[i]->m_fX), long(m_vecTile[i]->m_fY), long(m_vecTile[i]->m_fX + m_vecTile[i]->m_fCX), long(m_vecTile[i]->m_fY + m_vecTile[i]->m_fCY) };

		RECT rcDist;
		if(IntersectRect(&rcDist, &rcPlayer, &rcSource))
		{
			CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fX = 400;
			CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fY = 450;
			CSceneMgr::GetInstance()->ChangeScene(SCENE_SERIAROOM);
		}
	}

	for(int i = 223; i <= 319; i += 32)
	{
		RECT rcSource = { long(m_vecTile[i]->m_fX), long(m_vecTile[i]->m_fY), long(m_vecTile[i]->m_fX + m_vecTile[i]->m_fCX), long(m_vecTile[i]->m_fY + m_vecTile[i]->m_fCY) };

		RECT rcDist;
		if(IntersectRect(&rcDist, &rcPlayer, &rcSource))
		{
			//여기서 빌마르크로!!
			CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fX = 400;
			CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo()->fY = 450;
			CSceneMgr::GetInstance()->ChangeScene(SCENE_VILLMARK);
		}
	}

	//223, 255, 287, 319

	//32 차이

	return 0;
}

void CElvengard::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Elvengard",Rect(0 - g_Scroll.x ,0 - g_Scroll.y ,1600, 600),0,0,255,0,255);
	//CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Villmark1",Rect(0 - g_Scroll.x ,0 - g_Scroll.y ,1600, 600),0,0,255,0,255);
	if(m_bTile)
	{
		TileRender();
	}
	CObjMgr::GetInstance()->Render(m_BackBuffer.GetMemDC());
	BitBlt(_hdc, 0, 0, 800, 600, m_BackBuffer.GetMemDC(), 0, 0, SRCCOPY);

	
}
void CElvengard::TileRender(void)
{
	Rect m_TileSize;
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			int iIndex = j + i * 32;
			if(iIndex < 0 || iIndex >= 12 * 32)
					continue;
			m_TileSize.X = (int)m_vecTile[iIndex]->m_fX - g_Scroll.x;
			m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY - g_Scroll.y;
			m_TileSize.Width = TILECX;
			m_TileSize.Height = TILECY;
			CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile", m_TileSize, m_vecTile[iIndex]->m_iImage, 0, 191, 191, 191);
			//144 ~ 145
		}
	}
}
void CElvengard::Release(void)
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecTile.clear();

	list<CObj*>::iterator Objiter = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].begin();
	list<CObj*>::iterator Objiter_end = CObjMgr::GetInstance()->GetList()[OBJ_SKILL].end();

	for(Objiter; Objiter != Objiter_end; ++Objiter)
	{
		SAFE_DELETE(*Objiter);
	}

	CObjMgr::GetInstance()->GetList()[OBJ_SKILL].clear();


	Objiter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
	Objiter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

	for(Objiter; Objiter != Objiter_end; ++Objiter)
	{
		SAFE_DELETE(*Objiter);
	}

	CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].clear();	
}
void CElvengard::ElvenLoadData()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/Elven.dat", "rb");

	int iSize = 0;

	fread(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		delete m_vecTile[i];
		m_vecTile[i] = NULL;
	}
	m_vecTile.clear();

	for(int i = 0; i < iSize; ++i)
	{
		TILE* pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);

		m_vecTile.push_back( pTile );
	}

	fclose(pFile);	
}