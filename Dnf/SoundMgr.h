#pragma once

class CSoundMgr
{
private:
	static CSoundMgr* m_pInstance;

public:
	static CSoundMgr* GetInstance(void)
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CSoundMgr;
		}
		return m_pInstance;
	}

	static void DestroyInstance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	//Fmod 인터페이스
private:
	FMOD_SYSTEM*	m_pSystem;			//fmod 시스템 포인터
	FMOD_CHANNEL*	m_pEffect;	
	FMOD_CHANNEL*	m_pBGM;
	FMOD_CHANNEL*	m_pSkill;
	FMOD_CHANNEL*	m_pMonster;
	FMOD_CHANNEL*	m_pNPCSound;
	FMOD_CHANNEL*	m_pPlayerEffect;
	FMOD_CHANNEL*	m_pMonsterSkill;



	FMOD_RESULT		m_Result;		//실행잘되는지 확인하는 변수.

	unsigned int m_iVersion;
	
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;		//사운드 관리(map)

public:
	void Init(void);
	void LoadSoundFile(void);
	void PlaySound(TCHAR* pSoundKey);
	void PlayBGM(TCHAR* pSoundKey);
	void PlaySkillSound(TCHAR* pSoundKey);
	void PlayMonsterSound(TCHAR* pSoundKey);
	void PlayNPCSound(TCHAR* pSoundKey);
	void StopBGM(void);
	void StopSoundAll(void);

	void PlayEffect(TCHAR* pSoundKey);
	void PlayPlayerEffect(TCHAR* pSoundKey);
	void PlayMonsterSkillSound(TCHAR* pSoundKey);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}

private:
	void ErrorCheck(FMOD_RESULT _result);

private:
	CSoundMgr(void);

public:
	~CSoundMgr(void);
};