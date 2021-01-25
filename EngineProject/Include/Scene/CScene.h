#pragma once

#include "../Game.h"

// ���� ����� ����ϴ� ��� Ŭ������ ���̽� Ŭ�����̴�.
// �� Ŭ������ �����δ� ���̾ �ִ�.
class CScene
{
public:
	/* ���̾�� ���õ� �޼ҵ� */
	class CLayer* CreateLayer(const string& strTag,
		int nZOrder = 0);
	class CLayer* FindLayer(const string& strTag);

public : 
	// ���� �Լ��̴�!!!!(list�� sort caller�� callee�� �����Լ��� ���Ѵ�.)
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

public:
	/* ���� ��Ҹ� ���� �޼ҵ� */
	virtual bool Init();
	// �� �������� ������ ����� �ֱ� ���� �޼ҵ��.
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public : 
	// ������Ÿ�� ���� �޼ҵ�
	static void ErasePrototype(SCENE_CREATE sc);	// ��ü
	static void ErasePrototype(const string& strTag, SCENE_CREATE sc);

	// ������Ÿ�� ���� �޼ҵ�
	template<typename T>
	T* CreatePrototype(const string& strTag, SCENE_CREATE sc)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype[sc].insert(make_pair(strTag, pObj));

		return pObj;
	}

protected:
	friend class CSceneManager;	// �� �Ŵ����� �� Ŭ������ ���� �����ϴ�.

protected : 
	CScene();
	virtual ~CScene() = 0;	// ���� �����Լ���!


// ������Ʈ ��ü�� ���̾ ��ġ�� ���̴�.
// ���̾�� ����Ʈ�� ��������.
protected : 
	// �� ����� �̿��ϸ� ����� ���ư��� �� ��鿡 ���ӵ� ���
	// ���̾�鵵 �Բ� ���ư���.
	list<class CLayer*> m_LayerList;	
	SCENE_CREATE		m_eSceneType;

public :
	void SetSceneType(SCENE_CREATE eType)
	{
		m_eSceneType = eType;
	}

	SCENE_CREATE GetSceneType() const
	{
		return m_eSceneType;
	}

public:
	// ������ ���� �ʿ��ϴ�.
	static class CObj* FindPrototype(const string& strTag, SCENE_CREATE sc);
	static void ChangePrototype();

private:
	// ���� ��ü(������Ÿ��)�� ����
	// ������ �뵵, 
	// ���ε�� ��ũ�� ����� ġ��
	// HP ����� ������ ���� ���̴�.
	// �ٵ� ������ ��� ���ʹ� ������ �ٸ� ���̴�.
	// �׷��� ���Ͽ� �ִ� ���� �ε����ٵ� ������ ����!
	// �׷��� ������ ����ٰ� �̸� ��������, �������� ��ü����
	// ����� �� ���̴�.
	static unordered_map<string, class CObj*> m_mapPrototype[SC_END];
};

