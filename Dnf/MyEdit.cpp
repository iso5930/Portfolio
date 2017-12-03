#include "StdAfx.h"
#include "MyEdit.h"
#include "ObjMgr.h"
#include "ImageMgr.h"
#include "Factory.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CMyEdit::CMyEdit(void)
{

}

CMyEdit::~CMyEdit(void)
{
	Release();
}

void CMyEdit::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadImage("Tile",L"../Image/Tile.png");
	CImageMgr::GetInstance()->LoadBmp("Tile",L"../Image/Tile.bmp");
	CImageMgr::GetInstance()->LoadImage("SeriaRoom", L"../Image/Map/SeriaRoom.bmp");
	CImageMgr::GetInstance()->LoadBmp("Elvengard", L"../Image/Map/Elvengard.bmp");
	CImageMgr::GetInstance()->LoadBmp("Villmark1", L"../Image/Map/Vilmark.bmp");
	CImageMgr::GetInstance()->LoadBmp("Villmark2_edit", L"../Image/Map/Vilmark2_edit.bmp");
	CImageMgr::GetInstance()->LoadBmp("BossRoom_edit", L"../Image/Map/Boss_edit.bmp");

	m_eEditType = EDIT_SERIA;
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 16; ++j)
		{
			m_vecTile.push_back( new TILE(float(j * TILECX), float(i * TILECY), (float)TILECX, (float)TILECY, TILE_NORMAL, 0) );
		}
	}
	m_iOption = 0;
	m_ptScroll.x = 0;
	m_ptScroll.y = 0;
}

int CMyEdit::Progress(void)
{
	POINT	ptMouse = CMouse::GetMousePos();

	DWORD	dwKey = CKeyMgr::GetInstance()->GetKeyState();
	
	if(dwKey & KEY_LBUTTON)
	{
		int iIndex;
		switch(m_eEditType)
		{
		case EDIT_SERIA:
			iIndex = ptMouse.x / TILECX + ptMouse.y / TILECY * 16;
			if(iIndex < 0 || iIndex >= 12 * 16)
				return 0;
			break;
		case EDIT_ELVEN:
			iIndex = (-m_ptScroll.x + ptMouse.x) / TILECX + (-m_ptScroll.y + ptMouse.y) / TILECY * 32;
			if(iIndex < 0 || iIndex >= 12 * 32)
				return 0;
			break;

		case EDIT_VILLMARK1:
			 iIndex = (-m_ptScroll.x + ptMouse.x) / TILECX + (-m_ptScroll.y + ptMouse.y) / TILECY * 36;
			if(iIndex < 0 || iIndex >= 12 * 36)
				return 0;
			break;

		case EDIT_VILLMARK2:
			iIndex = (-m_ptScroll.x + ptMouse.x) / TILECX + (-m_ptScroll.y + ptMouse.y) / TILECY * 32;
			if(iIndex < 0 || iIndex >= 12 * 32)
				return 0;
			break;

		case EDIT_BOSSROOM:
				iIndex = (-m_ptScroll.x + ptMouse.x) / TILECX + (-m_ptScroll.y + ptMouse.y) / TILECY * 32;
			if(iIndex < 0 || iIndex >= 12 * 32)
				return 0;

			break;
		}
		m_vecTile[iIndex]->m_iImage = m_iOption;
		m_vecTile[iIndex]->m_eOption = eTILE_TYPE(m_iOption); 
	}
	if(dwKey & KEY_LEFT)
	{
		m_ptScroll.x += 10;
		if(m_ptScroll.x >= 0)
			m_ptScroll.x = 0;
	}

	if(dwKey & KEY_RIGHT)
	{
		m_ptScroll.x -= 10;
		if(m_ptScroll.x <= -800)
			m_ptScroll.x = -800;
	}

	if(dwKey & KEY_UP)
	{
		m_ptScroll.y += 10;
	}

	if(dwKey & KEY_DOWN)
	{
		m_ptScroll.y -= 10;
	}
	if(GetAsyncKeyState('1') & 0x8000)
	{
		m_iOption = 0;
	}

	if(GetAsyncKeyState('2') & 0x8000)
	{
		m_iOption = 1;
	}

	if(GetAsyncKeyState('3') & 0x8000)
	{
		m_iOption = 2;
	}

	if(dwKey & KEY_4)
	{
		if(MessageBox(g_hwnd,L"엘븐 가드 로드",L"알림",MB_YESNO) == IDYES)
		{
			Release();
			ElvenEdit();
			m_eEditType = EDIT_ELVEN;
		}
	}

	if(dwKey & KEY_5)
	{
		if(MessageBox(g_hwnd,L"빌마르크 1번방 로드",L"알림",MB_YESNO) == IDYES)
		{
			Release();
			VillMarkEdit1();
			m_eEditType = EDIT_VILLMARK1;
		}
	}

	if(dwKey & KEY_6)
	{
		if(MessageBox(g_hwnd,L"빌마르크 2번방 로드",L"알림",MB_YESNO) == IDYES)
		{
			Release();
			VillMarkEdit2();
			m_eEditType = EDIT_VILLMARK2;
		}
	}

	
	if(GetAsyncKeyState('7'))
	{
		if(MessageBox(g_hwnd,L"빌마르크 보스룸 로드",L"알림",MB_YESNO) == IDYES)
		{
			Release();
			BossRoomEdit();
			m_eEditType = EDIT_BOSSROOM;
		}
	}


	if(GetAsyncKeyState('S') & 0x8000)
	{
		switch(m_eEditType)
		{
		case EDIT_SERIA:
			SaveData();
			break;
		case EDIT_ELVEN:
			ElvenSaveData();
			break;
		case EDIT_VILLMARK1:
			VillMarkSaveData1();
			break;

		case EDIT_VILLMARK2:
			VillMarkSaveData2();
			break;
		case EDIT_BOSSROOM:
			BossRoomSaveData();
			break;
		}
		MessageBox(g_hwnd, L"저장완료", L"완료", 0 );
	}

	if(GetAsyncKeyState('L') & 0x8000)
	{
		switch(m_eEditType)
		{
		case EDIT_SERIA:
			LoadData();
			break;
		case EDIT_ELVEN:
			ElvenLoadData();
			break;

		case EDIT_VILLMARK1:
			VillMarkLoadData1();
			break;

		case EDIT_VILLMARK2:
			VillMarkLoadData2();
			break;

		case EDIT_BOSSROOM:
			BossRoomLoadData();
			break;
		}
		MessageBox(g_hwnd, L"로드완료", L"완료", 0 );
	}

	if(GetAsyncKeyState('P') & 0x8000)
	{
		CSceneMgr::GetInstance()->ChangeScene(SCENE_MENU);
	} //이전화면으로 

	return 0;
}


void CMyEdit::VillMarkEdit1()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 36; ++j)
		{
			m_vecTile.push_back( new TILE(float(j * TILECX), float(i * TILECY), (float)TILECX, (float)TILECY, TILE_NORMAL, 0) );
		}
	}
}

void CMyEdit::VillMarkEdit2()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			m_vecTile.push_back( new TILE(float(j * TILECX), float(i * TILECY), (float)TILECX, (float)TILECY, TILE_NORMAL, 0) );
		}
	}
}

void CMyEdit::ElvenEdit()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			m_vecTile.push_back( new TILE(float(j * TILECX), float(i * TILECY), (float)TILECX, (float)TILECY, TILE_NORMAL, 0) );
		}
	}
}
void CMyEdit::BossRoomEdit()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			m_vecTile.push_back( new TILE(float(j * TILECX), float(i * TILECY), (float)TILECX, (float)TILECY, TILE_NORMAL, 0) );
		}
	}
}
void CMyEdit::Render(HDC _hdc)
{	
	int iCullStartX = -m_ptScroll.x / 50;		//abs
	int iCullStartY = -m_ptScroll.y / 50;		//abs

	int iCullEndX = iCullStartX + 800 / 50 + 2;
	int iCullEndY = iCullStartY + 600 / 50 + 2;

	switch(m_eEditType)
	{
	case EDIT_SERIA:
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"SeriaRoom",Rect(0,0,800,600));

		for(int i = 0; i < 12; ++i)
		{
			for(int j = 0; j < 16; ++j)
			{
				int iIndex = j + i * 16;

				m_TileSize.X = (int)m_vecTile[iIndex]->m_fX;
				m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY;
				m_TileSize.Width = TILECX;
				m_TileSize.Height = TILECY;
				CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile",m_TileSize,m_vecTile[iIndex]->m_iImage,0,191,191,191);
			}
		}
		break;

	case EDIT_ELVEN:
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "Elvengard",Rect(0 + m_ptScroll.x ,0  + m_ptScroll.y ,1600, 600),0,0,255,0,255);
		for(int i = iCullStartY; i < iCullEndY; ++i)
		{
			for(int j = iCullStartX; j < iCullEndX; ++j)
			{
				int iIndex = j + i * 32;
				if(iIndex < 0 || iIndex >= 12 * 32)
					continue;
				m_TileSize.X = (int)m_vecTile[iIndex]->m_fX + m_ptScroll.x;
				m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY + m_ptScroll.y;
				m_TileSize.Width = TILECX;
				m_TileSize.Height = TILECY;
				CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile",m_TileSize,m_vecTile[iIndex]->m_iImage,0,191,191,191);
			}
		}
		break;

	case EDIT_VILLMARK1:
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "Villmark1",Rect(0 + m_ptScroll.x ,0  + m_ptScroll.y ,1789, 600),0,0,255,0,255);
		for(int i = iCullStartY; i < iCullEndY; ++i)
		{
			for(int j = iCullStartX; j < iCullEndX; ++j)
			{
				int iIndex = j + i * 36;
				if(iIndex < 0 || iIndex >= 12 * 36)
					continue;
				m_TileSize.X = (int)m_vecTile[iIndex]->m_fX + m_ptScroll.x;
				m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY + m_ptScroll.y;
				m_TileSize.Width = TILECX;
				m_TileSize.Height = TILECY;
				CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile",m_TileSize,m_vecTile[iIndex]->m_iImage,0,191,191,191);
			}
		}
		break;

	case EDIT_VILLMARK2:
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "Villmark2_edit",Rect(0 + m_ptScroll.x ,0  + m_ptScroll.y ,1600 , 600),0,0,255,0,255);
		for(int i = iCullStartY; i < iCullEndY; ++i)
		{
			for(int j = iCullStartX; j < iCullEndX; ++j)
			{
				int iIndex = j + i * 32;
				if(iIndex < 0 || iIndex >= 12 * 32)
					continue;
				m_TileSize.X = (int)m_vecTile[iIndex]->m_fX + m_ptScroll.x;
				m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY + m_ptScroll.y;
				m_TileSize.Width = TILECX;
				m_TileSize.Height = TILECY;
				CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile",m_TileSize,m_vecTile[iIndex]->m_iImage,0,191,191,191);
			}
		}
		break;
	case EDIT_BOSSROOM:
		CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "BossRoom_edit",Rect(0 + m_ptScroll.x ,0  + m_ptScroll.y ,1600 , 600),0,0,255,0,255);
		for(int i = iCullStartY; i < iCullEndY; ++i)
		{
			for(int j = iCullStartX; j < iCullEndX; ++j)
			{
				int iIndex = j + i * 32;
				if(iIndex < 0 || iIndex >= 12 * 32)
					continue;
				m_TileSize.X = (int)m_vecTile[iIndex]->m_fX + m_ptScroll.x;
				m_TileSize.Y = (int)m_vecTile[iIndex]->m_fY + m_ptScroll.y;
				m_TileSize.Width = TILECX;
				m_TileSize.Height = TILECY;
				CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(),"Tile",m_TileSize,m_vecTile[iIndex]->m_iImage,0,191,191,191);
			}
		}
		break;
	}
	
	BitBlt(_hdc,0,0,800,600,m_BackBuffer.GetMemDC(),0,0,SRCCOPY);
}

void CMyEdit::Release(void)
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecTile.clear();
}

void CMyEdit::SaveData()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/Seria.dat", "wb");

	int iSize = m_vecTile.size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}
	
	fclose(pFile);
}

void CMyEdit::LoadData()
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

void CMyEdit::ElvenSaveData()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/Elven.dat", "wb");

	int iSize = m_vecTile.size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}
	
	fclose(pFile);
}
void CMyEdit::ElvenLoadData()
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

void CMyEdit::VillMarkSaveData1()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/VillMark1.dat", "wb");

	int iSize = m_vecTile.size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}
	
	fclose(pFile);
}

void CMyEdit::VillMarkLoadData1()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/VillMark1.dat", "rb");

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

void CMyEdit::VillMarkSaveData2()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/VillMark2.dat", "wb");

	int iSize = m_vecTile.size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}
	
	fclose(pFile);
}

void CMyEdit::VillMarkLoadData2()
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

void CMyEdit::BossRoomLoadData()
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

void CMyEdit::BossRoomSaveData()
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, "../MapData/BossRoom.dat", "wb");

	int iSize = m_vecTile.size();

	fwrite(&iSize, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}
	
	fclose(pFile);
}	
