#version 120

uniform vec2 iResolution;
uniform mat4 inversedProjectionView;
uniform vec3 cameraPosition;
uniform float fractalParameter;

vec3 screenToWorld()
{
    // NORMALISED DEVICE SPACE
    float x = 2.0f*gl_FragCoord.x / iResolution.x - 1.0f;
    float y = 2.0f*gl_FragCoord.y / iResolution.y - 1.0f;

    // HOMOGENEOUS SPACE
    vec4 screenPos = vec4(x, -y, -1.0f, 1.0f);

    vec4 worldPos = screenPos * inversedProjectionView;
    return normalize(vec3(worldPos));
}

vec2 mandelbulb(vec3 position)
{
    //	float power = 3.0+4.0*(sin(10.0/30.0)+1.0);
    //	float3 z = position;
    //	float dr = 1.0f;
    //	float r = 0.0f;
    //
    //	for (int i = 0; i < 5; i++)
    //	{
    //		r = length(z);
    //		if (r > 2.0)
    //			break;
    //
    //		float theta = acos(z.z / r) * power;
    //		float phi = atan2 (z.y, z.x) * power;
    //		float zr = pow (r, power);
    //		dr = pow (r, power - 1.0f) * power * dr + 1.0f;
    //
    //		z = zr * float3(sin (theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
    //		z += position;
    //	}
    //	return (0.5 * log(r) * r / dr);


//    float power = mandelbulbPower+4.0*(sin(10.0/30.0)+1.0);
//    vec3 z = position;
//    float dr = 1.0f;
//    float r = 0.0f;
//
//    for (int i = 0; i < 16; i++)
//    {
//        r = length(z);
//        if (r > 1.5f)
//            break;
//
//        // convert to polar coordinates
//        float theta = acos(z.z/r);
//        float phi = atan(z.y*2.0f,z.x*2.0f);
//        dr =  pow( r, power-1.0f)*power*dr + 1.0f;
//
//        // scale and rotate the point
//        float zr = pow( r,power);
//        theta = theta*power;
//        phi = phi*power;
//
//        // convert back to cartesian coordinates
//        z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
//        z+=position;
//    }
//    return (0.5 * log(r) * r / dr);

    float Iterations = 64.;
    float Bailout = 2.;
    float Power = 6. - 4.*cos(fractalParameter/16.);

    vec3 trap = vec3(0,0,0);
    float minTrap = 1e10;

    vec3 z = position;
    float dr = 1.0;
    float r = 0.0;
    for (float i = 0.; i < Iterations ; i++) {
        r = length(z);
        if (r>Bailout) break;

        minTrap = min(minTrap, z.z);

        // convert to polar coordinates
        float theta = acos(z.z/r);
        float phi = atan(z.y,z.x);
        dr =  pow( r, Power-1.0)*Power*dr + 1.0;

        // scale and rotate the point
        float zr = pow( r,Power);
        theta = theta*Power;
        phi = phi*Power;

        // convert back to cartesian coordinates
        //z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
        z = zr*vec3( cos(theta)*cos(phi), cos(theta)*sin(phi), sin(theta) );
        z+=position;
    }
    return vec2(0.5*log(r)*r/dr, minTrap);
}

float boxDistance(vec3 currentMarchingLocation, vec3 position, vec3 size)
{
    vec3 offset = abs(currentMarchingLocation) - size;
    return length(max(offset, 0.0f)) + min(max(offset.x,max(offset.y,offset.z)),0.0f);
}

float sphereDistance(vec3 currentMarchingLocation, vec3 position, float radius)
{
    return (length(currentMarchingLocation - position) - radius);
}

vec2 getDistance(vec3 currentMarchingLocation)
{
//    float planeDistance = currentMarchingLocation.y;
//    float mandelbulb = mandelbulb(currentMarchingLocation);
    float sphereDistance = sphereDistance(currentMarchingLocation, vec3(0.0f, 0.0f, 0.0f), 0.01f);
//    float boxDistance = boxDistance(currentMarchingLocation, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
//    float distance = min(mandelbulb, sphereDistance);

    vec2 mandelbulb = mandelbulb(currentMarchingLocation);
    if (mandelbulb.x > sphereDistance)
        return vec2(sphereDistance, 0.0f);
    else
        return mandelbulb;

}

vec3 rayMarch(vec3 rayOrigin, vec3 rayDirection)
{
    float distanceFromOrigin = 0.0f;

    const int maxSteps = 500;
    const float maxDistance = 100.0f;
    const float minDistanceToSurface = 0.0001f;

    int steps = 0;
    for(; steps < maxSteps; steps++)
    {
        vec3 currentMarchingLocation = rayOrigin + rayDirection * distanceFromOrigin;
        vec2 distanceToScene = getDistance(currentMarchingLocation);
        distanceFromOrigin += distanceToScene.x;
        if(distanceToScene.x < minDistanceToSurface ||
        distanceFromOrigin > maxDistance)
            return vec3(distanceFromOrigin, steps, distanceToScene.y);
    }
    return vec3(0.0f);





//        const int maxSteps = 100;
//        const float maxDistance = 100.0f;
//        const float minDistanceToSurface = 0.01f;
//    float t = 0., i = 0.;
//    for(i=0.; i < maxSteps; i++) {
//        vec3 p = rayOrigin + t * rayDirection;
//        vec2 hit = getDistance(p);
//        float dt = hit.x;
//        t += dt;
//        if(dt < minDistanceToSurface) {
//            return vec3(t-minDistanceToSurface, 1.-i/maxSteps, hit.y);
//        }
//    }
//    return vec3(0.);






//    float tmin = 0.01f;
//    float tmax = 600.0f;
//    float stepSize = 1.0f;
//    float maxRayCasts = 128;
//    float precis = 0.01f;
//    vec2 res;
//
//    float t = tmin;
//    float m = -1.0f;
//    for( int i=0; i<maxRayCasts; i++ ) {
//        res = vec2(getDistance(rayOrigin+rayDirection*t));
//        if( abs(res.x)<precis || t>tmax ) break;
//        t += res.x*stepSize;
//        m = res.y;
//    }
//
//    if( t>tmax ) m=-1.0;
//    return t;
}

vec3 getNormal(vec3 location)
{
    const float epsilon = 0.001; // arbitrary — should be smaller than any surface detail in your distance function, but not so small as to get lost in float precision
    float centerDistance = getDistance(location).x;
    float xDistance = getDistance(location + vec3(epsilon, 0, 0)).x;
    float yDistance = getDistance(location + vec3(0, epsilon, 0)).x;
    float zDistance = getDistance(location + vec3(0, 0, epsilon)).x;
    vec3 normal = (vec3(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
    return normalize(normal);
}

// https://iquilezles.org/www/articles/palettes/palettes.htm
vec3 pal( float t, vec3 a, vec3 b, vec3 c, vec3 d ) {
    return a + b*cos(6.28318 * (c*t + d));
}

void main(void) {
//    vec2 uv = vec2(gl_FragCoord.x / iResolution.x, gl_FragCoord.y / iResolution.y);
    vec3 rayDirection = screenToWorld();
    vec3 distance = rayMarch(cameraPosition, rayDirection);
    vec3 normal = getNormal(rayDirection*distance.x+cameraPosition);
//    vec3 color = (vec3(0.0f) + vec3(distance.y/100.0f, 0.0f, distance.y/200.0f))/2.0f;
    float trap = fract(distance.z*.5 + .5);
    vec3 col = pal(trap, vec3(0.5), vec3(0.5), vec3(1.0,1.0,1.0), vec3(.0, .10, .2));
//    vec3 col = vec3(trap);
//    vec3 col = pal(trap, vec3(0.8, 0.5, 0.4), vec3(0.2, 0.4, 0.2), vec3(2.0, 1.0, 1.0), vec3(0.00, 0.25, 0.25));
//    col *= .2;
    col = (col + vec3(distance.y/100.0f, 0.0f, distance.y/200.0f))/2.0f;
    gl_FragColor = vec4(col, 1.0f);
}