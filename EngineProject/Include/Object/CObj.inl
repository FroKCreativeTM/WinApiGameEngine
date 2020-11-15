#pragma once

#include "../Scene/CLayer.h"

template <typename T>
static T* CObj::CreateObj(const string& strTag,
	class CLayer* pLayer)
{
	T* pObj = new T;

	if (!pObj->Init())
	{
		SAFE_RELEASE(pObj);
		return nullptr;
	}

	if (pLayer)
	{
		pLayer->AddObj(pObj);
	}

	return pObj;
}