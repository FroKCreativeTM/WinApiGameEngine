#include "CPlayer.h"
#include "../Core/CInput.h"
#include "CBullet.h"
#include "../Collider/CRectCollider.h"
#include "../Core/CCamera.h"
#include "../Animation/CAnimation.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& ref) : 
    CMoveObj(ref)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    SetPos(100.f, 100.f);
    SetSize(108.75f, 121.f);
    SetImageOffset(108.75f, 121.f);
    SetSpeed(400.f);
    SetPivot(0.5f, 0.5f);
    SetImageOffset(0.f, 0.f);

    SetTexture("Player", L"Player.bmp");
    SetColorKey(255, 255, 255); // ���

    CRectCollider* pRC = AddCollider<CRectCollider>("PlayerBody");
    pRC->SetRect(-54.375f, -60.5f, 54.375f, 60.5f);
    pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
    pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

    m_nHP = 100;

    SetPhysics(true);
    SetForce(200.f);

    CAnimation * pAnima = CreateAnimation("PlayerAnimation");

    AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP,
        1.f,
        8, 1, // 8�忡 1��¥��
        0, 0,
        8, 1,
        0.f,
        "PlayerIdleLeft", L"Player/Idle/Left/PlayerIdleLeft.bmp");
    SetAnimationClipColorKey("IdleLeft", 255, 0, 255);

    AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN,
        1.f,
        4, 1, // 4�忡 1��¥��
        0, 0,
        4, 1,
        0.f,
        "PlayerRunLeft", L"Player/Run/Left/PlayerRunLeft.bmp");
    SetAnimationClipColorKey("RunLeft", 255, 0, 255);

    /* AttackLeft�� ������ �ִϸ��̼����� ���� ����ϴ�. */

    AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP,
        1.f,
        8, 1, // 8�忡 1��¥��
        0, 0,
        8, 1,
        0.f,
        "PlayerIdleRight", L"Player/Idle/Right/PlayerIdleRight.bmp");
    SetAnimationClipColorKey("IdleRight", 255, 0, 255);

    AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN,
        1.f,
        4, 1, // 4�忡 1��¥��
        0, 0,
        4, 1,
        0.f,
        "PlayerRunRight", L"Player/Run/Right/PlayerRunRight.bmp");
    SetAnimationClipColorKey("RunRight", 255, 0, 255);

    AddAnimationClip("AttackRight", AT_ATLAS, AO_ONCE_RETURN,
        1.f,
        4, 1, // 4�忡 1��¥��
        0, 0,
        4, 1,
        0.f,
        "PlayerAttackRight", L"Player/Attack/Right/PlayerAttackRight.bmp");
    SetAnimationClipColorKey("AttackRight", 255, 0, 255);

    vector<wstring> vecFileName;

    for (size_t i = 1; i <= 4 ; ++i)
    {
        wchar_t strFileName[MAX_PATH] = {};
        // ���ڿ� �����Լ�
        wsprintf(strFileName, L"Player/Attack/Left/%d.bmp", i);
        vecFileName.push_back(strFileName);
    }

    AddAnimationClip("AttackLeft", AT_FRAME, AO_ONCE_RETURN,
        1.f,
        4, 1, // 4�忡 1��¥��
        0, 0,
        4, 1,
        0.f,
        "PlayerAttackRight", vecFileName);
    SetAnimationClipColorKey("AttackLeft", 255, 0, 255);

    SAFE_RELEASE(pAnima);

    m_isLeft = false;

    return true;
}

void CPlayer::Input(float fDeltaTime)
{

    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::Input(fDeltaTime);

    if (KEYPRESS("MoveFront"))
    {
        MoveYFromSpeed(fDeltaTime, MD_BACK);
    }
    if (KEYPRESS("MoveBack"))
    {
        MoveYFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYPRESS("MoveLeft"))
    {
        MoveXFromSpeed(fDeltaTime, MD_BACK);
        m_pAnimation->ChangeClip("RunLeft");
        m_isLeft = true;
        m_pAnimation->SetDefaultClip("IdleLeft");
    }
    if (KEYPRESS("MoveRight"))
    {
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
        m_pAnimation->ChangeClip("RunRight");
        m_isLeft = false;
        m_pAnimation->SetDefaultClip("IdleRight");
    }
    if (KEYPRESS("Jump"))
    {
        Jump();
    }
    if (KEYPRESS("Fire"))
    {
        Fire();

        if (m_isLeft)
        {
            m_pAnimation->ChangeClip("AttackLeft");
        }
        else
        {
            m_pAnimation->ChangeClip("AttackRight");
        }
    }
}

int CPlayer::Update(float fDeltaTime)
{
    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::Update(fDeltaTime);

    // ������ ���� ���
    if (m_isAttack && m_pAnimation->GetMotionEnd())
    {
        m_isAttack = false;
    }

    if (!m_isMove && !m_isAttack)
    {
        m_pAnimation->ReturnClip();
    }

    return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::LateUpdate(fDeltaTime);

    return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::Render(hDC, fDeltaTime);

    wchar_t strHP[32] = {};
    wsprintf(strHP, L"HP : %d", m_nHP);

    POSITION tPos = m_tPos - m_tSize * m_tPivot;
    tPos -= GET_SINGLE(CCamera)->GetPos();

    TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP));
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Hit(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetObj()->GetTag() == "EnemyBullet") 
    {
        m_nHP -= 5;
    }
    else if (pDst->GetTag() == "StageCollder")
    {
        ClearGravity();
        JumpEnd();
        m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
    }
}

// �߷��� ���� ���ó�� �浹�� ���������� �Ͼ ��
// �̸� �̿��ؼ� �� ���·� ���д�. (���� ���¸ӽ�)
void CPlayer::HitStay(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetTag() == "StageCollder")
    {
        ClearGravity();
        JumpEnd();
        m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;

    }
}

void CPlayer::Fire()
{
    m_isAttack = true;

    CObj* pBullet = 
        CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

    // CS_LEAVE : ���������� ����
    pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

    POSITION tPos;

    if (m_isLeft)
    {
        tPos.x = GetLeft() + pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);
    }
    else
    {
        tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
    }

    tPos.y = GetCenter().y;

    // ������ ���� ��ǥ�� �����Ѵ�.
    pBullet->SetPos(tPos);

    if (m_isLeft)
    {
        ((CMoveObj*)pBullet)->SetAngle(PI);
    }

    SAFE_RELEASE(pBullet);
}
