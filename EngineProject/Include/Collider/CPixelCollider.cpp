#include "CPixelCollider.h"
#include "../Object/CObj.h"
#include "CRectCollider.h"
#include "CSphereCollider.h"
#include "../Core/CPathManager.h"		// Full Path 만들기 위한 용도

bool CPixelCollider::Init()
{
	return true;
}

void CPixelCollider::Input(float fDeltaTime)
{
}

int CPixelCollider::Update(float fDeltaTime)
{
	return 0;
}

int CPixelCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CPixelCollider::Collision(CCollider* pDst)
{
	return false;
}

void CPixelCollider::Render(HDC hDC, float fDeltaTime)
{
}

CPixelCollider* CPixelCollider::Clone()
{
	return new CPixelCollider(*this);
}

bool CPixelCollider::SetPixelInfo(char* pFileName, const string& strPathKey)
{
	return true;
}

CPixelCollider::CPixelCollider()
{
}

CPixelCollider::CPixelCollider(const CPixelCollider& col) : 
	CCollider(col)
{
}

CPixelCollider::~CPixelCollider()
{
}
