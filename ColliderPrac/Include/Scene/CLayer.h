#pragma once

#include "../Game.h"

// ���̾�� �ΰ����� ������ ������ �ְ� �Ѵ�.
// ù��°�� �±��̴�. ���̾�� �� õ���� ������ �ʱ� ������
// ���� Ž���� �ϴ��� ũ�� ������ ����.
// �� �±׸� �̿��ؼ� ã�� �� �ֵ��� ���� ��
class CLayer
{
public : 
	void SetTag(const string& str)
	{
		this->m_strTag = str;
	}

	void SetZOrder(int nZOrder)
	{
		this->m_nZOrder = nZOrder;
	}

	void SetScene(class CScene* pScene)
	{
		this->m_pScene = pScene;
	}

	int GetZOrder() const
	{
		return m_nZOrder;
	}

	string GetTag() const
	{
		return m_strTag;
	}

	class CScene* GetScene() const 
	{
		return this->m_pScene;
	}

public : 
	/* �ھ���� ���� ���ư��� ���� ���̾����� �����Դ�. */
	/* ���� ��Ҹ� ���� �޼ҵ� */
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

public : 
	void AddObj(class CObj* pObj);

public:
	void SetEnable(bool bEnable)
	{
		this->m_bEnable = bEnable;
	}

	void SetLife(bool bLife)
	{
		this->m_bLife = bLife;
	}

	bool GetLife() const
	{
		return m_bLife;
	}

	bool GetEnable() const
	{
		return m_bEnable;
	}

private : 
	friend class CScene;

// �� �ܿ��� �������� ���ϵ��� �ϱ� ���ؼ� private�� ����
private : 
	CLayer();

public :
	// Safe_Delete_VecList�� ���ؼ�
	~CLayer();

private : 
	class CScene* m_pScene;	// �� ���̾ ���� ��� ������ ������.
	string		m_strTag;
	int			m_nZOrder;	// z���� ������ ����Ѵ�. (��� �켱����)
							// ����Ʈ ���̾���� ���� �����ϴ� ��
							// UI���̾�� ���� �ڿ�
							// �̰��� �����ϴ� ���� �ٷ� �� ZOrder�̴�.
							// ����� ���̾���� ��� �����ٵ�
							// �̰��� �����ϰ� �� ���̴�.

	// ������Ʈ�� ������ ���� ����� �׷� �����̴�.
	// �׷��� ������ �߰� ����,������ ������ ���� �߻��� ���̴�.
	// �׷� �κ��� vector���ٴ� list�� ������.
	list<class CObj*> m_ObjList;
	bool		m_bEnable;	// ���̾� Ȱ��ȭ
	bool		m_bLife;	// �츮�°� ���̴°�.
};

