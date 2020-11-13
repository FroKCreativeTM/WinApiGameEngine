#include "CLayer.h"
#include "../Object/CObj.h"

void CLayer::Input(float fDeltaTime)
{
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(fDeltaTime);
	}
}

int CLayer::Update(float fDeltaTime)
{
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(fDeltaTime);
	}
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, fDeltaTime);
	}
}

void CLayer::AddObj(CObj* pObj)
{
	pObj->SetScene(m_pScene);	// ���̾ �Ҽӵ� ���
	pObj->SetLayer(this);		// �� ���̾ ����
	pObj->AddRef();				// ���۷��� ī���� ����

	// ������Ʈ ����Ʈ�� �߰��Ѵ�.
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
