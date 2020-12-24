#include "CCollisionManager.h"
#include "../Object/CObj.h"
#include "CCollider.h"

DEFINITION_SINGLE(CCollisionManager);

CCollisionManager::CCollisionManager()
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::AddObject(CObj* pObj)
{
	if (pObj->CheckCollider())
	{
		// �浹ü�� �ִ� ������Ʈ�� ����� �´�.
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	// �� ���� �浹ü�� �־�� �浹�Ѵ�.
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}
	// ������Ʈ�� �浹 ó���� �Ѵ�.
	m_CollisionList.clear();
}
