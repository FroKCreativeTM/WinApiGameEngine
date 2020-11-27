#pragma once

#include "../Game.h"

// ���� ������ ��ü�� ������
// �̱������� ������ ��.
class CSceneManager
{
public : 
	bool Init();	
	/* �ھ�� �ִ� �κ��̴�. */
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime); // �׷��� �ϱ� ������ DC�� ���´�.

public : 
	template <typename T>
	T* CreateScene(SCENE_CREATE sc)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return nullptr;
		}

		// ����� ��ȯ�Ѵ�.
		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	}

public : 
	class CScene* GetScene() const
	{
		return m_pScene;
	}

private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;	// ��� ��ȯ�� ���

	DECLARE_SINGLE(CSceneManager)
};
