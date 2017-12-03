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

	//��ũƽ �ǽ�Ʈ
	bool m_bDeath;
	int m_iIndex;

	//����Ʈ�� ����
	eELEMENT_TYPE m_ElementType;
	bool m_bEnd;

	//�ʿ��� ��
	DWORD m_dwClearTime; //Ȱ��ȭ �ð�
	DWORD m_dwRunTime; // ���� ���� �ð� 
	bool m_bCreate; //���� �����ÿ��� Ȱ��
	bool m_bRun; //���� Ȱ��ȭ �ɶ� Ŭ���� Ÿ�ӵ� �ʱ�ȭ�� �Ǹ鼭 �ٽ� false�� �ٲ�� end ������ render�� �ٱ�����

	//�ҷ��� ������
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