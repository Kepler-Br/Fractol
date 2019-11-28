#ifndef IMAGE_H
#define IMAGE_H

#include <OpenCL/cl.h>

typedef struct						s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
	cl_uint2		geometry;
	void			*mlx;
	int				size;

	void			(*set_pixel)(struct s_image *this, cl_int2 pos, int color);
	int				(*get_pixel)(struct s_image *this, cl_int2 pos);
	void			(*clear)(struct s_image *this);
} t_image;

t_image						*t_image_create(void *mlx, cl_uint2 geometry);
void						t_image_destroy(t_image *object);

#endif
