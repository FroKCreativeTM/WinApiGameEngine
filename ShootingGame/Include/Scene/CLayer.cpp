#include "CLayer.h"
#include "../Object/CObj.h"

void CLayer::Input(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(fDeltaTime);
	}
}

int CLayer::Update(float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(fDeltaTime);
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
		(*iter)->LateUpdate(fDeltaTime);
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
		(*iter)->Collision(fDeltaTime);
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	// 오브젝트 리스트를 반복해서 돌려야 처리가 가능하다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, fDeltaTime);
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
	m_pScene(nullptr)
{
}

CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}
