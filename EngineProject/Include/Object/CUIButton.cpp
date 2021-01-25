#include "CUIButton.h"
#include "../Collider/CRectCollider.h"      // ���콺 �浹�� ���� �뵵
#include "../Core/CInput.h"                 // ���콺 �Է¿� ���� ó���뵵

CUIButton::CUIButton() : 
    m_bEnableCallback(false),
    m_eButtonState(BS_NONE)
{
}

CUIButton::CUIButton(const CUIButton& ref) : 
    CUI(ref),
    m_eButtonState(BS_NONE)
{
    m_bEnableCallback = ref.m_bEnableCallback;
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
    CRectCollider* pCollider = AddCollider<CRectCollider>("ButtonBody");
    SAFE_RELEASE(pCollider);

    return true;
}

void CUIButton::Input(float fDeltaTime)
{
    CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime)
{
    CUI::Update(fDeltaTime);
    return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
    CUI::LateUpdate(fDeltaTime);

    // LBUTTON Ŭ���� �ߴ��� �Ǵ��Ѵ�.
    if (m_eButtonState != BS_NONE)
    {
        if (KEYDOWN("MouseLButton"))
        {
            m_eButtonState = BS_CLICK;
            SetImageOffset(m_tSize.x * 2, 0.f);
        }
    }

    // ���� Ŭ�� �� ���ٸ�
    if (m_eButtonState == BS_CLICK && KEYUP("MouseLButton"))
    {
        m_eButtonState = BS_MOUSEON;
        SetImageOffset(m_tSize.x, 0.f);
        // �ݹ� ������ �Ǿ�����
        if (m_bEnableCallback)
        {
            m_BtnCallback(fDeltaTime);
        }
    }

    return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
    CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
    CUI::Render(hDC, fDeltaTime);
}

CUIButton* CUIButton::Clone()
{
    return new CUIButton(*this);
}

void CUIButton::MouseOn(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    // ������ ���콺��� ������ ���� ������ �̿� ���� ������ �����;��Ѵ�.
    if (pDst->GetTag() == "Mouse")
    {
        m_eButtonState = BS_MOUSEON;

        // �̹��� offset ����
        SetImageOffset(m_tSize.x, 0.f);
    }
}

void CUIButton::MouseOut(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetTag() == "Mouse")
    {
        m_eButtonState = BS_NONE;
        SetImageOffset(0.f, 0.f);
    }
}
