#include "image.h"
#include "libft.h"
#include <mlx.h>

static void		t_image_set_pixel(t_image *this, cl_int2 point, int color)
{
	int	i;

	if (point.x >= this->geometry.x || point.x < 0 ||
		point.y >= this->geometry.y || point.y < 0)
		return ;
	i = (point.x * this->bpp / 8) + (point.y * this->stride);
	this->ptr[i] = (char)color;
	this->ptr[++i] = (char)(color >> 8);
	this->ptr[++i] = (char)(color >> 16);
}

static int		t_image_get_pixel(t_image *this, cl_int2 point)
{
	int i;
	int color;

	if (point.x > this->geometry.x || point.x < 0.0f ||
		point.y > this->geometry.y || point.y < 0.0f)
		return (0);
	color = 0;
	i = (point.x * this->bpp / 8) + (point.y * this->stride);
	color = *(int *)&this->ptr[i];
	return (color);
}

static void		t_image_clear(t_image *this)
{
	ft_bzero(this->ptr, (this->geometry.x *
						 this->geometry.y * (this->bpp / 8)));
}

t_image			*t_image_create(void *mlx, cl_uint2 geometry)
{
	t_image		*object;

	if (!(object = malloc(sizeof(t_image))))
	{
		write(1, "make_t_image: cannot allocate t_image struct.\n", 46);
		exit(1);
	}
	object->mlx = mlx;
	object->geometry = geometry;

	object->get_pixel = &t_image_get_pixel;
	object->set_pixel = &t_image_set_pixel;
	object->clear = &t_image_clear;
	object->image = mlx_new_image(mlx, (int)geometry.x, (int)geometry.y);
	if (!object->image)
	{
		write(1, "make_t_image: cannot create mlx image.\n", 39);
		exit(1);
	}
	object->ptr = mlx_get_data_addr(object->image, &(object->bpp),
									&(object->stride), &(object->endian));
	object->size = ((int)object->geometry.x * object->bpp / 8) + ((int)object->geometry.y * object->stride);
	return (object);
}

void			t_image_destroy(t_image *object)
{
	mlx_destroy_image(object->mlx, object->image);
	free(object);
}
