void            set_pixel_flat(int position, __global char *A, int color);
int             rgb_to_int(double3 rgb);

void            set_pixel_flat(int position, __global char *A, int color)
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

int     rgb_to_int(double3 rgb)
{
	int r = clamp(rgb.x, 0.0, 1.0) * 255.0;
	int g = clamp(rgb.y, 0.0, 1.0) * 255.0;
	int b = clamp(rgb.z, 0.0, 1.0) * 255.0;
	int color = (int)((int)(r << 16) | (int)(g << 8) | (int)(b));

	return (color);
}

__kernel
void	main_image(__global char *image, int color)
{
	int flat = get_global_id(0);
	//int color;
	//color = rgb_to_int((double3)(1.0, 0.0, 1.0));
	set_pixel_flat(flat, image, color);
}
