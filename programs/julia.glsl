#version 120

uniform vec2 iResolution;
uniform vec2 cameraPosition;
uniform float zoom;
uniform vec2 juliaParameters;
uniform vec3 colPal[4];
uniform float paletteShift;

float  julia_distance(vec2 c, vec2 z)
{
    float di = 1.0;
    vec2 dz = vec2(1.0, 0.0);
    vec2 new_dz;
    vec2 new_z;
    float m2;
    for(int i = 0; i < 300; i++)
    {
        new_z = vec2(z.x*z.x - z.y*z.y, z.x*z.y + z.y*z.x) + c;
        new_dz = 2.0 * vec2(z.x*dz.x - z.y*dz.y, z.x*dz.y + z.y*dz.x);
        z = new_z;
        dz = new_dz;
        m2 = dot(z, z);
        if (m2 > 300.0)
        {
            di = 0.0;
            break;
        }
    }
    if (di > 0.5)
    return (0.0);
    else
    return (sqrt(m2 / dot(dz, dz)) * 0.5 * log(m2));
}

vec3 pal( float t, vec3 a, vec3 b, vec3 c, vec3 d ) {
    return a + b*cos(6.28318 * (c*t + d));
}

void main(void) {
    vec2 uv = gl_FragCoord.xy/iResolution;
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / iResolution.xy;
    p.x *= iResolution.x/iResolution.y;

    float tz = 0.5 - 0.5*zoom;
    float zoo = pow (0.5, 13.0 * tz);
    //      double2 c = (double2)(-0.05f, 0.6805f) + p*zoo;
    //      double2 c = (*i_position) + p*zoo;
    vec2 c = cameraPosition + p*zoo;

    float d = julia_distance(vec2(juliaParameters.x, juliaParameters.y), c);
    //      double d = julia_distance((double2)(cos(*i_time), 0.745), c);

    d = clamp( pow(4.0*d,0.2), 0.0, 1.0);
    vec3 col;
    if (d == 0.0)
        col = vec3(0.0f);
    else if (d != 0.0)
//        hsv = vec3((cos(d+777*3)+1.0)/2.0*360.0, 1.0, 1.0);
        col = pal(cos(d + paletteShift), colPal[0], colPal[1], colPal[2], colPal[3]);


//    vec2 rgb = hsv_to_rgb(hsv);
    gl_FragColor = vec4(col, 1.0f);
}