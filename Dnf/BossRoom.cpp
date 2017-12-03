#include "StdAfx.h"
#include "BossRoom.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "ImageMgr.h"
#include "Factory.h"
#include "Boss.h"
#include "CollisionMgr.h"
#include "Player.h"

CBossRoom::CBossRoom(void)
{
}

CBossRoom::~CBossRoom(void)
{
	Release();
}

void CBossRoom::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadBmp("BossRoom", L"../Image/Map/VilmarkBoss.bmp");
	CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
	((CPlayer*)pObj)->SetRun(false);
	BossRoomLoadData();
	CCollisionMgr::GetInstance()->SetTile(&m_vecTile);
	CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].push_back(CFactory<CBoss>::CreateObj());
	CSoundMgr::GetInstance()->PlayBGM(L"vilmark_boss.ogg");
	m_dwTime = GetTickCount();
}

int CBossRoom::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	return 0;
}

void CBossRoom::FrameMove(void)
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

void CBossRoom::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"BossRoom",Rect(0 - g_Scroll.x ,0 - g_Scroll.y ,1600, 600),0,0,255,0,255);
	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "Minimap", Rect(589, 0, 211,35),0,0);
	if(! (CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty()))
	{
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(-20  - g_Scroll.x, 282, 131, 240),0,0,255,0,255);
	}
	else
	{
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Gate_right", Rect(-20  - g_Scroll.x, 282, 131, 240),m_GateFrame.iRenderFrame,0,255,0,255);
	}

	CObjMgr::GetInstance()->Render(m_BackBuffer.GetMemDC());
	BitBlt(_hdc, 0, 0, 800, 600, m_BackBuffer.GetMemDC(), 0, 0, SRCCOPY);
}

void CBossRoom::Release(void)
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

void CBossRoom::BossRoomLoadData()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/BossRoom.dat", "rb");

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