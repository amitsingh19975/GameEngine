#include "dark/platform/openGL/OpenGLTexture.hpp"
#include "dark/core/Log.hpp"
#include "stb_image.h"
#include <OpenGL/glu.h>

namespace dk{
    OpenGLTexture2D::OpenGLTexture2D(std::string_view path) : m_path(path){
        
        int width, height, channels;
        
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.data(), &width, &height, &channels,0);
        
        CoreAssert(data != nullptr, "OpenGLTexture2D::OpenGLTexture2D: failed to load image!");
        
        m_height = height;
        m_width = width;
        
        GLenum internalFormat{};
        GLenum dataFormat{};

        if( channels == 4 ){
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }else if ( channels == 3 ){
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        CoreAssert( internalFormat & dataFormat, "Format is not supported");

        glEnable(GL_TEXTURE_2D);

        glGenTextures(1, &m_renderID);
        glBindTexture(GL_TEXTURE_2D,m_renderID);

        if constexpr (Config::os == OS::MACOS ){
            glEnable(GL_TEXTURE_RECTANGLE_ARB);
            glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_STORAGE_HINT_APPLE, GL_STORAGE_CACHED_APPLE);
            glPixelStorei(GL_UNPACK_CLIENT_STORAGE_APPLE, GL_TRUE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_STORAGE_HINT_APPLE, GL_STORAGE_CACHED_APPLE);
        }
        glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
        // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        CoreLog::Info("Image Width: {0}, Image Height: {1}", m_width, m_height);

        // gluBuild2DMipmaps(GL_TEXTURE_2D,internalFormat, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,m_width,m_height,dataFormat,GL_UNSIGNED_BYTE,data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(1,&m_renderID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const noexcept {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D,m_renderID);
    }
}