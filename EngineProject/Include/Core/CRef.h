#pragma once

#include "../Game.h"

/* �پ��� ����� ���۷��� ī��Ʈ�� ���� Ŭ���� */
class CRef
{
public : 
	void AddRef() { ++m_nRef; }
	int Release()
	{
		--m_nRef;

		if (m_nRef == 0)
		{
			delete this;
			return 0;
		}
		return m_nRef;
	}

public : 
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

protected : 
	CRef();
	virtual ~CRef();

protected :
	// �� ������Ʈ�� �󸶳� �����ϳĸ� ��Ÿ���� ��ǥ
	int			m_nRef;
	bool		m_bEnable;	// ��ü Ȱ��ȭ(��ü�� ������, ���̳� �� ���̴°�)
	bool		m_bLife;	// �츮�°� ���̴°�.
};

