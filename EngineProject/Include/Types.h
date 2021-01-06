#pragma once

typedef struct _tagResolution
{
	unsigned int nWidth;
	unsigned int nHeight;

	_tagResolution() : 
		nWidth(0), nHeight(0)	{}

	_tagResolution(int x, int y) : 
		nWidth(x), nHeight(y)	{}
}RESOLUTION, *PRESOLUTION;

// ������Ʈ���� ��ġ�� ǥ���ϱ� ���� ���Դϴ�.
// 2D�ϱ� x, y��
typedef struct _tagPosition
{
	float x, y; // ��Ȯ�� �̵� ��θ� ����� ���ؼ� float�� ����Ѵ�.

	/* ��ġ ������ ��Ʈ�Դϴ�. */
	_tagPosition() : x(0.f), y(0.f) {}
	_tagPosition(float x, float y) : x(x), y(y) {}
	_tagPosition(const _tagPosition& ref) : x(ref.x), y(ref.y) {}
	_tagPosition(const POINT& ref) : x(ref.x), y(ref.y) {}

	void operator= (const _tagPosition& ref)
	{
		x = ref.x;
		y = ref.y;
	}

	void operator= (const POINT& ref)
	{
		x = ref.x;
		y = ref.y;
	}

	void operator= (float f[2])
	{
		x = f[0];
		y = f[1];
	}

	/* ���� */
	_tagPosition operator+(const _tagPosition& ref) const
	{
		_tagPosition tPos;
		tPos.x = x + ref.x;
		tPos.y = y + ref.y;
		return tPos;
	}

	_tagPosition operator+(const POINT& ref) const
	{
		_tagPosition tPos;
		tPos.x = x + ref.x;
		tPos.y = y + ref.y;
		return tPos;
	}

	_tagPosition operator+(float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}

	_tagPosition operator+(float f) const 
	{
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	void operator+=(const _tagPosition& ref)
	{
		x += ref.x;
		y += ref.y;
	}

	/* ���� */
	_tagPosition operator-(const _tagPosition& ref) const
	{
		_tagPosition tPos;
		tPos.x = x - ref.x;
		tPos.y = y - ref.y;
		return tPos;
	}

	_tagPosition operator-(const POINT& ref) const
	{
		_tagPosition tPos;
		tPos.x = x - ref.x;
		tPos.y = y - ref.y;
		return tPos;
	}

	_tagPosition operator-(float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator-(float f) const
	{
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	void operator-=(const _tagPosition& ref)
	{
		this->x = x - ref.x;
		this->y = y - ref.y;
	}

	/* ���� */
	_tagPosition operator*(const _tagPosition& ref) const
	{
		_tagPosition tPos;
		tPos.x = x * ref.x;
		tPos.y = y * ref.y;
		return tPos;
	}

	_tagPosition operator*(const POINT& ref) const
	{
		_tagPosition tPos;
		tPos.x = x * ref.x;
		tPos.y = y * ref.y;
		return tPos;
	}

	_tagPosition operator*(float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator*(float f) const
	{
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}

	/* ������ */
	_tagPosition operator/(const _tagPosition& ref) const
	{
		_tagPosition tPos;
		tPos.x = x / ref.x;
		tPos.y = y / ref.y;
		return tPos;
	}

	_tagPosition operator/(const POINT& ref) const
	{
		_tagPosition tPos;
		tPos.x = x / ref.x;
		tPos.y = y / ref.y;
		return tPos;
	}

	_tagPosition operator/(float f[2]) const
	{
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator/(float f) const
	{
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}

}POSITION, *PPOSITION, _SIZE, *_PSIZE;

typedef struct _tagRectangle
{
	float left;
	float top;
	float right;
	float bottom;

	_tagRectangle() : 
		left(0.0f), top(0.0f), right(0.0f), bottom(0.0f)
	{}
}RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere
{
	POSITION tCenter;
	float fRadius;

	_tagSphere() :
		tCenter(0.f, 0.f), fRadius(0.f)
	{}

}SPHERE, *PSPHERE;