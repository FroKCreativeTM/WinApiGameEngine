#include "CPlayer.h"
#include "../Core/CInput.h"
#include "CBullet.h"

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
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
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
