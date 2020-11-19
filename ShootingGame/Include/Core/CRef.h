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

protected : 
	CRef();
	virtual ~CRef();

protected :
	// 이 오브젝트를 얼마나 참조하냐를 나타내는 지표
	int			m_nRef;
};

