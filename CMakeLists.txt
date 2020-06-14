cmake_minimum_required (VERSION 2.6)

cmake_policy(SET CMP0072 NEW)

project (fractals)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} src)

add_executable(fractals
  src/render.cpp
  src/shader.cpp
  src/shader.hpp
  src/camera.cpp
  src/camera.hpp
  src/fractals/fractal.hpp
  src/fractals/fractal.cpp
  src/fractals/tree.cpp
  src/fractals/tree.hpp
  src/fractals/petal.hpp
  src/fractals/petal.cpp
  src/fractals/infinicube.cpp
  src/fractals/infinicube.hpp
  src/fractals/sierpinski.cpp
  src/fractals/sierpinski.hpp
  src/shapes/shape.hpp
  src/shapes/shape.cpp
  src/shapes/cube.cpp
  src/shapes/cube.hpp
  src/shapes/pyramid.cpp
  src/shapes/pyramid.hpp
  )

target_link_libraries(fractals glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
