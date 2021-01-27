#include "CStaticObj.h"

CStaticObj::CStaticObj()
{
}

CStaticObj::CStaticObj(const CStaticObj& ref) : 
    CObj(ref)
{
}

CStaticObj::~CStaticObj()
{
}

void CStaticObj::Input(float fDeltaTime)
{
    CObj::Input(fDeltaTime);
}

int CStaticObj::Update(float fDeltaTime)
{
    CObj::Update(fDeltaTime);
    return 0;
}

int CStaticObj::LateUpdate(float fDeltaTime)
{
    CObj::LateUpdate(fDeltaTime);
    return 0;
}

void CStaticObj::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
}

void CStaticObj::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);
}

void CStaticObj::Save(FILE* pFile)
{
    CObj::Save(pFile);
}

void CStaticObj::Load(FILE* pFile)
{
}
