#pragma once

#include "../Game.h"

/* 다양한 방식의 레퍼런스 카운트를 위한 클래스 */
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

	void Die()
	{
		this->m_bLife = false;
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
	// 이 오브젝트를 얼마나 참조하냐를 나타내는 지표
	int			m_nRef;
	bool		m_bEnable;	// 객체 활성화(객체는 있지만, 보이냐 안 보이는가)
	bool		m_bLife;	// 살리는가 죽이는가.
};

