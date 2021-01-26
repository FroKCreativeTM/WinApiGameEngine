#include "CMath.h"

float CMath::Distance(const POSITION& tPos1, const POSITION& tPos2)
{
	float x, y;
	x = tPos2.x - tPos1.x;
	y = tPos2.y - tPos1.y;

	return sqrtf(x * x + y * y);
}
