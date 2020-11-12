#pragma once

#include "../Game.h"

// 레이어는 두가지의 정보를 가지고 있게 한다.
// 첫번째는 태그이다. 레이어는 몇 천개씩 가지지 않기 때문에
// 선형 탐색을 하더라도 크게 무리가 없다.
// 즉 태그를 이용해서 찾을 수 있도록 만들 것
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

// 씬 외에는 생성하지 못하도록 하기 위해서 private로 생성
private : 
	CLayer();

public :
	// Safe_Delete_VecList를 위해서
	~CLayer();

private : 
	class CScene* m_pScene;	// 이 레이어를 가진 장면 정보를 가진다.
	string		m_strTag;
	int			m_nZOrder;	// z축의 순서를 담당한다. (출력 우선순위)
							// 이펙트 레이어들은 위에 존재하는 등
							// UI레이어는 가장 뒤에
							// 이것을 결정하는 것이 바로 이 ZOrder이다.
							// 장면이 레이어들을 들고 있을텐데
							// 이것을 정렬하게 할 것이다.
};

