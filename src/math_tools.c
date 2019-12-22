#include "linear_alg.h"

float   lerpf(float source, float target, float t)
{
    return ((1.0f - t) * source + t * target);
}

t_vec3   lerpvec3(t_vec3 source, t_vec3 target, float t)
{
    return (t_vec3){(1.0f - t) * source.x + t * target.x,
                    (1.0f - t) * source.y + t * target.y,
                    (1.0f - t) * source.z + t * target.z};
}