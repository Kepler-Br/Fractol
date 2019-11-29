void            set_pixel_flat(int position, __global char *A, int color);
int             rgb_to_int(float3 rgb);
float3 screenToWorld(float2 fragCoord, float2 iResolution, float16 *inversedPV);
float4 float16_float4_mul(float16 *mat, float4 *vec);
float rayMarch(float3 rayOrigin, float3 rayDirection);
float getDistance(float3 currentMarchingLocation);
float3 getNormal(float3 location);
float getDiffuse(float3 position, float3 lightPosition);
float mandelbulb(float3 position);

void	set_pixel_flat(int position, __global char *A, int color)
{
	int bpp = 32;
	int stride = 4000;
	int geometry_x = 1000;
	int geometry_y = 1000;
	int i = i = (position%geometry_x * bpp / 8) + (position/geometry_y * stride);
	A[i] = (char)color;
	A[i+1] = (char)(color >> 8);
	A[i+2] = (char)(color >> 16);
}

int		rgb_to_int(float3 rgb)
{
	int r = clamp(rgb.x, 0.0f, 1.0f) * 255.0f;
	int g = clamp(rgb.y, 0.0f, 1.0f) * 255.0f;
	int b = clamp(rgb.z, 0.0f, 1.0f) * 255.0f;
	int color = (int)((int)(r << 16) | (int)(g << 8) | (int)(b));

	return (color);
}

float mandelbulb(float3 position)
{
	float power = 1.0f;
	float3 z = position;
	float dr = 1.0f;
	float r;

	for (int i = 0; i < 15; i++)
	{
		r = length(z);
		if (r > 2.0f)
			break;

		float theta = acos(z.z / r) * power;
		float phi = atan2 (z.y, z.x) * power;
		float zr = pow (r, power);
		dr = pow (r, power - 1.0f) * power * dr + 1.0f;

		z = zr * float3(sin (theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
		z += position;
	}
	return (0.5f * log(r) * r / dr);
}

float3	screenToWorld(float2 fragCoord, float2 iResolution, float16 *inversedPV)
{
	// Normalized device space.
	float x = 2.0f * fragCoord.x / iResolution.x - 1.0f;
	float y = 2.0f * fragCoord.y / iResolution.y - 1.0f;

	// Homogeneous space.
	float4 screenPos = (float4)(x, -y, -1.0f, 1.0f);

	float4 worldPos = float16_float4_mul(inversedPV, &screenPos);
	return (normalize((float3)(worldPos.xyz)));
}

float4	float16_float4_mul(float16 *mat, float4 *vec)
{
	float4 new_vec;
	new_vec.x = mat->s0 * vec->x + mat->s1 * vec->y + mat->s2 * vec->z +
				mat->s3 * vec->w;
	new_vec.y = mat->s4 * vec->x + mat->s5 * vec->y + mat->s6 * vec->z +
				mat->s7 * vec->w;
	new_vec.z = mat->s8 * vec->x + mat->s9 * vec->y + mat->sa * vec->z +
				mat->sb * vec->w;
	new_vec.w = mat->sc * vec->x + mat->sd * vec->y + mat->se * vec->z +
				mat->sf * vec->w;
	return (new_vec);
}

float3	getNormal(float3 location)
{
	const float epsilon = 0.001f;
	float centerDistance = getDistance(location);
	float xDistance = getDistance(location + (float3)(epsilon, 0.0f, 0.0f));
	float yDistance = getDistance(location + (float3)(0.0f, epsilon, 0.0f));
	float zDistance = getDistance(location + (float3)(0.0f, 0.0f, epsilon));
	float3 normal = ((float3)(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
	return (normalize(normal));
}

float	getDiffuse(float3 position, float3 lightPosition)
{
	float3 lightVector = normalize(lightPosition - position);
	float3 pointNormal = getNormal(position);

	float diffuse = dot(pointNormal, lightVector);

	float light = rayMarch(position+pointNormal*0.01f, lightPosition);
	if (light < length(lightPosition-position))
		diffuse *= 0.8f;
	return (diffuse);
}

float	getDistance(float3 currentMarchingLocation)
{
//	float planeDistance = currentMarchingLocation.y;
	float planeDistance = mandelbulb(currentMarchingLocation);
	float sphereRadius = 5.0f;
	float3 floatPosition = (float3)(0.0f, 0.0f, 0.0f);
	float sphereDistance = length(currentMarchingLocation - floatPosition) - sphereRadius;
	float distance = min(sphereDistance, planeDistance);
	return (distance);
}

float	rayMarch(float3 rayOrigin, float3 rayDirection)
{
	float distanceFromOrigin = 0.0f;

	const int maxSteps = 1000;
	const float maxDistance = 100.0f;
	const float minDistanceToSurface = 0.01f;

	for (int i = 0; i < maxSteps; i++)
	{
		float3 currentMarchingLocation = rayOrigin + rayDirection * distanceFromOrigin;
		float distanceToScene = getDistance(currentMarchingLocation);
		distanceFromOrigin += distanceToScene;
		if (distanceFromOrigin < minDistanceToSurface ||
		distanceFromOrigin > maxDistance)
			break;
	}
	return (distanceFromOrigin);
}

__kernel
void	main_image(__global char *image, float2 iResolution, float16 inversePV, float3 cameraPosition)
{
	int flat = get_global_id(0);
	float2 fragCoord = (float2)(flat % (int)iResolution.x, flat / iResolution.y);
//	float2 uv = fragCoord/(float2)(iResolution.xy);
	float3 rayDirection = screenToWorld(fragCoord, iResolution, &inversePV);
	float distance = rayMarch(cameraPosition, rayDirection);
	float3 lightPosition = (float3)(0.0f, 20.0f, 0.0f);
	float diffuse = getDiffuse(rayDirection*distance+cameraPosition, lightPosition);
	int color = rgb_to_int((float3)(diffuse));
	set_pixel_flat(flat, image, color);
}
