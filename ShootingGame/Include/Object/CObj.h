#pragma once

#include "../Core/CRef.h"

class CScene;
class CLayer;

// 게임 내 보이는 모든 오브젝트들이 상속받을 클래스입니다.
// 움직임이 있는가 없는가를 나눈다.
// 위치와 크기가 필요하다.

// CRef : 레퍼런스 카운터를 담당하는 기능이다.
class CObj : 
	public CRef
{
public : 
	void SetTag(const string& tag)
	{
		this->m_strTag = tag;
	}

	void SetPos(const POSITION& ref)
	{
		this->m_tPos = ref;
	}

	void SetPos(float x, float y)
	{
		this->m_tPos.x = x;
		this->m_tPos.y = y;
	}

	void SetSize(const _SIZE& ref)
	{
		this->m_tSize = ref;
	}

	void SetSize(float x, float y)
	{
		this->m_tSize.x = x;
		this->m_tSize.y = y;
	}

	string GetTag() const
	{
		return m_strTag;
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE GetSize() const
	{
		return m_tSize;
	}

public : 
	/* 게임 요소를 위한 메소드 */
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public : 
	void SetScene(class CScene* pScene)
	{
		this->m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		this->m_pLayer = pLayer;
	}

	class CScene* GetScene() const
	{
		return m_pScene;
	}

	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}

protected :
	CObj();
	CObj(const CObj& ref);
	virtual ~CObj();

protected :
	// 오브젝트도 태그를 가진다.
	string			m_strTag;	
	// 위치와 크기
	POSITION		m_tPos;
	_SIZE			m_tSize;
	POSITION		m_tPivot;

protected : 
	// 자기가 속한 장면과 레이어를 알게 한다.
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public : 
	// 굉장히 다양한 타입의 오브젝트를 만들기 위한 
	// 템플릿 타입의 메소드이다.
	template <typename T>
	static T* CreateObj(const string& strTag,
		class CLayer* pLayer = nullptr);
};

#include "CObj.inl"