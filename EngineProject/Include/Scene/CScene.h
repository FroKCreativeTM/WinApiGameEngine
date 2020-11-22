#pragma once

#include "../Game.h"

// 실제 장면을 담당하는 장면 클래스의 베이스 클래스이다.
// 이 클래스의 하위로는 레이어가 있다.
class CScene
{
public:
	/* 레이어와 관련된 메소드 */
	class CLayer* CreateLayer(const string& strTag,
		int nZOrder = 0);
	class CLayer* FindLayer(const string& strTag);

public : 
	// 전역 함수이다!!!!(list의 sort caller가 callee로 전역함수를 원한다.)
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

public:
	/* 게임 요소를 위한 메소드 */
	virtual bool Init();
	// 각 씬마다의 고유한 기능을 넣기 위한 메소드다.
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

protected:
	friend class CSceneManager;	// 씬 매니저만 이 클래스에 접근 가능하다.

protected : 
	CScene();
	virtual ~CScene() = 0;	// 순수 가상함수로!


// 오브젝트 자체를 레이어에 배치할 것이다.
// 레이어는 리스트로 보관하자.
protected : 
	// 이 방식을 이용하면 장면이 날아가면 그 장면에 종속된 모든
	// 레이어들도 함께 날아간다.
	list<class CLayer*> m_LayerList;	
};

