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
};

