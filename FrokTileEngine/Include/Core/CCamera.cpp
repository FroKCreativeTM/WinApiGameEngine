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
	/* ȭ���� �߰��������� ������� ���� */
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
	// Ÿ���� �ִٸ�
	if (m_pTarget)
	{
		// ��ġ �� �Ǻ�, ������ ������ �����´�.
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

		// Ÿ���� x��ǥ�� ���� ������ �����ؼ�, 
		// ī�޶� ���̻� ���� �� �Ǵ� ���
		if (tPos.x <= fLeftArea)
		{
			m_tPos.x = 0.f;
		}
		// ������ ���� ������ �� ���
		else if (tPos.x >= m_tWorldRS.nWidth - fRightArea)
		{
			m_tPos.x = m_tWorldRS.nWidth - m_tClientRS.nWidth;
		}
		// �ȿ� �����ϴ� ��ũ��!
		else
		{
			m_tPos.x = tPos.x - m_tClientRS.nWidth * m_tPivot.x;
		}

		// Ÿ���� y��ǥ�� ���� ������ �����ؼ�, 
		// ī�޶� ���̻� ���� �� �Ǵ� ���
		if (tPos.y <= fTopArea)
		{
			m_tPos.y = 0.f;
		}
		// ������ ���� ������ �� ���
		else if (tPos.y >= m_tWorldRS.nHeight - fBottomArea)
		{
			m_tPos.y = m_tWorldRS.nHeight - m_tClientRS.nHeight;
		}
		// �ȿ� �����ϴ� ��ũ��!
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
	// ���� Ÿ���� ������.
	SAFE_RELEASE(m_pTarget);
	// �ٽ� ����Ѵ�.
	m_pTarget = pObj;

	// �̷� ����ó���� ���ٸ� ũ���ð� �� ���̴�!
	if (m_pTarget)
	{
		m_pTarget->AddRef();
	}
}
