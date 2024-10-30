#include "glew.h"
#include "glfw3.h"

#include <iostream>

#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h" 


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
        -0.5f , -0.5f ,
         0.5f , -0.5f ,
         0.0f ,  0.5f ,
        -0.5f ,  0.5f ,
    }; 

    // индексный буффер
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    }; // индексация фактичесного буффера 

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //привязка массива вершин и указание его индефикатора

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    indexBuffer ib(indices, 6);

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
    "uniform vec4 u_Color;\n" // обьявление переменной дял цвета и отделение ее 
    "\n"
    "void main()\n"
    "{\n"
    "color = u_Color;\n"
    "}\n";

    unsigned int shader = Create_Shader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color"); //получение доступа к положению переменной цвета
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f); //установить данные в шейдере

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float red = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader); //прнивязыаем шейдер
        glUniform4f(location, red, 0.3f, 0.8f, 1.0f); //настраиваем униформу

        
        va.Bind();
        ib.Bind();  //привязыаем индексный буффер

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //фактический вызов отрисоки с помощью индексного буффера ( внимательно смотреть что в 3, тип данных инфексного буффера)

        if(red > 1.0f) increment = -0.05f; else if(red < 0.0f) increment = 0.05f;
        red+=increment;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);

}    
    glfwTerminate();
    return 0;
}