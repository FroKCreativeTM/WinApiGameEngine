#pragma once

#include "../Game.h"

// 게임 내 보이는 모든 오브젝트들이 상속받을 클래스입니다.
// 움직임이 있는가 없는가를 나눈다.
// 위치와 크기가 필요하다.
class CObj
{
protected : 
	CObj();
	virtual ~CObj();

protected : 
	// 위치와 크기
	POSITION		m_tPos;
	_PSIZE			m_tSize;
};

