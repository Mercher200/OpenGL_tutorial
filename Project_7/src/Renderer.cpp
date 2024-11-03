#include "glew.h"
#include "glfw3.h"

#include "Renderer.h"
#include <iostream>

void Renderer::Draw(const VertexArray& va, const indexBuffer& ib, const Shader& shader) const {
    
     shader.Bind();
        va.Bind();
        ib.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const{
    glClear(GL_COLOR_BUFFER_BIT);
}
