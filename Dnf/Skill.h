#pragma once
#include "obj.h"

class CSkill :	public CObj
{
private:
	Frame m_SkillFrame;
	int m_iCount;
	eSKILL_TYPE m_Skill_Type;
	DWORD m_dwTime;
	float m_vecX;
	float m_vecY;
	bool m_bSkillTime;
	DWORD m_HitTime;
	INFO m_PlayerInfo;

	//아크틱 피스트
	bool m_bDeath;
	int m_iIndex;

	//에스트럴 스톰
	eELEMENT_TYPE m_ElementType;
	bool m_bEnd;

	//초월의 룬
	DWORD m_dwClearTime; //활성화 시간
	DWORD m_dwRunTime; // 버프 유지 시간 
	bool m_bCreate; //최초 생성시에만 활성
	bool m_bRun; //룬이 활성화 될때 클리어 타임도 초기화가 되면서 다시 false로 바뀌고 end 지점과 render을 바구어줌

	//할로윈 버스터
	DWORD m_dwFireTime;

	bool m_bStart;

public:
	eSKILL_TYPE GetSkillType(void) { return m_Skill_Type; };
	bool GetSkillTime(void) { return m_bSkillTime; }
	void SetIndex(int _index){ m_iIndex = _index; };

	void SetSkillType(eSKILL_TYPE _SkillType) { m_Skill_Type = _SkillType; };
	void SetEnd(bool _end) { m_bEnd = _end; };

	void SetRun(bool _Run) { m_bRun = _Run; };
	void SetDwRunTime(DWORD _dwTime) { m_dwRunTime = _dwTime; };
	void SetDwRunClearTime(DWORD _dwTime) { m_dwClearTime = _dwTime; };

public:
	void SetPlayerInfo(INFO _tInfo) { m_PlayerInfo = _tInfo; };

public:
	void FrameMove(void);
	void SetVec(float _vec, float _vecY = 0) { m_vecX = _vec; m_vecY = _vecY; };
	void SetType(eELEMENT_TYPE _ElementType) { m_ElementType = _ElementType; };
	bool PtInCircle(float _CircleX, float _CircleY, float _CircleWidth, float _CircleHeight, float _CursorX, float _CursorY);

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CSkill(void);
	virtual ~CSkill(void);
};