#include "CCollider.h"
#include "../Object/CObj.h"
#include "../Core/CMath.h"

bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dst)
{
	if (src.left > dst.right)
	{
		return false;
	}
	else if (src.right < dst.left)
	{
		return false;
	}
	else if (src.top > dst.bottom)
	{
		return false;
	}
	else if (src.bottom < dst.top)
	{
		return false;
	}
	return true;
}

bool CCollider::CollisionRectToSphere(const RECTANGLE& src, const SPHERE& dst)
{
	// ���� ������ x ��ǥ�� �簢���� ���� ���� �ȿ� �ִ���,
	// ���� ������ y ��ǥ�� �簢���� ���� ���� �ȿ� �ִ��� üũ�Ѵ�.
	if ((src.left <= dst.tCenter.x && dst.tCenter.x <= src.right) ||
		(src.top <= dst.tCenter.y && dst.tCenter.y <= src.bottom))
	{
		RECTANGLE tRC = src;
		tRC.left -= dst.fRadius;
		tRC.top -= dst.fRadius;
		tRC.right += dst.fRadius;
		tRC.bottom += dst.fRadius;

		if (dst.tCenter.x < tRC.left)
		{
			return false;
		}
		else if (dst.tCenter.x > tRC.right)
		{
			return false;
		}
		else if (dst.tCenter.y < tRC.top)
		{
			return false;
		}
		else if (dst.tCenter.y > tRC.bottom)
		{
			return false;
		}

		return true;
	}
	
	// �簢���� 4���� ���� �ϳ��� �� �ȿ� ���� ��� �浹�̴�.
	POSITION tPos[4];
	tPos[0] = POSITION(src.left, src.top);
	tPos[1] = POSITION(src.right, src.top);
	tPos[2] = POSITION(src.left, src.bottom);
	tPos[3] = POSITION(src.right, src.bottom);

	for (int i = 0; i < 4; ++i)
	{
		float fDist = CMath::Distance(tPos[i], dst.tCenter);
		if (fDist <= dst.fRadius)
		{
			return true;
		}
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE& src, const SPHERE& dst)
{
	float fDist = CMath::Distance(src.tCenter, dst.tCenter);

	// �� �������� �պ��� ������ true
	return fDist <= src.fRadius + dst.fRadius;
}

bool CCollider::CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& dst, int nWidth, int nHeight)
{
	// ���� ���ٰ� �����Ѵ�.
	m_tHitPoint.x = -1;
	m_tHitPoint.y = -1;

	int nStartX, nEndX;
	int nStartY, nEndY;

	nStartX = src.left < 0 ? 0 : src.left;
	nEndX = src.right >= nWidth ? nWidth - 1 : src.right;

	nStartY = src.top < 0 ? 0 : src.top;
	nEndY = src.bottom >= nHeight ? nHeight - 1 : src.bottom;

	for (size_t y = nStartY; y <= nEndY; ++y)
	{
		for (size_t x = nStartX; x <= nEndX; ++x)
		{
			int idx = y * nWidth + x;
			const PIXEL& pixel = dst[idx];

			if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
			{
				m_tHitPoint.x = x;
				m_tHitPoint.y = y;
				return true;
			}
		}
	}

	return false;
}

CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider& col)
{
	*this = col;
}

CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		// �� ���� ���� �� ����
		(*iter)->EraseCollsionList(this);
	}
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDst)
{
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}