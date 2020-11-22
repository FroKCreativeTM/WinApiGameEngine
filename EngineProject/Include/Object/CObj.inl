#pragma once

#include "../Scene/CLayer.h"
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
inline T* CObj::CreatePrototype(const string& strTag)
{
	T* pObj = new T;

	pObj->SetTag(strTag);

	if (!pObj->Init())
	{
		SAFE_RELEASE(pObj);
		return nullptr;
	}

	pObj->AddRef();
	m_mapPrototype.insert(make_pair(strTag, pObj));

	return pObj;
}
