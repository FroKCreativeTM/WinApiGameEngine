#include "CObj.h"
#include "../Scene/CScene.h"
#include "../Scene/CLayer.h"

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
}

// m_nRef가 0이면 지워진다.
// 즉 이것을 만드는 시점에서 누군가는 이 오브젝트를 참조한다.
CObj::CObj()  
{
}

// 모든 정보를 다 복사하자.
CObj::CObj(const CObj& ref) 
{
	*this = ref;
}

CObj::~CObj()
{
}
