#pragma once

#include "../Game.h"

// 서브 관리자 객체기 때문에
// 싱글톤으로 생성할 것.
class CSceneManager
{
public : 
	bool Init();	
	/* 코어에도 있던 부분이다. */
	void Input(float fDeltaTime);
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime); // 그려야 하기 때문에 DC를 얻어온다.

public : 
	template <typename T>
	T* CreateScene(SCENE_CREATE sc = SC_CURRENT)
	{
		T* pScene = new T;

		pScene->SetSceneType(sc);

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return nullptr;
		}

		// 장면을 전환한다.
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

private : 
	SCENE_CHANGE ChangeScene();

private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;	// 장면 전환용 장면

	DECLARE_SINGLE(CSceneManager)
};
