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

	// ����� �ִ� ���
	if (m_pTexture)
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();

		// ȭ�鿡 DC�� ���ִ� ������ ������ִ� �Լ��̴�.
		// 1. DC
		// 2~3. ��� ����Ұ��ΰ�
		// 4~5. ȭ��� �󸶳� ũ�� ����ҷ� (â�� ũ�⸸ŭ!)
		// 6. source�� DC
		// 7~8. �̹����� ������ ���?
		// 9. 6�� ���ڿ� ����
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
