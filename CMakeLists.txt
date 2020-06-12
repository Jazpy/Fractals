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
  src/fractal.hpp
  src/fractal.cpp
  src/shape.hpp
  src/shape.cpp
  src/tree.cpp
  src/tree.hpp
  src/petal.hpp
  src/petal.cpp
  src/infinicube.cpp
  src/infinicube.hpp
  src/camera.cpp
  src/camera.hpp
  src/cube.cpp
  src/cube.hpp
  )

target_link_libraries(fractals glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
