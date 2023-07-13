#pragma once
#include <math.h>

# define M_PI  3.14159265358979323846  /* pi */

class Vector3 {
public:

	float x, y, z;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	float magnitude(Vector3 target);
	float yawAngle(Vector3 target);
	float pitchAngle(Vector3 target);
};