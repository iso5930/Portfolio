#ifndef _TYPE_DEF_
#define _TYPE_DEF_

class CObj;

typedef list<CObj*> OBJ_LIST;
typedef list<CObj*>::iterator OBJ_ITER;

class CItem;

typedef vector<CItem*> ITEM_VECTOR;
typedef vector<CItem*>::iterator ITEM_ITER;

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
	float fJumpY;

	tagInfo(void) { };

	tagInfo(float _fX, float _fY, float _fCX, float _fCY) 
		:fX(_fX),fY(_fY),fCX(_fCX),fCY(_fCY)
	{

	};

}INFO;

typedef struct tagItemInfo
{
	TCHAR szName[50]; //아이템 이름.
	int iAtt;	//무기 공격력
	int iInt;	//지능 상승량
	int iCount; //아이템 갯수
	int iHp; //hp 회복량
	int iMp;	//mp회복량

	tagItemInfo() {}
	tagItemInfo(PTCHAR _pName, int _Att, int _Int, int _Count = 1, int _Hp = 0, int _Mp = 0)
		:iAtt(_Att), iInt(_Int), iHp(_Hp), iMp(_Mp), iCount(_Count)
	{
		lstrcpy(szName,_pName);
	}
}ItemInfo;

typedef struct tagPlayerInfo
{
	TCHAR szName[50]; //닉네임
	TCHAR szJob[50]; //직업이름
	int iHp;
	int iMaxHp;
	int iMp;
	int iMaxMp;
	int iAtt; //공격력
	int iDef; //방어력
	int iInt; //지능

	float fMoveSpeed; //이동속도
	float fAttSpeed; //공격속도
	float fCastingSpeed; //캐스팅속도
	
}PlayerInfo;

typedef struct tagMonsterInfo
{
	TCHAR szName[50];
	int iHp;
	int iMaxHp;
	int iAtt;
	int iDef;

	float fMoveSpeed; //이동속도

}MonsterInfo;

typedef struct tagFrame
{
	int iStartFrame; //시작
	int iRenderFrame; //현재 진행
	int iEndFrame;	//끝 프레임
	DWORD dwFrameTime;
	
	tagFrame() {};
	tagFrame(int _Start, int _End, DWORD _Frame)
	{
		iStartFrame = _Start;
		iRenderFrame = _Start;
		iEndFrame = _End;
		dwFrameTime = _Frame;
	};
}Frame;

typedef struct tagTile
{
	float m_fX;
	float m_fY;
	float m_fCX;
	float m_fCY;
	eTILE_TYPE	m_eOption;			//충돌인지 아닌지..(속성)
	int	m_iImage;			//어떤 이미지를 출력할것인지.

	tagTile(void){}

	tagTile(float _fX, float _fY, float _fCX, float _fCY, eTILE_TYPE _eOption, int _iImage)
		:m_fX(_fX)
		,m_fY(_fY)
		,m_fCX(_fCX)
		,m_fCY(_fCY)
		,m_eOption(_eOption)
		,m_iImage(_iImage)
	{}
}TILE;

#endif //_TYPE_DEF_