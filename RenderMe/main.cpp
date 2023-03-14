#include <iostream>
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Vertex.h"
#include "ErrorHandler.h"
#include "TexturesManager.h"
#include "MeshRenderer.h"
#include <stdio.h>

using namespace RenderMe::Base;

RenderMe::RenderMe3D::Camera* cam;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if ((action == GLFW_PRESS || action == GLFW_REPEAT )&& cam != nullptr)
    {
        if (key == GLFW_KEY_RIGHT)
            cam->g_rotation.y += .5f;
        else if (key == GLFW_KEY_LEFT)
            cam->g_rotation.y -= 0.5f;
        else if (key == GLFW_KEY_UP)
            cam->g_rotation.x += 0.5f;
        else if (key == GLFW_KEY_DOWN)
            cam->g_rotation.x -= .5f;
    }
}

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
    // Set the keyboard callback function
    glfwSetKeyCallback(window, key_callback);   

    glewInit();
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glViewport(0, 0, 640, 480);
    glClearColor(.1, .1, .1, 1);
    Scene scene = Scene();
    Entity entity = scene.addEntity();
    Entity entity1 = scene.addEntity();
    Entity entity2 = scene.addEntity();
    Entity entity3 = scene.addEntity();
    Entity entity4 = scene.addEntity();
    Entity entity5 = scene.addEntity();
    TransformComponent tran = {10,10,10,5,5,2,2,2,2};
    TransformComponent tran1 = {10,0,-10,5,5,2,2,2,2};
    TransformComponent tran2 = {10,0,-10,5,5,2,2,2,2};
    TransformComponent tran3 = {-10,-10,-10,5,5,2,2,2,2};
    TransformComponent tran4 = {-10,0,-10,5,5,2,2,2,2};
    TransformComponent tran5 = {-10,0,10,5,5,2,2,2,2};
  
    TexturesManager texturesManager = TexturesManager();
    texturesManager.addTexture("C:\\Users\\TMAX27\\Pictures\\Idea.PNG", "test");
     
    unsigned int vertexShader = scene.getShadersManager()->compileShader_by_filePath("Hello",GL_VERTEX_SHADER,"D:\\Dev\\VS projects\\RenderMe Project\\x64\\Debug\\vertexShader.txt");
    unsigned int fragmentShader = scene.getShadersManager()->compileShader_by_filePath("Hello1",GL_FRAGMENT_SHADER,"D:\\Dev\\VS projects\\RenderMe Project\\x64\\Debug\\fragmentShader.txt");
    
    // Define the vertices of the cube
    std::vector<RenderMe::RenderMe3D::Vertex> vertices = {
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}
    };

    // Define the indices of the cube
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0, // Front face
        1, 5, 6, 6, 2, 1, // Right face
        5, 4, 7, 7, 6, 5, // Back face
        4, 0, 3, 3, 7, 4, // Left face
        3, 2, 6, 6, 7, 3, // Top face
        4, 5, 1, 1, 0, 4  // Bottom face
    };

    // Create a mesh from the cube vertices and indices
    RenderMe::RenderMe3D::Mesh mesh(vertices,indices);

    RenderMe::RenderMe3D::MeshRenderer meshRenderer = RenderMe::RenderMe3D::MeshRenderer(mesh, texturesManager.getTexture("test"), vertexShader, fragmentShader);
    scene.addComponent(entity, meshRenderer);
    scene.addComponent(entity1, meshRenderer);
    scene.addComponent(entity2, meshRenderer);
    scene.addComponent(entity3, meshRenderer);
    scene.addComponent(entity4, meshRenderer);
    scene.addComponent(entity5, meshRenderer);
    scene.addComponent(entity, tran);
    scene.addComponent(entity1, tran1);
    scene.addComponent(entity2, tran2);
    scene.addComponent(entity3, tran3);
    scene.addComponent(entity4, tran4);
    scene.addComponent(entity5, tran5);
    cam  =new RenderMe::RenderMe3D::Camera(&scene, { 0,0,0}, { 0,0,0 });
    int height, width;
    while (!glfwWindowShouldClose(window))
    {
        cam->render();
        glfwGetWindowSize(window,&width, &height);
        glViewport(0, 0, width, height);
        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
    
}