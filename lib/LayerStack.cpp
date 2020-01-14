#include "dark/LayerStack.hpp"

namespace dk{
    LayerStack::~LayerStack(){
        std::for_each(begin(),end(),[](LayerStack::value_type& layer){
            layer->OnDetach();
            layer.~shared_ptr();
        });
    }

    void LayerStack::PushLayer( LayerStack::value_type& layer ){
        m_layer.emplace(begin() + m_layerInsertIndex, layer);
        ++m_layerInsertIndex;
    }

    void LayerStack::PushOverlay( LayerStack::value_type& overlay ){
        m_layer.emplace_back(overlay);
    }

    void LayerStack::PopLayer( LayerStack::value_type& layer ){
        auto it = std::find(begin(), begin() + m_layerInsertIndex, layer);
        if( it != begin() + m_layerInsertIndex ){
            layer->OnDetach();
            m_layer.erase(it);
            --m_layerInsertIndex;
        }
    }

    void LayerStack::PopOverlay( LayerStack::value_type& overlay ){
        auto it = std::find(begin() + m_layerInsertIndex, end() , overlay);
        if( it != begin() + m_layerInsertIndex ){
            overlay->OnDetach();
            m_layer.erase(it);
        }
    }
}