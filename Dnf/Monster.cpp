#include "StdAfx.h"
#include "Monster.h"
#include "SceneMgr.h"

CMonster::CMonster(void)
{

}
CMonster::CMonster(string strName, float _fX, float _fY, float _fCX, float _fCY)
	:CObj(strName,_fX, _fY, _fCX, _fCY)
{

}


CMonster::~CMonster(void)
{
	Release();
}

void CMonster::Init(void)
{

}

int CMonster::Progress(void)
{
	return 0;
}

void CMonster::Render(HDC _hdc)
{

}

void CMonster::Release(void)
{

}

bool CMonster::CowCaptain(void)
{
	RECT rcMonster = m_ShadowCollision;
	INFO* m_pInfo = &m_tInfo;

	vector<TILE*>::iterator iter = CSceneMgr::GetInstance()->GetScene()->GetTile()->begin();
	vector<TILE*>::iterator iter_end = CSceneMgr::GetInstance()->GetScene()->GetTile()->end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->m_eOption == TILE_BLOCK || (*iter)->m_eOption == TILE_WARP)//못가는 타일일때만
		{
			RECT rcSource = { long((*iter)->m_fX), long((*iter)->m_fY), long((*iter)->m_fX + (*iter)->m_fCX), long((*iter)->m_fY + (*iter)->m_fCY) };

			RECT rcDist;

			if(IntersectRect(&rcDist, &rcMonster, &rcSource))
			{
				return true;
			}
		}
	}
	return false;
}

void CMonster::TileCheck(void)
{
	RECT rcMonster = m_ShadowCollision;
	INFO* m_pInfo = &m_tInfo;

	vector<TILE*>::iterator iter = CSceneMgr::GetInstance()->GetScene()->GetTile()->begin();
	vector<TILE*>::iterator iter_end = CSceneMgr::GetInstance()->GetScene()->GetTile()->end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->m_eOption == TILE_NORMAL)
			continue;

		if((*iter)->m_eOption == TILE_BLOCK || (*iter)->m_eOption == TILE_WARP)//못가는 타일일때만
		{
			RECT rcSource = { long((*iter)->m_fX), long((*iter)->m_fY), long((*iter)->m_fX + (*iter)->m_fCX), long((*iter)->m_fY + (*iter)->m_fCY) };

			RECT rcDist;

			if(IntersectRect(&rcDist, &rcMonster, &rcSource))
			{
				float fMonsterX = float(rcMonster.left + ((rcMonster.right - rcMonster.left) / 2));
				float fMonsterY = float(rcMonster.bottom - ((rcMonster.bottom - rcMonster.top) / 2));
				float fSourceX = (*iter)->m_fX + ((*iter)->m_fCX / 2);
				float fSourceY = (*iter)->m_fY + ((*iter)->m_fCY / 2);

				float fDistX = abs(fMonsterX - fSourceX);
				float fDistY = abs(fMonsterY - fSourceY);

				float fOverlabX = ((rcMonster.right - rcMonster.left) / 2) + ((*iter)->m_fCX / 2) - fDistX;
				float fOverlabY = ((rcMonster.bottom - rcMonster.top) / 2) + ((*iter)->m_fCY / 2) - fDistY;

				if(fMonsterY < fSourceY)// 내가 위쪽
				{
					if(fOverlabX > fOverlabY)	//위쪽에서 부딪혔다.
					{
						m_tInfo.fX = m_pInfo->fX;
						m_tInfo.fY = m_pInfo->fY - fOverlabY;
						continue;
					}
				}
				else
				{
					if(fOverlabX > fOverlabY) //밑에서
					{
						m_tInfo.fX = m_pInfo->fX;
						m_tInfo.fY = m_pInfo->fY + fOverlabY;
						continue;
					}
				}
				if(fMonsterX > fSourceX) //오른쪽
				{
					m_tInfo.fX = m_pInfo->fX + fOverlabX;
					m_tInfo.fY = m_pInfo->fY;

				}
				else
				{
					m_tInfo.fX = m_pInfo->fX - fOverlabX;
					m_tInfo.fY = m_pInfo->fY;
				}
			}
		}
	}	
}