#pragma once
#include "obj.h"
#include "Item.h"

class CPlayer :	public CObj
{
private:
	ePLAYER_STATE	m_PlayerState;
	PlayerInfo		m_tPlayerInfo;
	bool			m_bSuperArmor;

private:
	Frame			m_Waiting;
	Frame			m_Waking;
	Frame			m_Dash;
	Frame			m_Jump; //8번
	Frame			m_DashAttck;
	Frame			m_Attck1;
	Frame			m_Attck2;
	Frame			m_Attck3;
	Frame			m_Hit;
	
private:
	DWORD			m_dwKey;
	DWORD			m_dwTime;
	DWORD			m_dwDashTime;
	DWORD			m_dwLeftDashTime;
	DWORD			m_dwJump;
	DWORD			m_dwShowInven;
	DWORD			m_dwMagicCursorTime;
	
private:
	int				m_iLeftDashCount;
	bool			m_bLeftDash;
	int				m_iDashCount;
	bool			m_bDash;
	bool			m_bJump;
	bool			m_bJumpMax;
	float			m_fTime;
	bool			m_bAttck1;
	bool			m_bAttck2;

private:
	//스킬 캐스팅 관련.
	ePLAYER_STATE   m_SkillCastingState;
	Frame			m_SkillVoidCasting;
	Frame			m_SkillThunderCasting;
	Frame			m_SkillMagicCursor;
	Frame			m_FrameCastingStart;
	Frame			m_FrameCastingEnd;
	bool			m_bSkillCasting;
	bool			m_bSkillCastingEnd;
	int				m_iSkillCastingCount;
	int				m_iThunderCount;
	bool			m_bThunder;
	INFO			m_tMagicCursor;
	bool			m_CastingStart;
	bool			m_CastingEnd;

	//각성기
	Frame			m_ElementalCasting;
	int				m_iElementalCount;
	DWORD			m_dwCreateTime;
	bool			m_ElementalEnd;

	bool			m_bRun; //초월의 룬
	int				m_iRunCount;

	
public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void SetPlayerState(ePLAYER_STATE _state) { m_PlayerState = _state; };

public:
	void SetPlayerInfo(PlayerInfo _PlayerInfo) { m_tPlayerInfo = _PlayerInfo; };
	PlayerInfo* GetPlayerInfo(void) { return &m_tPlayerInfo; };
	ePLAYER_STATE GetPlayerState(void) { return m_PlayerState; };
	Frame GetPlayerFrame(void);
	void CObjProgress(void);
	void SkillCasting(void);
	bool PtInCircle(float _MagicX, float _MagicY, float _MagicWidth, float _MagicHeight, float _CursorX, float _CursorY);
	bool CastingKeyCheck(void);
	bool GetSuperArmor(void) { return m_bSuperArmor; };

public:
	void KeyCheck(void);
	void SetScroll(void);
	void MoveFrame();
	RECT GetCollision(void);
	void Jump(void);
	void SetPlayerState(void);
	void SetRun(bool _bool) { m_bRun = _bool; }; 

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};