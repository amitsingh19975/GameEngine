#if !defined(DK_OPENGL_TEXTURE_HPP)
#define DK_OPENGL_TEXTURE_HPP

#include "dark/renderer/Texture.hpp"

namespace dk{
    struct OpenGLTexture2D : Texture2D{
        OpenGLTexture2D( std::string_view path );
        ~OpenGLTexture2D();
        inline uint32_t GetWidth() const noexcept override { return m_width;}
        inline uint32_t GetHeight() const noexcept override { return m_height; }

        void Bind(uint32_t slot = 0) const noexcept override;

    private:
        uint32_t    m_width;
        uint32_t    m_height;
        uint32_t    m_renderID;
        std::string m_path;

    };
}

#endif // DK_OPENGL_TEXTURE_HPP
