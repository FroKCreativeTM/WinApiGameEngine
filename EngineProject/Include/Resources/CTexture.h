#pragma once

#include "../Core/CRef.h"

class CTexture : 
	public CRef
{
private : 
	// �� �����ڸ� �ؽ�ó ���� ����
	friend class CResourceManager;

private : 
	CTexture();
	~CTexture();
};

