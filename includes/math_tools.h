#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

#include <OpenGL/gl.h>
#include "linear_alg.h"

float   lerpf(float source, float target, float t);
t_vec3  lerpvec3(t_vec3 source, t_vec3 target, float t);
#endif
