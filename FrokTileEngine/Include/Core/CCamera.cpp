#include "CCamera.h"
#include "../Object/CObj.h"

DEFINITION_SINGLE(CCamera)

CCamera::CCamera() : 
	m_pTarget(nullptr)
{
}

CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget);
}

bool CCamera::Init(const POSITION& tPos, 
	const RESOLUTION& tRS, 
	const RESOLUTION& tWorldRS)
{
	/* 화면이 중간에서부터 따라오게 설정 */
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);

	return true;
}

void CCamera::Input(float fDeltaTime)
{
	if (!m_pTarget)
	{

	}
}

void CCamera::Update(float fDeltaTime)
{
	// 타겟이 있다면
	if (m_pTarget)
	{
		// 위치 및 피봇, 사이즈 정보를 가져온다.
		POSITION	tPos = m_pTarget->GetPos();
		POSITION	tPivot = m_pTarget->GetPivot();
		_SIZE		tSize = m_pTarget->GetSize();

		float fLeft = tPos.x - tPivot.x * tSize.x;
		float fRight = fLeft + tSize.x;
		float fTop = tPos.y - tPivot.y * tSize.y;
		float fBottom = fTop + tSize.y;

		float fLeftArea = m_tClientRS.nWidth * m_tPivot.x;
		float fRightArea = m_tClientRS.nWidth - fLeftArea;
		float fTopArea = m_tClientRS.nHeight * m_tPivot.y;
		float fBottomArea = m_tClientRS.nHeight - fTopArea;

		// 타겟의 x좌표가 왼쪽 공간에 존재해서, 
		// 카메라가 더이상 가면 안 되는 경우
		if (tPos.x <= fLeftArea)
		{
			m_tPos.x = 0.f;
		}
		// 오른쪽 영역 끝까지 온 경우
		else if (tPos.x >= m_tWorldRS.nWidth - fRightArea)
		{
			m_tPos.x = m_tWorldRS.nWidth - m_tClientRS.nWidth;
		}
		// 안에 존재하니 스크롤!
		else
		{
			m_tPos.x = tPos.x - m_tClientRS.nWidth * m_tPivot.x;
		}

		// 타겟의 y좌표가 왼쪽 공간에 존재해서, 
		// 카메라가 더이상 가면 안 되는 경우
		if (tPos.y <= fTopArea)
		{
			m_tPos.y = 0.f;
		}
		// 오른쪽 영역 끝까지 온 경우
		else if (tPos.y >= m_tWorldRS.nHeight - fBottomArea)
		{
			m_tPos.y = m_tWorldRS.nHeight - m_tClientRS.nHeight;
		}
		// 안에 존재하니 스크롤!
		else
		{
			m_tPos.y = tPos.y 
				- m_tClientRS.nHeight * m_tPivot.y;
		}
	}
}

void CCamera::Scroll(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	if (m_tPos.x < 0)
	{
		m_tPos.x = 0;
	}
	else if (m_tPos.x > m_tWorldRS.nWidth - m_tClientRS.nWidth)
	{
		m_tPos.x = m_tClientRS.nWidth;
	}
	if (m_tPos.y < 0)
	{
		m_tPos.y = 0;
	}
	else if (m_tPos.y > m_tWorldRS.nHeight - m_tClientRS.nHeight)
	{
		m_tPos.y = m_tClientRS.nHeight;
	}
}

void CCamera::SetTarget(CObj* pObj)
{
	// 기존 타겟은 날린다.
	SAFE_RELEASE(m_pTarget);
	// 다시 등록한다.
	m_pTarget = pObj;

	// 이런 예외처리가 없다면 크래시가 날 것이다!
	if (m_pTarget)
	{
		m_pTarget->AddRef();
	}
}
