#pragma once

#include "../Scene/CLayer.h"
#include "../Collider/CCollider.h"
#include "CObj.h"

template <typename T>
static T* CObj::CreateObj(const string& strTag,
	class CLayer* pLayer)
{
	T* pObj = new T;

	pObj->SetTag(strTag);

	if (!pObj->Init())
	{
		SAFE_RELEASE(pObj);
		return nullptr;
	}

	if (pLayer)
	{
		pLayer->AddObj(pObj);
	}

	AddObj(pObj);

	return pObj;
}

template<typename T>
inline void CObj::AddCollisionFunction(
	const string& strTag, COLLISION_STATE eState, T* pObj, void(T::* pFunc)(CCollider*, CCollider*, float))
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddCollisionFunction(eState, pObj, pFunc);
			break;
		}

	}
}

