#pragma once

/* 매크로 단점! 디버깅이 안 된다! */
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }

// 클래스를 싱글톤으로 자동 생성한다.
#define DECLARE_SINGLE(Type) \
private : \
	static Type*	m_pInst;\
public: \
	static Type* GetInst()\
	{\
		if(!m_pInst)\
		{\
			m_pInst = new Type;\
		}\
		return m_pInst;\
	}\
static void DestroyInst()\
{\
	SAFE_DELETE(m_pInst);\
}\
private : \
	Type();\
	~Type();

// 싱글톤 객체를 NULL로 초기화 정의한다.
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL; 
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()