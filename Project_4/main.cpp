#include "glew.h"
#include "glfw3.h"

#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source){ 
    // компиляция шейдера и получение его индефикатора
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str(); //поиск первого символа в строке и возврат адреса памяти 
        glShaderSource(id, 1, &src, nullptr); //указать источник шейдера
        glCompileShader(id); //компиляция шейдера

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);//запрос информации о провверки правильности компиляции (статус компиляции)
        if(result == GL_FALSE){
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char)); 
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile shader!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }
    return id;
}

static unsigned int Create_Shader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    // вершинный и фрагментный шейдеры
    unsigned int vs = CompileShader(GL_VERTEX_SHADER , vertexShader); //вершинный щейдер
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER , fragmentShader); //фрагментный щейдер

    // обьединение двух шейдеров в одну программу 
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program); //устанавливает состояние программы 

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
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

    //вершинный шейдер
    std::string vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "void main()\n"
    "{\n"
    "gl_Position = position;\n"
    "}\n";

    //фрагментный шейдер (настройки цвета)
    std::string fragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    unsigned int shader = Create_Shader(vertexShader, fragmentShader);
    glUseProgram(shader);

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