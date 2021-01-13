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

	/* 이중 루프를 돌면서 모든 충돌체간 처리를 담당할 것이다. */
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		list<CObj*>::iterator innerIter = iter;
		++innerIter;
		list<CObj*>::iterator innerIterEnd = m_CollisionList.end();

		for (; innerIter != innerIterEnd; ++innerIter)
		{
			Collision(*iter, *innerIter, fDeltaTime);
		}
	}

	// 오브젝트간 충돌 처리를 한다.
	m_CollisionList.clear();
}

// 두개의 오브젝트를 넘겨줘서 충돌처리를 한다.
bool CCollisionManager::Collision(CObj* pSrc, CObj* pDst, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDstcList = pDst->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDst;
	list<CCollider*>::const_iterator iterDstEnd = pDstcList->end();
	
	bool bCollision = false;

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
	{
		for (iterDst = pDstcList->begin(); iterDst != iterDstEnd; ++iterDst)
		{
			if ((*iterSrc)->Collision(*iterDst))
			{
				bCollision = true;

				// 이미 히트포인트는 만들어져 있을 것
				// dest의 히트 포인트를 세팅한다.
				(*iterDst)->SetHitPoint((*iterSrc)->GetHitPoint());

				// 충돌목록에서 이전에 충돌된 적이 없다면 처음 막 충돌되었다는 뜻이다.
				if (!(*iterSrc)->CheckCollisionList(*iterDst))
				{
					// 서로 상대방을 충돌 목록으로 추가한다.
					(*iterSrc)->AddCollider(*iterDst);
					(*iterDst)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDst, fDeltaTime);
					(*iterDst)->CallFunction(CS_ENTER, *iterSrc, fDeltaTime);
				}
				// 이전에 이미 충돌된 적이 있다면 계속 충돌이다.
				else
				{
					(*iterSrc)->CallFunction(CS_STAY, *iterDst, fDeltaTime);
					(*iterDst)->CallFunction(CS_STAY, *iterSrc, fDeltaTime);
				}
			}
			// 이제 막 충돌 상태에서 떨어진 경우
			// 즉 현재 충돌이 안 된 상태에서 이전에 충돌이 되고 있었다면
			// 이제 막 충돌상태에서 떨어졌다는 의미.
			else if((*iterSrc)->CheckCollisionList(*iterDst))
			{
				// 서로 충돌이 안되므로 충돌 목록에서 지워준다.
				(*iterSrc)->EraseCollsionList(*iterDst);
				(*iterDst)->EraseCollsionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDst, fDeltaTime);
				(*iterDst)->CallFunction(CS_LEAVE, *iterSrc, fDeltaTime);
			}
		}
	}

	return bCollision;
}
