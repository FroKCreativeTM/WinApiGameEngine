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
};

