#include "glew.h"
#include "glfw3.h"

#include <iostream>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) std::cout << "ERROR !!!" << std::endl;

    std::cout<<glGetString(GL_VERSION) <<std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f , -0.5f);
        glVertex2f( 0.0f ,  0.0f);
        glVertex2f( 0.0f , -0.5f);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}