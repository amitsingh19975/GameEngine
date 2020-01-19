#if !defined(DK_TEXTURE_HPP)
#define DK_TEXTURE_HPP

#include "dark/core/Core.hpp"

namespace dk{

    struct Texture{

        virtual ~Texture(){}

        virtual uint32_t GetWidth() const noexcept = 0;
        virtual uint32_t GetHeight() const noexcept = 0;

        virtual void Bind(uint32_t slot = 0) const noexcept = 0;
    };

    struct Texture2D : Texture{

        static Ref<Texture2D> Create( std::string_view path ) noexcept;

    };

}

#endif // DK_TEXTURE_HPP
