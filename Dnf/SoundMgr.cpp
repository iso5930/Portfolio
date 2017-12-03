#include "StdAfx.h"
#include "SoundMgr.h"
#include "Func.h"



CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	m_iVersion = 0;

	Init();
}

CSoundMgr::~CSoundMgr(void)
{

}
void CSoundMgr::Init(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		cout << "����" << endl;
		return;
	}
}


void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd;

	long handle;
	int iResult = 1;

	handle = _findfirst("..\\Sound\\*.*", &fd);		//�ش��� ��� �о��.

	if (handle == -1)
	{
		return;
	}

	while(iResult != -1)
	{
		TCHAR szName[256];

		ZeroMemory(szName, sizeof(szName));	//��ũ�� �Լ�.

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
							fd.name, strlen(fd.name), szName, 256);
		//��Ƽ����Ʈ�� �����ڵ�� ����.

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);

		char szFullName[256];

		strcpy_s(szFullName, "..\\Sound\\");
		strcat_s(szFullName, fd.name);


		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
		{
			m_mapSound.insert( make_pair(pName, pSound) );
		}
		else
		{
			delete [] pName;
		}

		iResult = _findnext(handle, &fd);		//���Ž���� �Ѵ�.

	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);

	ErrorCheck(m_Result);

}

void CSoundMgr::PlayMonsterSkillSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pMonsterSkill);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlaySound(TCHAR* pSoundKey)
{

	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect);

	ErrorCheck(m_Result);

}

void CSoundMgr::PlayBGM(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pBGM);

	ErrorCheck(m_Result);
}
void CSoundMgr::PlayNPCSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pNPCSound);

	ErrorCheck(m_Result);
}
void CSoundMgr::PlayPlayerEffect(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pPlayerEffect);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlayEffect(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlaySkillSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pSkill);

	ErrorCheck(m_Result);
}

void CSoundMgr::PlayMonsterSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pMonster);

	ErrorCheck(m_Result);
}

void CSoundMgr::StopBGM(void)
{

}

void CSoundMgr::StopSoundAll(void)
{

}