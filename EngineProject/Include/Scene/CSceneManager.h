#pragma once

#include "../Game.h"

// ���� ������ ��ü�� ������
// �̱������� ������ ��.
class CSceneManager
{
private : 
	class CScene* m_pScene;
	class CScene* m_pNextScene;	// ��� ��ȯ�� ���

public : 
	bool Init();

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

	DECLARE_SINGLE(CSceneManager)
};
