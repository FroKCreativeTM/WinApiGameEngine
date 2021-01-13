#include "CPlayer.h"
#include "../Core/CInput.h"
#include "CBullet.h"
#include "../Collider/CRectCollider.h"
#include "../Core/CCamera.h"

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
    SetSize(100.f, 100.f);
    SetSpeed(400.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("Player", L"todd.bmp");

    CRectCollider* pRC = AddCollider<CRectCollider>("PlayerBody");
    pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
    pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
    pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

    m_nHP = 100;

    SetPhysics(true);
    SetForce(200.f);

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
    }
    if (KEYPRESS("MoveRight"))
    {
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYPRESS("Jump"))
    {
        Jump();
    }
    if (KEYPRESS("Fire"))
    {
        Fire();
    }
}

int CPlayer::Update(float fDeltaTime)
{
    // �θ��� �Լ��� ȣ�����ش�.
    CMoveObj::Update(fDeltaTime);
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
    }
}

// �߷��� ���� ���ó�� �浹�� ���������� �Ͼ ��
// �̸� �̿��ؼ� �� ���·� ���д�. (���� ���¸ӽ�)
void CPlayer::HitStay(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetTag() == "StageCollder")
    {
        ClearGravity();
    }
}

void CPlayer::Fire()
{
    CObj* pBullet = 
        CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

    // CS_LEAVE : ���������� ����
    pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

    POSITION tPos;
    tPos.x = GetRight() 
        + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    // ������ ���� ��ǥ�� �����Ѵ�.
    pBullet->SetPos(tPos);

    SAFE_RELEASE(pBullet);
}
