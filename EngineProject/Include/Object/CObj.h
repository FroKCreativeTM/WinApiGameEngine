#pragma once

#include "../Core/CRef.h"

class CScene;
class CLayer;

// ���� �� ���̴� ��� ������Ʈ���� ��ӹ��� Ŭ�����Դϴ�.
// �������� �ִ°� ���°��� ������.
// ��ġ�� ũ�Ⱑ �ʿ��ϴ�.

// CRef : ���۷��� ī���͸� ����ϴ� ����̴�.
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
	/* ���� ��Ҹ� ���� �޼ҵ� */
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
	// ������Ʈ�� �±׸� ������.
	string			m_strTag;	
	// ��ġ�� ũ��
	POSITION		m_tPos;
	_SIZE			m_tSize;
	POSITION		m_tPivot;

protected : 
	// �ڱⰡ ���� ���� ���̾ �˰� �Ѵ�.
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public : 
	// ������ �پ��� Ÿ���� ������Ʈ�� ����� ���� 
	// ���ø� Ÿ���� �޼ҵ��̴�.
	template <typename T>
	static T* CreateObj(const string& strTag,
		class CLayer* pLayer = nullptr);
};

#include "CObj.inl"