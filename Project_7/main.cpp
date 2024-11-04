#include "glew.h"
#include "glfw3.h"

#include <iostream>

#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h" 
#include "Shader.h" 
#include "VertexBufferLayout.h"
#include "Renderer.h" 
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;


    window = glfwCreateWindow(640, 480, " ", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK) std::cout << "ERROR !!!" << std::endl;

    std::cout<<glGetString(GL_VERSION) <<std::endl;
{
    float positions[] = { //фактический буфер 
        -0.5f , -0.5f , 0.0f, 0.0f,
         0.5f , -0.5f , 1.0f, 0.0f,
         0.0f ,  0.5f , 1.0f, 1.0f,
        -0.5f ,  0.5f , 0.0f, 1.0f
    }; 

    // индексный буффер
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    }; // индексация фактичесного буффера 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //unsigned int vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao); //привязка массива вершин и указание его индефикатора

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    indexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    Shader shader("Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);

    Texture texture("src/logo.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Bind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer renderer;

    float red = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();    

        shader.Bind();
        shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        if(red > 1.0f) increment = -0.05f; else if(red < 0.0f) increment = 0.05f;
        red+=increment;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}    
    glfwTerminate();
    return 0;
}