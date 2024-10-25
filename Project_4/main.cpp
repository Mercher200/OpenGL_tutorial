#include "glew.h"
#include "glfw3.h"

#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str(); //поиск первого символа в строке и возврат адреса памяти 
    glShaderSource(id, 1, &src, nullptr); //указать источник шейдера
}

static int Create_Shader(const std::string& vertexShader, const std::string& fragmentShader){

    unsigned int program = glCreateProgram();
    // вершинный и фрагментный шейдеры
    unsigned int vs = CompileShader(GL_VERTEX_SHADER , vertexShader);//вершинный щейдер

}

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
    
    // - расположение фактического буффера
    glEnableVertexAttribArray(0); //для обрезки массива
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // привязка буффера
    // -

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3); // если нет индексного буффера
        // glDrawElements(); //использую индексный буффер

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}