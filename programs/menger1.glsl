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

float sdBox(vec3 currentMarchingLocation, vec3 position, vec3 size)
{
    vec3 offset = abs(currentMarchingLocation) - size;
    return length(max(offset, 0.0f)) + min(max(offset.x,max(offset.y,offset.z)),0.0f);
}

float sdCross(vec3 position)
{
//    float da = sdBox(position.xy,vec3(1.0));
//    float db = sdBox(position.yz,vec3(1.0));
//    float dc = sdBox(position.zx,vec3(1.0));
//    return min(da,min(db,dc));
    return 0.0f;
}

// http://www.iquilezles.org/www/articles/menger/menger.htm
float menger(vec3 position)
{
    float d = sdBox(position, vec3(1.0f), vec3(0.01f));
//    float c = sdCross(p*3.0f)/3.0f;
//    d = max(d, -c);
    return d;
}



float sphereDistance(vec3 currentMarchingLocation, vec3 position, float radius)
{
    return (length(currentMarchingLocation - position) - radius);
}

float getDistance(vec3 currentMarchingLocation)
{
    //    float planeDistance = currentMarchingLocation.y;
    //    float mandelbulb = mandelbulb(currentMarchingLocation);
    float sphereDistance = sphereDistance(currentMarchingLocation, vec3(0.0f, 0.0f, 0.0f), 0.01f);
    //    float boxDistance = boxDistance(currentMarchingLocation, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
    //    float distance = min(mandelbulb, sphereDistance);

    float menger = menger(currentMarchingLocation);
    if (menger > sphereDistance)
    return sphereDistance;
    else
    return menger;

}

vec2 rayMarch(vec3 rayOrigin, vec3 rayDirection)
{
    float distanceFromOrigin = 0.0f;

    const int maxSteps = 500;
    const float maxDistance = 100.0f;
    const float minDistanceToSurface = 0.0001f;

    int steps = 0;
    for(; steps < maxSteps; steps++)
    {
        vec3 currentMarchingLocation = rayOrigin + rayDirection * distanceFromOrigin;
        float distanceToScene = getDistance(currentMarchingLocation);
        distanceFromOrigin += distanceToScene;
        if(distanceToScene < minDistanceToSurface ||
        distanceFromOrigin > maxDistance)
        return vec2(distanceFromOrigin, steps);
    }
    return vec2(0.0f);
}

vec3 getNormal(vec3 location)
{
    const float epsilon = 0.00001f; // arbitrary — should be smaller than any surface detail in your distance function, but not so small as to get lost in float precision
    float centerDistance = getDistance(location);
    float xDistance = getDistance(location + vec3(epsilon, 0, 0));
    float yDistance = getDistance(location + vec3(0, epsilon, 0));
    float zDistance = getDistance(location + vec3(0, 0, epsilon));
    vec3 normal = (vec3(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
    return normalize(normal);
}

float getDiffuse(vec3 position, vec3 lightPosition)
{
    vec3 lightVector = normalize(lightPosition-position);
    vec3 pointNormal = getNormal(position);

    float diffuse = dot(pointNormal, lightVector);

    vec2 light = rayMarch(position+pointNormal*0.01f, lightPosition);
    if(light.x < length(lightPosition-position))
    diffuse *= 0.8f;
    return diffuse;
}

// https://iquilezles.org/www/articles/palettes/palettes.htm
vec3 pal( float t, vec3 a, vec3 b, vec3 c, vec3 d ) {
    return a + b*cos(6.28318 * (c*t + d));
}

vec3 light = vec3(10.0,10.9,10.3);

void main(void) {
    vec3 rayDirection = screenToWorld();
    vec2 distance = rayMarch(cameraPosition, rayDirection);
    vec3 normal = getNormal(rayDirection*distance.x+cameraPosition);
    vec3 col = vec3(distance.y/100.0f, 0.0f, distance.y/200.0f);
    float diffuse = getDiffuse(rayDirection*distance.x+cameraPosition, light);
    col += mix(vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 0.1f, 0.5f), diffuse);
    gl_FragColor = vec4(col, 1.0f);
}