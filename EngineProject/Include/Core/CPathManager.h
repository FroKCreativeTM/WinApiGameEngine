#pragma once

#include "../Game.h"

// ��� ������ �����ϴ� Ŭ�����Դϴ�.
class CPathManager
{
public : 
	bool Init();
	bool CreatePath(const string& strKey,
		const wchar_t* pPath,
		const string& strBaseKey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);

private : 
	// wstring�� �����ڵ� string�̴�.
	unordered_map<string, wstring> m_mapPath;

	DECLARE_SINGLE(CPathManager)
};

