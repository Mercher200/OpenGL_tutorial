#include "glew.h"
#include "glfw3.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &m_RenderID); //создание фактического буффера
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderID); //привязка фактического буффера
    glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW); // заполнение фактического буффера
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_RenderID);
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}

void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}