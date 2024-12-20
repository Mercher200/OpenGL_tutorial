#include "glew.h"
#include "glfw3.h"

#include "VertexBufferLayout.h"
#include "VertexArray.h"

VertexArray::VertexArray(){
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElement();
    std::size_t offset = 0;
    for(unsigned int i =0; i<elements.size(); i++){
       const auto& element = elements[i];
       glEnableVertexAttribArray(i); 
       glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(std::size_t)offset);
       offset+= element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind()const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()const {
    glBindVertexArray(0);
}