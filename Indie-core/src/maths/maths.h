#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#define _USE_MATH_DEFINES

#include <math.h>

inline float toRadians(float degrees)
{
	return (float)(degrees * M_PI / 180.0f);
}