#include "CLayer.h"
#include "../Object/CObj.h"

void CLayer::Input(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		// 비활성화시
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Input(fDeltaTime);

		// 만약 이 레이어가 죽었다면
		if (!(*iter)->GetLife())
		{
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			++iter;
		}
	}
}

int CLayer::Update(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{// 비활성화시
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fDeltaTime);

		// 만약 이 레이어가 죽었다면
		if (!(*iter)->GetLife())
		{
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			++iter;
		}
	}

	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// 비활성화시
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		// 만약 이 레이어가 죽었다면
		if (!(*iter)->GetLife())
		{
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			++iter;
		}
	}

	return 0;
}

void CLayer::Collision(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// 비활성화시
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(fDeltaTime);

		// 만약 이 레이어가 죽었다면
		if (!(*iter)->GetLife())
		{
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// 비활성화시
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		// 만약 이 레이어가 죽었다면
		if (!(*iter)->GetLife())
		{
			CObj::EraseObj(*iter);
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::AddObj(CObj* pObj)
{
	pObj->SetScene(m_pScene);	// 레이어가 소속된 장면
	pObj->SetLayer(this);		// 이 레이어를 전달
	pObj->AddRef();				// 레퍼런스 카운터 증가

	// 오브젝트 리스트에 추가한다.
	m_ObjList.push_back(pObj);
}

CLayer::CLayer() :
	m_strTag(""),
	m_nZOrder(0),
	m_pScene(nullptr),
	m_bEnable(true),
	m_bLife(true)
{
}

CLayer::~CLayer()
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		CObj::EraseObj(*iter);
		SAFE_RELEASE((*iter));
	}

	m_ObjList.clear();
}
