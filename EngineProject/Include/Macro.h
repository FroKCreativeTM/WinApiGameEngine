#pragma once

/* ��ũ�� ����! ������� �� �ȴ�! */
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }

// Ŭ������ �̱������� �ڵ� �����Ѵ�.
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

// �̱��� ��ü�� NULL�� �ʱ�ȭ �����Ѵ�.
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL; 
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()

// �ػ󵵸� ������ ��ũ��
#define GET_RESOLUTION		CCore::GetInst()->GetResolution()
// ������ �ڵ� ��������
#define GET_WINDOWHANDLE	CCore::GetInst()->GetWindowHandle()
 
#define KEYDOWN(key)	CInput::GetInst()->KeyDown(key)
#define KEYPRESS(key)	CInput::GetInst()->KeyPress(key)
#define KEYUP(key)		CInput::GetInst()->KeyUp(key)