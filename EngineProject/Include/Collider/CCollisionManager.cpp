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
		// 충돌체가 있는 오브젝트만 여기로 온다.
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	// 두 개의 충돌체가 있어야 충돌한다.
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}
	// 오브젝트간 충돌 처리를 한다.
	m_CollisionList.clear();
}
