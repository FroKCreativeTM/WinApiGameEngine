#include "CInput.h"
#include "../Object/CMouse.h"
#include "../Animation/CAnimation.h"
#include "../Scene/CLayer.h"
#include "../Collider/CCollisionManager.h"

DEFINITION_SINGLE(CInput);

CInput::CInput() : 
	m_pCreateKey(nullptr),
	m_pMouse(nullptr)
{

}

CInput::~CInput()
{
	CObj::EraseObj(m_pMouse);	// ������Ʈ ��Ͽ��� ���� �ڿ� SAFE_RELEASE
	SAFE_RELEASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey('D', "MoveRight");
	AddKey('A', "MoveLeft");
	AddKey(VK_CONTROL, "Fire");
	AddKey(VK_SPACE, "Jump");
	AddKey(VK_LBUTTON, "MouseLButton");
	AddKey(VK_RBUTTON, "MouseRButton");

	// ���콺 ��ġ�� ������ �Լ�
	GetCursorPos(&m_tMousePos);

	// ���콺 ����
	m_pMouse = CObj::CreateObj<CMouse>("Mouse");

	m_pMouse->SetSize(32, 31);
	// m_pMouse->SetTexture("Mouse0", L"StartBackground.bmp");

	CAnimation* pAni = m_pMouse->CreateAnimation("MouseAnimation");

	m_pMouse->AddAnimationClip("MouseIdle", AT_ATLAS, AO_LOOP,
		1.f,
		1, 1, // 4�忡 1��¥��
		0, 0,
		1, 1,
		0.f,
		"MouseIdle", L"Mouse/MouseCursor.bmp");
	m_pMouse->SetAnimationClipColorKey("MouseIdle", 255, 0, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CInput::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int nPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			// üũ�Ϸ��� Ű�� ���ȴٸ�
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
			{
				nPushCount++;
			}			
		}

		// ���� ���
		if (nPushCount == iter->second->vecKey.size())
		{
			// ó�� ���� ���
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bDown = true;
				iter->second->bPress = true;
			}
			// ��� ���� ���
			else if (iter->second->bDown)
			{
				iter->second->bDown = false;
			}
		}
		// �� ����
		else
		{
			// �����ٰ� �� ���
			if (iter->second->bDown || iter->second->bPress)
			{
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPress = false;
			}
			else if (iter->second->bUp)
			{
				iter->second->bUp = false;
			}
		}
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

	// �浹 �Ŵ����� �������� �浹 ó���� �ȴ�.
	GET_SINGLE(CCollisionManager)->AddObject(m_pMouse);
}

bool CInput::KeyDown(const string& strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);
	if (!pInfo)
		return false;
	return pInfo->bDown;
}

bool CInput::KeyPress(const string& strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);
	if (!pInfo)
		return false;
	return pInfo->bPress;
}

bool CInput::KeyUp(const string& strKey) const
{
	PKEYINFO pInfo = FindKey(strKey);
	if (!pInfo)
		return false;
	return pInfo->bUp;
}

POSITION CInput::GetMouseClientPos() const
{
	return m_pMouse->GetPos();
}

POSITION CInput::GetMouseWorldPos() const
{
	return m_pMouse->GetWorldPos();
}

POSITION CInput::GetMouseMove() const
{
	return m_pMouse->GetMove();
}

PKEYINFO CInput::FindKey(const string& strKey) const
{
	unordered_map<string, PKEYINFO>::const_iterator iter 
		= m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
	{
		return nullptr;
	}
	return iter->second;
}
