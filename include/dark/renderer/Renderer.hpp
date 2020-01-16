#if !defined(DK_RENDER_HPP)
#define DK_RENDER_HPP

namespace dk{

    enum class RendererAPI{
        None = 0, 
        OpenGL
    };

    struct Renderer{
        inline static RendererAPI GetAPI() noexcept { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };
    
}

#endif // DK_RENDER_HPP