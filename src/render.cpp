#include <iostream>
#include <memory>

using std::cout;       using std::cerr;
using std::cin;        using std::endl;
using std::string;
using std::unique_ptr; using std::make_unique;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <shader.hpp>
#include <fractals/tree.hpp>
#include <fractals/petal.hpp>
#include <fractals/infinicube.hpp>
#include <fractals/sierpinski.hpp>
#include <camera.hpp>

// Available fractals and shaders
enum Fractals_e {
  tree, petal, infinicube, sierpinski
};

enum Shaders_e {
  simple, flat
};

// Auxiliary setup functions
void GLFWSetup(GLFWwindow **window);
void GLEWSetup();
void GLSetup(GLuint &vao, GLuint &program_id, unsigned int shader);

// Auxiliary cleanup function
void Cleanup(GLuint &vao, GLuint &program_id);

int main()
{
  // Get user input
  unsigned int fractal_op;
  unsigned int shader_op;
  unsigned int iterations;

  // Simple menu with fractal options
  cout << "\nAvailable Fractals:\n";
  cout << "\tTree       - 0\n";
  cout << "\tPetal      - 1\n";
  cout << "\tInfinicube - 2\n";
  cout << "\tSierpinski - 3\n";

  cout << "\nFractal to render: ";
  cin >> fractal_op;

  // Simple menu with shader options
  cout << "\nAvailable Shaders:\n";
  cout << "\tSimple     - 0\n";
  cout << "\tFlat       - 1\n";

  cout << "\nShader to use: ";
  cin >> shader_op;

  cout << "Number of iterations: ";
  cin >> iterations;

  // Initialize GLFW and GLEW
  GLFWwindow *window;

  try
  {
    GLFWSetup(&window);
    GLEWSetup();
  } catch(int e) {
    return e;
  }

  // Setup OpenGL, includes binding VAO and loading shaders
  GLuint vertex_array_id;
  GLuint program_id;
  GLSetup(vertex_array_id, program_id, shader_op);

  // Set up our camera
  Camera camera(program_id, 45.0f, 16.0f / 9.0f, 0.1f, 1000.0f,
    glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 5.0f, 0.0f));

  // Build desired fractal
  unique_ptr<Fractal> fractal;
  switch(fractal_op)
  {
  case tree:
    fractal = make_unique<Tree>(iterations);
    break;
  case petal:
    fractal = make_unique<Petal>(iterations);
    break;
  case infinicube:
    fractal = make_unique<Infinicube>(iterations);
    break;
  case sierpinski:
    fractal = make_unique<Sierpinski>(iterations);
    break;
  default:
    fractal = make_unique<Tree>(iterations);
  }
  fractal->BindToVAO();

  // Begin rendering loop
  double last_time = glfwGetTime();
  do {
    // Get delta time
    double curr_time  = glfwGetTime();
    float  delta_time = float(curr_time - last_time);

    // Rotate camera
    camera.rotate_origin(delta_time);

    // Draw our current batch
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(fractal->get_mode(), 0, fractal->get_elements());

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    last_time = curr_time;
  // Check if the ESC key was pressed or the window was closed
  } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(window) == 0);

  return 0;
}

void GLFWSetup(GLFWwindow **window)
{
  // Initialize GLFW
  if(!glfwInit())
  {
    cerr << "Failed to initialize GLFW" << endl;

    throw -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  *window = glfwCreateWindow(1600, 900, "Fractals", NULL, NULL);

  if(*window == NULL)
  {
    cerr << "Failed to open GLFW window. "
      "If you have an Intel GPU, "
      "they are not 3.3 compatible" << endl;
    glfwTerminate();

    throw -1;
  }

  glfwMakeContextCurrent(*window);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
}

void GLEWSetup()
{
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile

  if(glewInit() != GLEW_OK)
  {
    cerr << "Failed to initialize GLEW." << endl;
    glfwTerminate();

    throw -1;
  }
}

void GLSetup(GLuint &vao, GLuint &program_id, unsigned int shader)
{
  // Enable depth test, accept if fragment is closer to camera
  // than the former one
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Enable culling
  glEnable(GL_CULL_FACE);

  // Enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Generate and bind our VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create and compile our GLSL program from the shaders
  string vert_src;
  string geom_src;
  string frag_src;
  switch(shader)
  {
  case simple:
    vert_src = "../assets/shaders/simple/fractals.vert";
    frag_src = "../assets/shaders/simple/fractals.frag";
    break;
  case flat:
    vert_src = "../assets/shaders/flat/fractals.vert";
    geom_src = "../assets/shaders/flat/fractals.geom";
    frag_src = "../assets/shaders/flat/fractals.frag";
    break;
  default:
    vert_src = "../assets/shaders/simple/fractals.vert";
    frag_src = "../assets/shaders/simple/fractals.frag";
  }

  program_id = LoadShaders(
    vert_src,
    geom_src,
    frag_src
  );

  // Use our shader
  glUseProgram(program_id);
}

void Cleanup(GLuint &vao, GLuint &program_id)
{
  // Cleanup VBO and shader
  glDeleteProgram(program_id);
  glDeleteVertexArrays(1, &vao);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}
