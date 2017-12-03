#ifndef _FACTORY_H
#define _FACTORY_H
#include "Skill.h"
#include "InterFace.h"

template<typename T>
class CFactory abstract		//추상 클래스로 만들어준다.
{
public:
	static CObj*	CreateObj(void)
	{
		CObj* pObj = new T;
		pObj->Init();
		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->SetPos(_fX, _fY);
		pObj->Init();
		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, int _iDamage, bool _Cri)
	{
		CObj* pObj = new T;
		pObj->SetPos(_fX, _fY);
		((CInterFace*)pObj)->SetDamage(_iDamage);
		((CInterFace*)pObj)->SetCri(_Cri);
		pObj->Init();

		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, eSKILL_TYPE _type, float _vec, INFO _tTarget)
	{
		CObj* pObj = new T;
		pObj->SetPos(_fX, _fY);
		((CSkill*)pObj)->SetSkillType(_type);
		((CSkill*)pObj)->SetVec(_vec);
		((CSkill*)pObj)->SetPlayerInfo(_tTarget);
		pObj->Init();
		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, eSKILL_TYPE _type, float _vecX, float _vecY, INFO _tTarget)
	{
		CObj* pObj = new T;
		pObj->SetPos(_fX, _fY);
		((CSkill*)pObj)->SetSkillType(_type);
		((CSkill*)pObj)->SetVec(_vecX, _vecY);
		((CSkill*)pObj)->SetPlayerInfo(_tTarget);
		pObj->Init();
		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, eSKILL_TYPE _type, float _vec, eELEMENT_TYPE _Type, INFO _tTarget, bool _ELEMENT_END = false)
	{
		CObj* pObj = new T;
		pObj->SetPos(_fX, _fY);
		((CSkill*)pObj)->SetSkillType(_type);
		((CSkill*)pObj)->SetVec(_vec);
		((CSkill*)pObj)->SetType(_Type);
		((CSkill*)pObj)->SetEnd(_ELEMENT_END);
		((CSkill*)pObj)->SetPlayerInfo(_tTarget);
		pObj->Init();
		return pObj;
	}
};


#endif //_FACTORY_H