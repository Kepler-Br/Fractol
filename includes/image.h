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
	cl_int2			geometry;
	void			(*set_pixel)(struct s_image *this, cl_int2 pos, int color);
	int				(*get_pixel)(struct s_image *this, cl_int2 pos);
	void			(*clear)(struct s_image *this);
} t_image;

t_image						*make_t_image(void *mlx, cl_int2 geometry);
void						destroy_t_image(t_image *object, void *mlx);

#endif
