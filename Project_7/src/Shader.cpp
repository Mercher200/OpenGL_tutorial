#include "glew.h"
#include "glfw3.h"
#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

ShaderProgramSource Shader::ParseShader (const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("#vertex") != std::string::npos) type = ShaderType::VERTEX;
            else
            if(line.find("#fragment") != std::string::npos) type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
    glDeleteProgram(m_RendererID);
}

void Shader::Bind () const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind () const{
    glUseProgram(0);
}

void Shader::SetUniform4f( const std::string& name, float v0, float v1, float v2, float v3){
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1f( const std::string& name, float value){
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i( const std::string& name, int value){
    glUniform1i(GetUniformLocation(name), value);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){ 
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


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
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
   
int Shader::GetUniformLocation(const std::string& name){

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
   if(location == -1) std::cout<< "Warning: uniform " << name <<std::endl;
  m_UniformLocationCache[name] = location;
    return location;
}