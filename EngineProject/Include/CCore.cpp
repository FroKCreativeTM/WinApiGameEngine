#include "CCore.h"

// nullptr ������ ���⼭ �����ϴ�.
// �ֳĸ� ��� ���α׷� ���۰� ����� �ν��Ͻ���
// ���������ϱ�(static)
CCore* CCore::m_pInstance = nullptr;

CCore* CCore::GetInst()
{
	if (!m_pInstance)
	{
		m_pInstance = new CCore;
	}
	return m_pInstance;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInstance);
}

CCore::CCore()
{
}

CCore::~CCore()
{
}
