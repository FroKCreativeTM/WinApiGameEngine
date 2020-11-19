#include "CSceneManager.h"
#include "CInGameScene.h"

DEFINITION_SINGLE(CSceneManager)

// m_pScene : 현재 씬을 나타낸다.
CSceneManager::CSceneManager() : 
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
}

// 서브 관리자로써 할 일들을 준다.
bool CSceneManager::Init()
{
	// 기본 장면은 무조건 하나 만들어둔다.
	CreateScene<CInGameScene>(SC_CURRENT);

	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	// 현재 씬의 입력을 받는다.
	m_pScene->Input(fDeltaTime);
}

int CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return 0;
}

int CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return 0;
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}
