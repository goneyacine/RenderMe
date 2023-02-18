#include <iostream>
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "ErrorHandler.h"
#include <chrono>

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

      Texture t = Texture(100,100,0);
    unsigned int vertexShader = scene.getShadersManager()->compileShader_by_filePath("Hello",GL_VERTEX_SHADER,"D:\\Dev\\VS projects\\RenderMe Project\\x64\\Debug\\vertexShader.txt");
    unsigned int fragmentShader = scene.getShadersManager()->compileShader_by_filePath("Hello1",GL_FRAGMENT_SHADER,"D:\\Dev\\VS projects\\RenderMe Project\\x64\\Debug\\fragmentShader.txt");

    SpriteRenderer spr = SpriteRenderer(t,vertexShader,fragmentShader,100);
    scene.addComponent<TransformComponent>(entity, tran);
    scene.addComponent<SpriteRenderer>(entity, spr);
    Camera cam = Camera(&scene,0,0,0,0,0,0);
    

    while (!glfwWindowShouldClose(window))
    {
        
        cam.render();

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}