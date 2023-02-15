#include <iostream>
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "SpriteRenderer.h"
#include "Camera.h"

using namespace RenderMe::Base;
using namespace RenderMe::RenderMe2D;

int main()
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();
    Scene scene = Scene();
    Entity entity = scene.addEntity();
    TransformComponent tran;
    tran.x_position = 0;
    tran.y_position = 0;
    tran.x_scale = 1;
    tran.y_scale = 1;
    char* message = new char;
     scene.getShadersManager()->compileShader(message,"Hello",GL_VERTEX_SHADER,"D:\\Dev\\VS projects\\RenderMe Project\\x64\\Debug\\vertexShader.txt");
    Camera cam = Camera(&scene,0,0,0,0,0,0);
    
    while (!glfwWindowShouldClose(window))
    {

       
        cam.render();



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    
    }

    glfwTerminate();
    return 0;

}