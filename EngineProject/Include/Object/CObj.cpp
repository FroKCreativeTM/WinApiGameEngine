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
	// 텍스처가 있는 경우
	if (m_pTexture)
	{
		// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
		// 1. DC
		// 2~3. 어디에 출력할것인가
		// 4~5. 화면상 얼마나 크게 출력할래
		// 6. source의 DC
		// 7~8. 이미지의 어디부터 출력?
		// 9. 6번 인자에 복사
		BitBlt(hDC, m_tPos.x, m_tPos.y, 
			m_tSize.x, m_tSize.y,
			m_pTexture->GetDC(), 
			0, 0,
			SRCCOPY);
	}
}

void CObj::AddObj(CObj* pObj)
{
	// 인자로 들어온 물건들을 다 넣어준다.
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
	// 기존 텍스처를 날린다.
	SAFE_RELEASE(m_pTexture);

	m_pTexture = pTexture;

	// 텍스처가 있어서 오류가 안 난 경우에만
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



// m_nRef가 0이면 지워진다.
// 즉 이것을 만드는 시점에서 누군가는 이 오브젝트를 참조한다.
CObj::CObj() :
	m_pTexture(nullptr)
{
}

// 모든 정보를 다 복사하자.
CObj::CObj(const CObj& ref)
{
	*this = ref;

	// 만약 텍스처를 가지고 있다면 공유기 때문에
	// 레퍼런스 카운터만 증가시킨다.
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
	// 어떤 타입인지 알아서 찾아서 복사하도록
	// 짜피 static이라 CScene::
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

