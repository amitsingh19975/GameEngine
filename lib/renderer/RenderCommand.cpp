#include "dark/renderer/RenderCommand.hpp"
#include "dark/platform/openGL/OpenGLRendererAPI.hpp"

namespace dk {
    Scope<RendererAPI> RenderCommand::s_rendererAPI = CreateScope<OpenGLRendererAPI>();
}