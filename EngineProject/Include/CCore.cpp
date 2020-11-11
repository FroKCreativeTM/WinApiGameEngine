#include "CCore.h"

// nullptr 선언은 여기서 가능하다.
// 왜냐면 얘는 프로그램 시작과 생기는 인스턴스고
// 전역변수니까(static)
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
