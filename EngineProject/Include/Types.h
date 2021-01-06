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

// 오브젝트들의 위치를 표현하기 위한 것입니다.
// 2D니까 x, y만
typedef struct _tagPosition
{
	float x, y; // 정확한 이동 경로를 만들기 위해서 float를 사용한다.

	/* 위치 생성자 파트입니다. */
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

	/* 덧셈 */
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

	/* 뺄셈 */
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

	/* 곱셈 */
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

	/* 나눗셈 */
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