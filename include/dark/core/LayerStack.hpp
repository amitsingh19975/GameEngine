#if !defined(DK_LAYER_STACK_HPP)
#define DK_LAYER_STACK_HPP

#include "dark/core/Core.hpp"
#include "dark/core/Layer.hpp"

namespace dk{
    struct LayerStack{
        
        using base_type = std::vector< Ref<Layer> >;
        using size_type = typename base_type::size_type;
        using value_type = typename base_type::value_type;
        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;

        LayerStack() = default;
        ~LayerStack();

        void PushLayer( value_type& layer );
        void PushOverlay( value_type& overlay );
        void PopLayer( value_type& layer );
        void PopOverlay( value_type& overlay );

        iterator begin() { return m_layer.begin(); }
        iterator end() { return m_layer.end(); }
        reverse_iterator rbegin() { return m_layer.rbegin(); }
        reverse_iterator rend() { return m_layer.rend(); }
        
        const_iterator begin() const { return m_layer.begin(); }
        const_iterator end() const { return m_layer.end(); }
        const_reverse_iterator rbegin() const { return m_layer.rbegin(); }
        const_reverse_iterator rend() const { return m_layer.rend(); }

    private:
        base_type m_layer;
        uint32_t m_layerInsertIndex{0};
    };
}

#endif // DK_LAYER_STACK_HPP
