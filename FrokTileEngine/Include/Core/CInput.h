#pragma once
#include "../Game.h"

typedef struct _tagKeyInfo
{
	string			strName;
	// unsigned long
	// ������ char Ÿ���̸� push
	vector<DWORD>	vecKey;
	bool			bDown;
	bool			bPress;
	bool			bUp;

	_tagKeyInfo() :
		bDown(false),
		bPress(false),
		bUp(false)
	{}
}KEYINFO, *PKEYINFO;

class CInput
{
public : 
	bool Init(HWND hWnd);
	void Update(float fDeltaTime);
	bool KeyDown(const string& strKey) const;
	bool KeyPress(const string& strKey) const;
	bool KeyUp(const string& strKey) const;

public : 
	template <typename T>
	bool AddKey(const T& data)
	{
		// ó���� NULL�� �Ǿ��ִ�.
		if (!m_pCreateKey)
		{
			m_pCreateKey = new KEYINFO;
		}

		// ���ø� �ĺ� ��ȣ�� ���� �����Ѵ�.
		const char* pTType = typeid(T).name();

		// ������ char�� ���
		if (strcmp(pTType, "char") == 0 ||
			strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}
		// map�� key���̴�.
		else
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		return true;
	}

	// template ... Types
	// ���� ���ø�
	// ������ ����Լ��� ���...
	template <typename T, typename ... Types>
	bool AddKey(const T& data, const Types& ...arg)
	{
		// ó���� NULL�� �Ǿ��ִ�.
		if (!m_pCreateKey)
		{
			m_pCreateKey = new KEYINFO;
		}

		// ���ø� �ĺ� ��ȣ�� ���� �����Ѵ�.
		const char* pTType = typeid(T).name();

		// ������ char�� ���
		if (strcmp(pTType, "char") == 0 ||
			strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}
		// map�� key���̴�.
		else
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		// ��ͷ� ������.
		AddKey(arg...);

		// ��Ϳ� ������ �ٽ� �ʱ�ȭ
		if (m_pCreateKey)
		{
			m_pCreateKey = nullptr;
		}

		return true;
	}

	class CMouse* GetMouse() const
	{
		return m_pMouse;
	}

	POSITION  GetMouseClientPos() const;
	POSITION  GetMouseWorldPos() const;
	POSITION  GetMouseMove() const;	// �󸶳� ���콺�� �������°�.

private : 
	PKEYINFO FindKey(const string& strKey) const;

private : 
	HWND		m_hWnd;
	// �� Ű�� ������ ȣ��Ǵ� �Լ� ����� ��Ī�� ���̴�.
	unordered_map<string, PKEYINFO>	m_mapKey;
	// ��� �Լ� �������
	PKEYINFO	m_pCreateKey;

private : 
	// ���콺�� ���� ����
	POINT				m_tMousePos;
	POINT				m_tMouseMove;
	class CMouse*		m_pMouse;

	DECLARE_SINGLE(CInput)
};

