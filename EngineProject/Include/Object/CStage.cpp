#include "CStage.h"
#include "../Resources/CTexture.h"
#include "../CCore.h"
#include "../Core/CCamera.h"

CStage::CStage()
{
}

CStage::CStage(const CStage& pStage) : 
	CStaticObj(pStage)
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1580.f, 740.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage1", L"Background.bmp");

	return true;
}

void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	// CStaticObj::Render(hDC, fDeltaTime);

	// 배경이 있는 경우
	if (m_pTexture)
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();

		// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
		// 1. DC
		// 2~3. 어디에 출력할것인가
		// 4~5. 화면상 얼마나 크게 출력할래 (창의 크기만큼!)
		// 6. source의 DC
		// 7~8. 이미지의 어디부터 출력?
		// 9. 6번 인자에 복사
		BitBlt(hDC, tPos.x, tPos.y,
			GET_RESOLUTION.nWidth, GET_RESOLUTION.nHeight,
			m_pTexture->GetDC(),
			tCameraPos.x, tCameraPos.y,
			SRCCOPY);
	}
}

CStage* CStage::Clone()
{
	return new CStage(*this);
}
