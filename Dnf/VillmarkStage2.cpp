#include "StdAfx.h"
#include "VillmarkStage2.h"
#include "ImageMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "CowCaptain.h"
#include "SceneMgr.h"
#include "Player.h"


CVillmarkStage2::CVillmarkStage2(void)
	:m_GateFrame(1,2,200)
{

}

CVillmarkStage2::~CVillmarkStage2(void)
{
	Release();
}

void CVillmarkStage2::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadBmp("Villmark2", L"../Image/Map/Vilmark2.bmp");
	CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
	((CPlayer*)pObj)->SetRun(false);
	CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].push_back(CFactory<CCowCaptain>::CreateObj(800,300));
	MapLoad();
	CCollisionMgr::GetInstance()->SetTile(&m_vecTile);
	m_dwTime = GetTickCount();
}

int CVillmarkStage2::Progress(void)
{
	CObjMgr::GetInstance()->Progress();

	CCollisionMgr::GetInstance()->Progress();

	FrameMove();

	if(CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty())
	{
		for(size_t i = 0; i < m_vecTile.size(); ++i)
		{
			if(m_vecTile[i]->m_eOption == TILE_WARP)
			{
				RECT rcSource = { long(m_vecTile[i]->m_fX), long(m_vecTile[i]->m_fY), long(m_vecTile[i]->m_fX + m_vecTile[i]->m_fCX), long(m_vecTile[i]->m_fY + m_vecTile[i]->m_fCY) };

				RECT rcDist;

				if(IntersectRect(&rcDist, &(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetShadowCollision()), &rcSource))
				{
					CSceneMgr::GetInstance()->ChangeScene(SCENE_BOSSROOM);
					CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->SetPos(154,400);
				}
			}
		}
	}


	return 0;
}

void CVillmarkStage2::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Villmark2",Rect(0 - g_Scroll.x ,0 - g_Scroll.y ,1600, 600),0,0,255,0,255);

	if(! (CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty()))
	{
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(1464  - g_Scroll.x, 269, 131, 240),0,0,255,0,255);
		//CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(-20  - g_Scroll.x, 282, 131, 240),0,0,255,0,255);
	}
	else
	{
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(1464  - g_Scroll.x, 269, 131, 240),m_GateFrame.iRenderFrame,0,255,0,255);
		//CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(-20  - g_Scroll.x, 282, 131, 240),m_GateFrame.iRenderFrame,0,255,0,255);
	}

	CObjMgr::GetInstance()->Render(m_BackBuffer.GetMemDC());
	BitBlt(_hdc, 0, 0, 800, 600, m_BackBuffer.GetMemDC(), 0, 0, SRCCOPY);
}

void CVillmarkStage2::FrameMove(void)
{
	if(CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty())
	{
		if(m_dwTime + m_GateFrame.dwFrameTime < GetTickCount())
		{
			m_dwTime = GetTickCount();
			if(++m_GateFrame.iRenderFrame > m_GateFrame.iEndFrame)
			{
				m_GateFrame.iRenderFrame = 1;
			}
		}
	}
}

void CVillmarkStage2::Release(void)
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
}
void CVillmarkStage2::MapLoad(void)
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/VillMark2.dat", "rb");

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