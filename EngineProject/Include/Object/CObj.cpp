#include "../Scene/CLayer.h"
#include "../Scene/CScene.h"
#include "CObj.h"

// static
list<CObj*> CObj::m_ObjList;
unordered_map<string, CObj*> CObj::m_mapPrototype;

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
}

void CObj::AddObj(CObj* pObj)
{
	// ���ڷ� ���� ���ǵ��� �� �־��ش�.
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObj* CObj::FindObj(const string& strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}
	return nullptr;
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

void CObj::EraseObj(CObj* pObj)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pObj)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string& strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::ErasePrototype()
{
	// ��ü ������Ÿ���� ������ ������.
	Safe_Release_Map(m_mapPrototype);
}

void CObj::ErasePrototype(const string& strTag)
{
	unordered_map<string, CObj*>::iterator iter 
		= m_mapPrototype.find(strTag);

	if (!iter->second)
	{
		return;
	}

	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);
}

// m_nRef�� 0�̸� ��������.
// �� �̰��� ����� �������� �������� �� ������Ʈ�� �����Ѵ�.
CObj::CObj()
{
}

// ��� ������ �� ��������.
CObj::CObj(const CObj& ref) 
{
	*this = ref;
}

CObj::~CObj()
{
}

CObj* CObj::CreateCloneObj(const string& strProtoKey,
	const string& strTag,
	CLayer* pLayer = nullptr)
{
	// � Ÿ������ �˾Ƽ� ã�Ƽ� �����ϵ���
	CObj* pPrototype = FindPrototype(strProtoKey);

	if (!pPrototype)
	{
		return nullptr;
	}

	CObj* pObj = pPrototype->Clone();
	pObj->SetTag(strTag);

	if (pLayer)
	{
		pLayer->AddObj(pObj);
	}

	AddObj(pObj);

	return pObj;
}

CObj* CObj::FindPrototype(const string& strTag)
{
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype.find(strTag);

	if (iter == m_mapPrototype.end())
	{
		return nullptr;
	}

	return iter->second;
}
