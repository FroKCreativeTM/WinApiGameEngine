#pragma once

#include "../Game.h"

// ���� �� ���̴� ��� ������Ʈ���� ��ӹ��� Ŭ�����Դϴ�.
// �������� �ִ°� ���°��� ������.
// ��ġ�� ũ�Ⱑ �ʿ��ϴ�.
class CObj
{
protected : 
	CObj();
	virtual ~CObj();

protected : 
	// ��ġ�� ũ��
	POSITION		m_tPos;
	_PSIZE			m_tSize;
};

