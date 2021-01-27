#pragma once

#include "../Core/CRef.h"
#include "../Collider/CCollider.h"

class CScene;
class CLayer;

// ���� �� ���̴� ��� ������Ʈ���� ��ӹ��� Ŭ�����Դϴ�.
// �������� �ִ°� ���°��� ������.
// ��ġ�� ũ�Ⱑ �ʿ��ϴ�.

// CRef : ���۷��� ī���͸� ����ϴ� ����̴�.
class CObj : 
	public CRef
{
public : 
	/* Setter */
	void SetPos(const POSITION& ref)
	{
		this->m_tPos = ref;
	}

	void SetPos(float x, float y)
	{
		this->m_tPos.x = x;
		this->m_tPos.y = y;
	}

	void SetSize(const _SIZE& ref)
	{
		this->m_tSize = ref;
	}

	void SetSize(float x, float y)
	{
		this->m_tSize.x = x;
		this->m_tSize.y = y;
	}

	void SetScene(class CScene* pScene)
	{
		this->m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		this->m_pLayer = pLayer;
	}

	void SetPivot(const _SIZE& ref)
	{
		this->m_tPivot = ref;
	}

	void SetPivot(float x, float y)
	{
		this->m_tPivot.x = x;
		this->m_tPivot.y = y;
	}

	void SetPhysics(bool bPhysics)
	{
		m_bPhysics = bPhysics;
	}

	void SetImageOffset(const _SIZE& tOffset)
	{
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x, float y)
	{
		m_tImageOffset.x = x;
		m_tImageOffset.y = y;
	}

	/* Getter */
	CCollider* GetCollider(const string& strTag);

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE GetSize() const
	{
		return m_tSize;
	}

	_SIZE GetPivot() const
	{
		return m_tPivot;
	}

	float GetLeft() const
	{
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}

	float GetRight() const
	{
		return GetLeft() + m_tSize.x ;
	}

	float GetTop() const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}

	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}

	POSITION GetCenter() const
	{
		return POSITION(GetLeft() + m_tSize.x / 2.f,
			GetTop() + m_tSize.y / 2.f);
	}

	class CScene* GetScene() const
	{
		return m_pScene;
	}

	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}

	// ����Ʈ �����͸� �ѱ��.
	const list<CCollider*>* GetColliderList() const
	{
		return &m_ColliderList;
	}

	bool GetPhysics() const
	{
		return m_bPhysics;
	}

/* ���� ��Ҹ� ���� �޼ҵ� */
public : 	
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0;
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public : 
	void SaveFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void SaveFromFullPath(const char* pFullPath);
	void LoadFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void LoadFromFullPath(const char* pFullPath);

// ������Ʈ �ڷ� �ٷ�� 
public :
	static void AddObj(CObj* pObj);
	static CObj* FindObj(const string& strTag);
	static void EraseObj();	// ��ü
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);

// �ؽ��� ����
public : 
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = nullptr,
		const string& strPathKey = TEXTURE_PATH);

// �ִϸ��̼� ���� �޼���
public : 
	class CAnimation* CreateAnimation(const string& strTag);
	// ��Ʋ�� �ִϸ��̼ǿ�
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
		int nLengthX, int nLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	// ������ �ִϸ��̼ǿ�
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
		int nLengthX, int nLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring>& vecFileName,
		const string& strPathKey = TEXTURE_PATH);

	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned b);

public:
	// ������ �پ��� Ÿ���� ������Ʈ�� ����� ���� 
	// ���ø� Ÿ���� �޼ҵ��̴�.
	template <typename T>
	static T* CreateObj(const string& strTag,
		class CLayer* pLayer = nullptr);
	// ������ ������Ÿ���� ���縦 �����Ѵ�.
	// ���ø����� ���� ������ ����.
	static CObj* CreateCloneObj(const string& strProtoKey,
		const string& strTag, 
		SCENE_CREATE sc,
		class CLayer* pLayer = nullptr);
	template <typename T>
	void AddCollisionFunction(const string& strTag,
		COLLISION_STATE eState, T* pObj,
		void(T::* pFunc)(CCollider*, CCollider*, float));

public:
	template <typename T>
	T* AddCollider(const string& strTag)
	{
		// �浹ü�� �����ϰ� �� �浹ü�� ���� ������Ʈ�� ������ �����Ѵ�
		T* pCollider = new T;
		pCollider->SetObj(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return nullptr;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;
	}

	bool CheckCollider()
	{
		// �浹�� �ֳ������� �˻��Ѵ�.
		return !m_ColliderList.empty();
	}

	void ClearGravity()
	{
		m_fGravityTime = 0.f;
	}


protected :
	CObj();
	CObj(const CObj& ref);
	virtual ~CObj();

protected :
	// ��ġ�� ũ��
	POSITION				m_tPos;
	_SIZE					m_tSize;
	_SIZE					m_tImageOffset;		// ������? ���� ���ϴ� Ư�� ��ǥ����ŭ ����Ѵ�.
	POSITION				m_tPivot;
	// �ؽ�ó ����
	class CTexture*			m_pTexture;
	// �浹ü�� ���� ����
	list<CCollider*>		m_ColliderList;
	// �������� ���� �޴� ��ü�δ�.
	bool					m_bPhysics;
	// �߷� �ð���
	float					m_fGravityTime;
	// ������Ʈ�� �ִϸ��̼� ������ ���� Ŭ����
	class CAnimation*		m_pAnimation;

protected:
	// �ڱⰡ ���� ���� ���̾ �˰� �Ѵ�.
	class CScene* m_pScene;
	class CLayer* m_pLayer;

protected : 
	friend class CScene;

private : 
	// �����Ǵ� ��� ������Ʈ���� ���⼭ ����ȴ�.
	// �� ���̾ ��ġ�Ǹ鼭 ���ÿ� ���⿡ ���´ٴ� ���̴�.
	// (���� ��ġ��)
	static list<CObj*>	m_ObjList;


};

#include "CObj.inl"