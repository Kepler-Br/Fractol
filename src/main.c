#include "main_loop.h"
#include "raymarch_state.h"
#include "julia_state.h"
#include "linear_alg.h"


int main()
{
	t_main_loop *main_loop = t_main_loop_create("Fract'ol", (t_ivec2){1000, 1000});
	t_state *raymarch_state = t_raymarch_state_create(main_loop->mlx_instance, "./programs/menger.glsl");
	main_loop->state = raymarch_state;
//    t_state *julia_state = t_julia_state_create(main_loop->mlx_instance, "./programs/julia.glsl");
//    main_loop->state = julia_state;
	main_loop->run(main_loop);
	return 0;
}