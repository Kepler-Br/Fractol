#ifndef MLX_INSTANCE_H
#define MLX_INSTANCE_H

#import "linear_alg.h"

typedef struct	s_mlx_instance
{
	void		*mlx;
	void		*window;
	t_ivec2 	window_geometry;
}				t_mlx_instance;

#endif
