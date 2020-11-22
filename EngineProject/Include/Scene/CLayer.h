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

public : 
	/* 코어부터 지금 돌아가는 씬의 레이어들까지 내려왔다. */
	/* 게임 요소를 위한 메소드 */
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

	// 오브젝트는 삭제가 많이 생기는 그런 물건이다.
	// 그렇기 때문에 중간 삽입,삭제가 굉장히 많이 발생할 것이다.
	// 그런 부분은 vector보다는 list가 빠르다.
	list<class CObj*> m_ObjList;
	bool		m_bEnable;	// 레이어 활성화
	bool		m_bLife;	// 살리는가 죽이는가.
};

