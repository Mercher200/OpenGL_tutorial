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

    float positions[6] = {
        -0.5f , -0.5f ,
         0.0f ,  0.0f ,
         0.0f , -0.5f ,
    }; 

    uint32_t buffer;
    glGenBuffers(1, &buffer); //создание фактического буффера
    glBindBuffer(GL_ARRAY_BUFFER, buffer); //привязка фактического буффера
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // заполнение фактического буффера

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3); // если нет индексного буффера, треугольник не ресуется(
        // glDrawElements(); //использую индексный буффер

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}