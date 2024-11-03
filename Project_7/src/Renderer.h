#pragma once

#include "indexBuffer.h"
#include "VertexArray.h" 
#include "Shader.h" 

class Renderer {
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const indexBuffer& ib, const Shader& shader) const;
};