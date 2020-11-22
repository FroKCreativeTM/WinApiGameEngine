#include "CZako.h"

CZako::CZako()
{
}

CZako::CZako(const CZako& mushroom)
{
}

CZako::~CZako()
{
}

bool CZako::Init()
{
	return false;
}

int CZako::Update(float fDeltaTime)
{
	return 0;
}

int CZako::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CZako::Collision(float fDeltaTime)
{
}

void CZako::Render(HDC hDC, float fDeltaTime)
{
}

CZako* CZako::Clone()
{
	return new CZako(*this);
}
