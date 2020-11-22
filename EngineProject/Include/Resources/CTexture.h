#pragma once

#include "../Core/CRef.h"

class CTexture : 
	public CRef
{
private : 
	// 이 관리자만 텍스처 생성 가능
	friend class CResourceManager;

private : 
	CTexture();
	~CTexture();
};

