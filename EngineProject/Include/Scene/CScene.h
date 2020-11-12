#pragma once

#include "../Game.h"

// ���� ����� ����ϴ� ��� Ŭ������ ���̽� Ŭ�����̴�.
// �� Ŭ������ �����δ� ���̾ �ִ�.
class CScene
{
public:
	class CLayer* CreateLayer(const string& strTag,
		int nZOrder = 0);

	// ���� �Լ��̴�!!!!(list�� sort caller�� callee�� �����Լ��� ���Ѵ�.)
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

public:
	virtual bool Init();

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

