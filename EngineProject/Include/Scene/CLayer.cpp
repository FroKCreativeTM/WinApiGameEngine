#include "CLayer.h"
#include "../Object/CObj.h"

void CLayer::Input(float fDeltaTime)
{
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		// ��Ȱ��ȭ��
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Input(fDeltaTime);

		// ���� �� ���̾ �׾��ٸ�
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{// ��Ȱ��ȭ��
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fDeltaTime);

		// ���� �� ���̾ �׾��ٸ�
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// ��Ȱ��ȭ��
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		// ���� �� ���̾ �׾��ٸ�
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// ��Ȱ��ȭ��
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(fDeltaTime);

		// ���� �� ���̾ �׾��ٸ�
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
	// ������Ʈ ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// ��Ȱ��ȭ��
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		// ���� �� ���̾ �׾��ٸ�
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
	pObj->SetScene(m_pScene);	// ���̾ �Ҽӵ� ���
	pObj->SetLayer(this);		// �� ���̾ ����
	pObj->AddRef();				// ���۷��� ī���� ����

	// ������Ʈ ����Ʈ�� �߰��Ѵ�.
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
