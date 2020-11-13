#include "CSceneManager.h"
#include "CInGameScene.h"

DEFINITION_SINGLE(CSceneManager)

// m_pScene : ���� ���� ��Ÿ����.
CSceneManager::CSceneManager() : 
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
}

// ���� �����ڷν� �� �ϵ��� �ش�.
bool CSceneManager::Init()
{
	// �⺻ ����� ������ �ϳ� �����д�.
	CreateScene<CInGameScene>(SC_CURRENT);

	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	// ���� ���� �Է��� �޴´�.
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
