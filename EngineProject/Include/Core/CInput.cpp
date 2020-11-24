#include "CInput.h"

DEFINITION_SINGLE(CInput);

CInput::CInput() : 
	m_pCreateKey(nullptr)
{

}

CInput::~CInput()
{
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey('D', "MoveRight");
	AddKey('A', "MoveLeft");
	AddKey(VK_SPACE, "Fire");

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
			// 체크하려는 키가 눌렸다면
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
			{
				nPushCount++;
			}			
		}

		// 누른 경우
		if (nPushCount == iter->second->vecKey.size())
		{
			// 처음 누른 경우
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bDown = true;
				iter->second->bPress = true;
			}
			// 계속 누른 경우
			else if (iter->second->bDown)
			{
				iter->second->bDown = false;
			}
		}
		// 안 누름
		else
		{
			// 누르다가 뗀 경우
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
