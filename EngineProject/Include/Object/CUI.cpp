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
	// 텍스처가 있는 경우
	if (m_pTexture)
	{
		POSITION tImagePos; // (0,0)

		// 만약 애니메이션이 있다면
		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			// 이미지 크기 갱신
			if (pClip->eType == AT_ATLAS)
			{
				// 아틀라스는 오프셋은 애니메이션이 있던 없던 둘 다 적용한다.
				tImagePos.x = pClip->nFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->nFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		// 컬러키 활성화 여부에 따라 다르다.
		if (m_pTexture->GetColorKeyEnable())
		{
			// 인자가 
			TransparentBlt(hDC, m_tPos.x, m_tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,		// 시작 위치
				m_tSize.x, m_tSize.y, 	// 크기
				m_pTexture->GetColorKey());
		}
		else
		{
			// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
			// 1. DC
			// 2~3. 어디에 출력할것인가
			// 4~5. 화면상 얼마나 크게 출력할래
			// 6. source의 DC
			// 7~8. 이미지의 어디부터 출력?
			// 9. 6번 인자에 복사
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
		// 콜라이더가 비활성화 되어있다면
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
