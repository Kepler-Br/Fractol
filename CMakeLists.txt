cmake_minimum_required(VERSION 3.14)
project(fractol_reloaded C)

set(CMAKE_C_STANDARD 90)

INCLUDE_DIRECTORIES(libft)
INCLUDE_DIRECTORIES(includes)
LINK_DIRECTORIES(libft)
add_executable(fractol_reloaded src/main.c src/main_loop.c includes/main_loop.h includes/state.h includes/mlx_instance.h includes/raymarch_state.h src/raymarch_state.c includes/mlx_keys.h includes/opencl_instance.h src/opencl_instance.c includes/tools.h src/tools.c includes/image.h src/image.c includes/linear_alg.h src/linear_alg.c includes/shader.h src/shader.c includes/vertex_buffer.h)
find_library(OPENCL_UNIT OpenCL)
target_link_libraries(fractol_reloaded mlx ft)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_link_libraries(fractol_reloaded ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OPENCL_UNIT})