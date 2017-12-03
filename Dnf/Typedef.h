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
	TCHAR szName[50]; //������ �̸�.
	int iAtt;	//���� ���ݷ�
	int iInt;	//���� ��·�
	int iCount; //������ ����
	int iHp; //hp ȸ����
	int iMp;	//mpȸ����

	tagItemInfo() {}
	tagItemInfo(PTCHAR _pName, int _Att, int _Int, int _Count = 1, int _Hp = 0, int _Mp = 0)
		:iAtt(_Att), iInt(_Int), iHp(_Hp), iMp(_Mp), iCount(_Count)
	{
		lstrcpy(szName,_pName);
	}
}ItemInfo;

typedef struct tagPlayerInfo
{
	TCHAR szName[50]; //�г���
	TCHAR szJob[50]; //�����̸�
	int iHp;
	int iMaxHp;
	int iMp;
	int iMaxMp;
	int iAtt; //���ݷ�
	int iDef; //����
	int iInt; //����

	float fMoveSpeed; //�̵��ӵ�
	float fAttSpeed; //���ݼӵ�
	float fCastingSpeed; //ĳ���üӵ�
	
}PlayerInfo;

typedef struct tagMonsterInfo
{
	TCHAR szName[50];
	int iHp;
	int iMaxHp;
	int iAtt;
	int iDef;

	float fMoveSpeed; //�̵��ӵ�

}MonsterInfo;

typedef struct tagFrame
{
	int iStartFrame; //����
	int iRenderFrame; //���� ����
	int iEndFrame;	//�� ������
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
	eTILE_TYPE	m_eOption;			//�浹���� �ƴ���..(�Ӽ�)
	int	m_iImage;			//� �̹����� ����Ұ�����.

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