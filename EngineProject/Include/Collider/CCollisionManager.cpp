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

	/* ���� ������ ���鼭 ��� �浹ü�� ó���� ����� ���̴�. */
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

	// ������Ʈ�� �浹 ó���� �Ѵ�.
	m_CollisionList.clear();
}

// �ΰ��� ������Ʈ�� �Ѱ��༭ �浹ó���� �Ѵ�.
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

				// �̹� ��Ʈ����Ʈ�� ������� ���� ��
				// dest�� ��Ʈ ����Ʈ�� �����Ѵ�.
				(*iterDst)->SetHitPoint((*iterSrc)->GetHitPoint());

				// �浹��Ͽ��� ������ �浹�� ���� ���ٸ� ó�� �� �浹�Ǿ��ٴ� ���̴�.
				if (!(*iterSrc)->CheckCollisionList(*iterDst))
				{
					// ���� ������ �浹 ������� �߰��Ѵ�.
					(*iterSrc)->AddCollider(*iterDst);
					(*iterDst)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDst, fDeltaTime);
					(*iterDst)->CallFunction(CS_ENTER, *iterSrc, fDeltaTime);
				}
				// ������ �̹� �浹�� ���� �ִٸ� ��� �浹�̴�.
				else
				{
					(*iterSrc)->CallFunction(CS_STAY, *iterDst, fDeltaTime);
					(*iterDst)->CallFunction(CS_STAY, *iterSrc, fDeltaTime);
				}
			}
			// ���� �� �浹 ���¿��� ������ ���
			// �� ���� �浹�� �� �� ���¿��� ������ �浹�� �ǰ� �־��ٸ�
			// ���� �� �浹���¿��� �������ٴ� �ǹ�.
			else if((*iterSrc)->CheckCollisionList(*iterDst))
			{
				// ���� �浹�� �ȵǹǷ� �浹 ��Ͽ��� �����ش�.
				(*iterSrc)->EraseCollsionList(*iterDst);
				(*iterDst)->EraseCollsionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDst, fDeltaTime);
				(*iterDst)->CallFunction(CS_LEAVE, *iterSrc, fDeltaTime);
			}
		}
	}

	return bCollision;
}
