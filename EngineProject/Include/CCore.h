#pragma once

#include "Game.h"

// 게임의 코어
class CCore
{
public : 
	static CCore* GetInst();
	static void DestroyInst();

// 싱글톤! 
// static이라 결국은 전역변수화되니 이 점 주의!(멀티스레드 상에선 특히나)
// 메모리 생성 시점! 프로그램 시작할 때
private : 
	static CCore* m_pInstance;

// 외부에서 메모리 건들지 못하게.
private : 
	CCore();
	~CCore();
};

