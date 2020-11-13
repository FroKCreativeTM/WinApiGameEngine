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

protected : 
	CRef();
	virtual ~CRef();

protected :
	// �� ������Ʈ�� �󸶳� �����ϳĸ� ��Ÿ���� ��ǥ
	int			m_nRef;
};

