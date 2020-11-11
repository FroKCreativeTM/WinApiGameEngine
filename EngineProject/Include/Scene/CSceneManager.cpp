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
