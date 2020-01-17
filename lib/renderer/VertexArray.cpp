#include "dark/renderer/VertexArray.hpp"
#include "dark/platform/openGL/OpenGLVertexArray.hpp"

namespace dk{
    Scope<VertexArray> VertexArray::Create(){
        return CreateScope<OpenGLVertexArray>();
    }
}