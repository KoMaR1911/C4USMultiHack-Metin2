#pragma once

class MathExtension
{
public:
	static bool PointInCircle(D3DVECTOR posA, D3DVECTOR posB, float r)
	{
		return (posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y) < r * r;
	}
};
