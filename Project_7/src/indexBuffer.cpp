#include "glew.h"
#include "glfw3.h"

#include "indexBuffer.h"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {

    glGenBuffers(1, &m_RenderID); //создание фактического буффера
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID); //привязка фактического буффера
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int), data, GL_STATIC_DRAW); // заполнение фактического буффера
}

indexBuffer::~indexBuffer(){
    glDeleteBuffers(1, &m_RenderID);
}

void indexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void indexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}