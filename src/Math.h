#pragma once
class Math
{
public:
	static float PI() { return 3.1415927f; }
	static float Epsilon() { return 1e-6f; }
	static float ToRadian(float degree) { return degree * PI() / 180.0f; }
	static float ToDegree(float radian) { return radian * 180.0f / PI(); }
};