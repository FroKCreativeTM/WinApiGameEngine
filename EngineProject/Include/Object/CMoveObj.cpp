#include "CMoveObj.h"

CMoveObj::CMoveObj()
{
}

// �θ��� ���� ������ ����!
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
