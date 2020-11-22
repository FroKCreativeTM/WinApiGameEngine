#include "CPathManager.h"

DEFINITION_SINGLE(CPathManager)

CPathManager::CPathManager()
{

}

CPathManager::~CPathManager()
{

}

bool CPathManager::Init()
{
	// MAX_PATH : winapi의 상수(260)
	wchar_t strPath[MAX_PATH] = {};

	// 현재 실행되고 있는 경로를 뽑아온다.
	// 문제는 디버깅/릴리즈의 경로가 다르다.
	// 또한 개발 도중에 디렉토리 이름이 달라질 수 있다.
	// GetCurrentDirectory()

	// 이 함수는 실행파일의 이름까지 출력한다.(../test.exe)
	// 이것을 지워줘야...
	GetModuleFileName(NULL, strPath, MAX_PATH);

	for (int i = lstrlen(strPath) - 1; i >= 0; --i)
	{
		// 파일을 가르는 / 또는 \를 발견한 경우
		if (strPath[i] == '/' ||
			strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, 
				sizeof(wchar_t) * (MAX_PATH - (i + 1)));
			break; 
		}
	}

	// 이제 루트 패스로 저장하자.
	m_mapPath.insert(make_pair(ROOT_PATH, strPath));

	// 텍스처 경로 설정
	if (!CreatePath(TEXTURE_PATH, L"Texture\\"))
	{
		return false;
	}

	return true;
}

// 디폴트 패스(ex. 텍스처 패스까지의 경로)를 생성
// 1. 키값
// 2. 우리가 만들 path
// 3. 기본 패스 경로
bool CPathManager::CreatePath(const string& strKey, 
	const wchar_t* pPath, const string& strBaseKey)
{
	const wchar_t* pBasePath = FindPath(strBaseKey);

	wstring strPath;

	// 있을 경우에만!
	if (pBasePath)
	{
		strPath = pBasePath;
	}

	strPath += pPath;

	// 맵에 넣어준다.
	m_mapPath.insert(make_pair(strKey, strPath));

	return true;
}

const wchar_t* CPathManager::FindPath(const string& strKey)
{
	unordered_map<string, wstring>::iterator iter = 
		m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
	{
		return nullptr;
	}

	return iter->second.c_str();
}
