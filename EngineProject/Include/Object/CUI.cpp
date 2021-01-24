#include "CUI.h"
#include "../Animation/CAnimation.h"
#include "../Resources/CTexture.h"

CUI::CUI()
{
}

CUI::CUI(const CUI& ref) : 
	CObj(ref)
{
}

CUI::~CUI()
{
}

void CUI::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CUI::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	return 0;
}

int CUI::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CUI::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CUI::Render(HDC hDC, float fDeltaTime)
{
	// �ؽ�ó�� �ִ� ���
	if (m_pTexture)
	{
		POSITION tImagePos; // (0,0)

		// ���� �ִϸ��̼��� �ִٸ�
		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			// �̹��� ũ�� ����
			if (pClip->eType == AT_ATLAS)
			{
				// ��Ʋ�󽺴� �������� �ִϸ��̼��� �ִ� ���� �� �� �����Ѵ�.
				tImagePos.x = pClip->nFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->nFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		// �÷�Ű Ȱ��ȭ ���ο� ���� �ٸ���.
		if (m_pTexture->GetColorKeyEnable())
		{
			// ���ڰ� 
			TransparentBlt(hDC, m_tPos.x, m_tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,		// ���� ��ġ
				m_tSize.x, m_tSize.y, 	// ũ��
				m_pTexture->GetColorKey());
		}
		else
		{
			// ȭ�鿡 DC�� ���ִ� ������ ������ִ� �Լ��̴�.
			// 1. DC
			// 2~3. ��� ����Ұ��ΰ�
			// 4~5. ȭ��� �󸶳� ũ�� ����ҷ�
			// 6. source�� DC
			// 7~8. �̹����� ������ ���?
			// 9. 6�� ���ڿ� ����
			BitBlt(hDC, m_tPos.x, m_tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,
				SRCCOPY);
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		// �ݶ��̴��� ��Ȱ��ȭ �Ǿ��ִٸ�
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}
