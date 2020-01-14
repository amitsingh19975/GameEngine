#if !defined(DK_LAYER_HPP)
#define DK_LAYER_HPP

#include "core.hpp"
#include "events/Event.hpp"
#include "Timestep.hpp"

namespace dk{
    struct Layer{
        Layer() = default;
        Layer( std::string_view name );
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate( Timestep ) {}
        virtual void OnEvent( EventBase& ) {}

        constexpr std::string const& GetName() const { return m_debugName; }
    private:
        std::string m_debugName{"Layer"};
    };
}

#endif // DK_LAYER_HPP
