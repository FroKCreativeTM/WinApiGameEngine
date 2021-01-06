#pragma once

#include "../Core/CRef.h"

// �浹�� ���õ� �⺻ Ŭ�����Դϴ�.
class CCollider : 
	public CRef	
{
public : 
	/* ���� ��Ҹ� ���� �޼ҵ� */
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDst);
	virtual void Render(HDC hDC, float fDeltaTime);
	// 
	virtual CCollider* Clone() = 0;

protected :
	bool CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dst);
	bool CollisionRectToSphere(const RECTANGLE& src, const SPHERE& dst);
	bool CollisionSphereToSphere(const SPHERE& src, const SPHERE& dst);

protected:
	CCollider();
	CCollider(const CCollider& col);
	virtual ~CCollider() = 0;

public : 
	COLLIDER_TYPE GetColliderType() const
	{
		return m_eColType;
	}


	class CObj* GetObj() const
	{
		return m_pObj;
	}

	void SetObj(class CObj* obj)
	{
		m_pObj = obj;
	}

public : 
	void AddCollider(CCollider* pCollider)
	{
		m_CollisionList.push_back(pCollider);
	}

	bool CheckCollisionList(CCollider* pCollider)
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider)
			{
				return true;
			}
		}

		return false;
	}

	void EraseCollsionList(CCollider* pCollider)
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider)
			{
				m_CollisionList.erase(iter);
				break;
			}
		}
	}

	void AddCollisionFunction(COLLISION_STATE eState,
		void(*pFunc)(CCollider*, CCollider*, float))
	{
		function<void(CCollider*, CCollider*, float)> func;

		func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

		m_FuncList[eState].push_back(func);
	}

	template <typename T>
	void AddCollisionFunction(COLLISION_STATE eState, T* pObj,
		void(T::*pFunc)(CCollider*, CCollider*, float))
	{
		function<void(CCollider*, CCollider*, float)> func;

		// pObj : ȣ�� ��ü
		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_FuncList[eState].push_back(func);
	}


	void CallFunction(COLLISION_STATE eState, CCollider* pDest, float fDeltaTime)
	{
		list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
		list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd= m_FuncList[eState].end();

		for (iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter)
		{
			(*iter)(this, pDest, fDeltaTime);
		}
	}

protected:
	COLLIDER_TYPE	m_eColType;
	class CObj* m_pObj;
	list<CCollider*>		m_CollisionList;
	// C++11
	// �پ��� �浹ü�� ���õ� �Լ� �����(callback)
	list<function<void(CCollider*, CCollider*, float)>> m_FuncList[CS_END];

private : 
	friend class CObj;
};

