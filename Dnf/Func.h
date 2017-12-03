#pragma once

class CStringCmp
{
private:
	const TCHAR*		m_pName;

public:
	explicit CStringCmp(const TCHAR* pKey)
		:m_pName(pKey){}

public:
	template<typename T>
	bool operator () (T data)
	{
		return (!lstrcmp(data.first, m_pName));
	}
};