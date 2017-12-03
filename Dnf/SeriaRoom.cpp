#include "StdAfx.h"
#include "SeriaRoom.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Player.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "Seria.h"
#include "Store.h"
#include "HUD.h"
#include "Info.h"
#include "Combo.h"
#include "SoundMgr.h"
CSeriaRoom::CSeriaRoom(void)
	:m_ImageSize(0,0,800,600)
{

}

CSeriaRoom::~CSeriaRoom(void)
{
	Release();
}


void CSeriaRoom::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadBmp("SeriaRoom", L"../Image/Map/SeriaRoom.bmp");
	
	CImageMgr::GetInstance()->LoadBmp("Tile",L"../Image/Tile.bmp");
	CImageMgr::GetInstance()->LoadBmp("MouseOver", L"../Image/Item/MouseOver.bmp");
	CImageMgr::GetInstance()->LoadBmp("HUD", L"../Image/UI/HUD3.bmp");
	m_dwTime = GetTickCount();

	if(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].empty())
	{
		CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].push_back(CFactory<CPlayer>::CreateObj());
		CObjMgr::GetInstance()->GetList()[OBJ_HUD].push_back(CFactory<CHUD>::CreateObj());
		CCollisionMgr::GetInstance()->SetPlayer((CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()));
		CObjMgr::GetInstance()->GetList()[OBJ_INFO].push_back(CFactory<CInfo>::CreateObj());
		CObjMgr::GetInstance()->GetList()[OBJ_COMBO].push_back(CFactory<CCombo>::CreateObj());
	}
	if(CObjMgr::GetInstance()->GetList()[OBJ_NPC].empty())
	{
		CObjMgr::GetInstance()->GetList()[OBJ_NPC].push_back(CFactory<CSeria>::CreateObj());
		CObjMgr::GetInstance()->GetList()[OBJ_STORE].push_back(CFactory<CStore>::CreateObj());
	}
	
	m_bTile = false;
	LoadData();
	CCollisionMgr::GetInstance()->SetTile(&m_vecTile);

	CSoundMgr::GetInstance()->PlayBGM(L"seria_gate.ogg");
}

int CSeriaRoom::Progress(void)
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

	for(int i = 182; i < 186; ++i)
	{
		RECT rcSource = { long(m_vecTile[i]->m_fX), long(m_vecTile[i]->m_fY), long(m_vecTile[i]->m_fX + m_vecTile[i]->m_fCX), long(m_vecTile[i]->m_fY + m_vecTile[i]->m_fCY) };

		RECT rcDist;
		if(IntersectRect(&rcDist, &rcPlayer, &rcSource))
		{
			//여기서 신 체인지
			CSceneMgr::GetInstance()->ChangeScene(SCENE_ELVENGARD);
		}
	}
	return 0;
}

void CSeriaRoom::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "SeriaRoom", m_ImageSize,0,0,255,0,255);
	CObjMgr::GetInstance()->Render(m_BackBuffer.GetMemDC());
	if(m_bTile)
		TileRender();

	//static int iA = 0;

	//HDC			dcTemp = CreateCompatibleDC(GetDC(g_hwnd));
	//HBITMAP		hBitMap = CreateCompatibleBitmap(GetDC(g_hwnd),800,600);

	//HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitMap);

	//BitBlt(dcTemp,0,0,800,600,m_BackBuffer.GetMemDC(),0,0,SRCCOPY);

	//BLENDFUNCTION	tFunction;
	//tFunction.BlendOp = AC_SRC_OVER;
	//tFunction.BlendFlags = 0;
	//tFunction.SourceConstantAlpha = 255;	//이게 투명한 정도를 나타낸다 0 ~ 255
	//tFunction.AlphaFormat = 0;

	//if(++iA >= 30)
	//{
	//	iA = 0;
	//}

	//CImageMgr::GetInstance()->ImageRender(dcTemp, "Cutin", Rect(0,0,800,600),iA,0,123,123,123);

	//AlphaBlend(m_BackBuffer.GetMemDC(), 0, 0, 800, 600, dcTemp,0,0,800,600,tFunction); // 알파 블렌딩

	BitBlt(_hdc,0,0,800,600,m_BackBuffer.GetMemDC(),0,0,SRCCOPY);
}

void CSeriaRoom::Release(void)
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	
	m_vecTile.clear();
	
	list<CObj*>::iterator iter2 = CObjMgr::GetInstance()->GetList()[OBJ_NPC].begin();

	SAFE_DELETE(*iter2);
	
	CObjMgr::GetInstance()->GetList()[OBJ_NPC].erase(iter2);

	iter2 = CObjMgr::GetInstance()->GetList()[OBJ_STORE].begin();

	SAFE_DELETE(*iter2);
	
	CObjMgr::GetInstance()->GetList()[OBJ_STORE].erase(iter2);
}

void CSeriaRoom::LoadData(void)
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/Seria.dat", "rb");

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
void CSeriaRoom::TileRender(void)
{
	Rect m_TileSize;

	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 16; ++j)
		{
			int iIndex = j + i * 16;
			m_TileSize.X = (int)m_vecTile[iIndex]->m_fX;
			m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY;
			m_TileSize.Width = TILECX;
			m_TileSize.Height = TILECY;
			CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile", m_TileSize, m_vecTile[iIndex]->m_iImage, 0, 191, 191, 191);
		}
	}
}