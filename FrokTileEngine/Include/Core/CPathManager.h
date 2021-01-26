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
	const char* FindPathMultiByte(const string& strKey);

private : 
	// wstring�� �����ڵ� string�̴�.
	unordered_map<string, wstring>	m_mapPath;
	// ��Ƽ����Ʈ �����
	char							m_strPath[MAX_PATH];

	DECLARE_SINGLE(CPathManager)
};

