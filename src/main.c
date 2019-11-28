#include "main_loop.h"
#include "raymarch_state.h"

int main()
{
	t_state *raymarch_state = t_raymarch_state_create();
	t_main_loop *main_loop = t_main_loop_create("Test test", (cl_uint2){1000, 1000}, raymarch_state);
	main_loop->run(main_loop);
	return 0;
}