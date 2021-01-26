#include "CRef.h"

CRef::CRef() : 
	m_nRef(1),
	m_bEnable(true),
	m_bLife(true)
{
}

CRef::~CRef()
{
}
