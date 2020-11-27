#pragma once

#include "../Game.h"

// 경로 관련을 지원하는 클래스입니다.
class CPathManager
{
public : 
	bool Init();
	bool CreatePath(const string& strKey,
		const wchar_t* pPath,
		const string& strBaseKey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);

private : 
	// wstring는 유니코드 string이다.
	unordered_map<string, wstring> m_mapPath;

	DECLARE_SINGLE(CPathManager)
};

