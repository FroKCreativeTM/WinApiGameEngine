#pragma once
#include "CUI.h"

class CUIButton :
    public CUI
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIButton* Clone();

public:
	void MouseOn(CCollider* pSrc, CCollider* pDst, float fDeltaTime);
	void MouseOut(CCollider* pSrc, CCollider* pDst, float fDeltaTime);

public : 
	/* ���� �ݹ��Լ� ��� */
	template <typename T>
	void SetCallback(T* pObj, void (T::* pFunc)(float))
	{
		m_BtnCallback = bind(pFunc, pObj, placeholders::_1);
		m_bEnableCallback = true;
	}

	void SetCallback(void (*pFunc)(float))
	{
		m_BtnCallback = bind(pFunc, placeholders::_1);
		m_bEnableCallback = true;
	}

private : 
	// �� ��ư�� ���� �ٸ� ������� �����ϰ� ������ش�.
	function<void(float fTime)> m_BtnCallback;
	// �ݹ��� Ȱ��ȭ �Ǿ��ִ°�
	bool						m_bEnableCallback;

private:
	friend class CObj;
	friend class CScene;

private:
	CUIButton();
	CUIButton(const CUIButton& ref);
	~CUIButton();
};

