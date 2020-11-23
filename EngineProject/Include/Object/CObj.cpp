#include "CObj.h"
#include "../Scene/CLayer.h"
#include "../Scene/CSceneManager.h"
#include "../Scene/CScene.h"
#include "../Resources/CResourceManager.h"
#include "../Resources/CTexture.h"

// static
list<CObj*> CObj::m_ObjList;

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
	// �ؽ�ó�� �ִ� ���
	if (m_pTexture)
	{
		// ȭ�鿡 DC�� ���ִ� ������ ������ִ� �Լ��̴�.
		// 1. DC
		// 2~3. ��� ����Ұ��ΰ�
		// 4~5. ȭ��� �󸶳� ũ�� ����ҷ�
		// 6. source�� DC
		// 7~8. �̹����� ������ ���?
		// 9. 6�� ���ڿ� ����
		BitBlt(hDC, m_tPos.x, m_tPos.y, 
			m_tSize.x, m_tSize.y,
			m_pTexture->GetDC(), 
			0, 0,
			SRCCOPY);
	}
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

void CObj::SetTexture(CTexture* pTexture)
{
	// ���� �ؽ�ó�� ������.
	SAFE_RELEASE(m_pTexture);

	m_pTexture = pTexture;

	// �ؽ�ó�� �־ ������ �� �� ��쿡��
	if (pTexture)
	{
		m_pTexture->AddRef();
	}
}

void CObj::SetTexture(const string& strKey, 
	const wchar_t* pFileName, 
	const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourceManager)->
		LoadTexture(strKey, pFileName, strPathKey);
}



// m_nRef�� 0�̸� ��������.
// �� �̰��� ����� �������� �������� �� ������Ʈ�� �����Ѵ�.
CObj::CObj() :
	m_pTexture(nullptr)
{
}

// ��� ������ �� ��������.
CObj::CObj(const CObj& ref)
{
	*this = ref;

	// ���� �ؽ�ó�� ������ �ִٸ� ������ ������
	// ���۷��� ī���͸� ������Ų��.
	if (m_pTexture)
	{
		m_pTexture->AddRef();
	}
}

CObj::~CObj()
{
	SAFE_RELEASE(m_pTexture);
}

CObj* CObj::CreateCloneObj(const string& strProtoKey,
	const string& strTag,
	CLayer* pLayer)
{
	// � Ÿ������ �˾Ƽ� ã�Ƽ� �����ϵ���
	// ¥�� static�̶� CScene::
	CObj* pPrototype = CScene::FindPrototype(strProtoKey);

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

