#include "CMoveObj.h"

CMoveObj::CMoveObj()
{
}

// 부모의 복사 생성자 먼저!
CMoveObj::CMoveObj(const CMoveObj& ref) : 
	CObj(ref)
{

}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::Input(float fDeltaTime)
{
}

int CMoveObj::Update(float fDeltaTime)
{
	return 0;
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
}
