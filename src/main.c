#include "main_loop.h"
#include "raymarch_state.h"
#include "linear_alg.h"

void print_float16(cl_float16 m)
{
	int i;

	i = 0;
	while (i < 16)
	{
		printf("%f ", m.s[i]);
		if ((i + 1) % 4 == 0 && i != 0)
			write(1, "\n", 1);
		i++;
	}
}
int main()
{
	t_main_loop *main_loop = t_main_loop_create("Fract'ol", (cl_uint2){1000, 1000});
	t_state *raymarch_state = t_raymarch_state_create(main_loop->mlx_instance);
	main_loop->state = raymarch_state;
	main_loop->run(main_loop);
	return 0;
}