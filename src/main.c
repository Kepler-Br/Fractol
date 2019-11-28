#include "main_loop.h"

int main()
{
	t_main_loop *main_loop = t_main_loop_create("Test test", (cl_uint2){1000, 1000}, NULL);
	main_loop->run(main_loop);
	return 0;
}