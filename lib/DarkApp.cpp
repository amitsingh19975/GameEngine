#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"

namespace dk{

    Dark* Dark::s_instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLType( ShaderDataType type){
        switch ( type ){
            case ShaderDataType::Float  : 
            case ShaderDataType::Float2 : 
            case ShaderDataType::Float3 : 
            case ShaderDataType::Mat2   : 
            case ShaderDataType::Mat3   : 
            case ShaderDataType::Mat4   : 
            case ShaderDataType::Float4 : return GL_FLOAT;
            case ShaderDataType::Int    : 
            case ShaderDataType::Int2   : 
            case ShaderDataType::Int3   : 
            case ShaderDataType::Int4   : return GL_INT;
            case ShaderDataType::Bool   : return GL_BOOL;
            default : {
                CoreAssert(false, "Unknown Data Type");
                return GL_NONE;
            }
        }
    }

    Dark::Dark(): m_window(Window::Create()), m_imGuiLayer(new ImGuiLayer()){
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        m_window->SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        PushOverlay(m_imGuiLayer);
        
        std::string vertexSrc = R"(
            attribute vec3 a_Pos;
            attribute vec4 a_Col;
            varying vec4 v_Col;
            void main(){
                v_Col = a_Col;
                gl_Position = vec4(a_Pos ,1.0);
            }
        )";

        std::string fragmentSrc = R"(
            varying vec4 v_Col;
            void main(){
                gl_FragColor = v_Col;
            }
        )";

        DKGenVertexArrays(1,&m_vertexArray);
        DKBindVertexArray(m_vertexArray);

        typename VertexBuffer::value_type vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.5f, 0.8f, 0.2f, 1.f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.6f, 1.f
        };

        m_vertexBuffer = VertexBuffer::Create(vertices,sizeof(vertices));
        {
            BufferLayout lay = {
                {ShaderDataType::Float3, "a_Pos"},
                {ShaderDataType::Float4, "a_Color"}
            };
            
            m_vertexBuffer->SetLayout(lay);
        }
        auto idx = 0ul;

        m_shader = CreateScope<Shader>(vertexSrc, fragmentSrc);

        CoreLog::Info("Shader Compiled");
        
        for(auto const& el : m_vertexBuffer->GetLayout() ){
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(idx, el.GetComponentCount() 
                ,ShaderDataTypeToOpenGLType(el.type) 
                ,el.normalized ? GL_TRUE : GL_FALSE 
                ,m_vertexBuffer->GetLayout().GetStride() 
                ,reinterpret_cast<const void*>(el.offset)
            );
            // m_shader->BindAttribute(idx,el.name);
            ++idx;
        }


        typename IndexBuffer::value_type indices[] = {
            0,1,2
        };
        m_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / IndexBuffer::value_size);
    }
    
    Dark::~Dark(){}

    void Dark::onEvent( EventBase& e ){
        EventDispatcher disp(e);
        CoreLog::Info(e);
        
        disp.Dispatch<WindowCloseEvent>(
            std::bind(&Dark::onWindowClose,this,std::placeholders::_1)
        );
        
        std::for_each(m_layerStack.rbegin(), m_layerStack.rend(),[&e]( auto& layer) {
            layer->OnEvent(e);
            if( e.Handled ) return;
        });
    }

    void Dark::Run(){
        CoreLog::Info("Starting Window");
        while(m_running){
            float time = SDL_GetTicks()/ 1000.f;
            Timestep ts = time - m_lastFrame;
            m_lastFrame = time;
            m_shader->Bind();
            glClearColor(0.1f,.1f,.1f, 1.f);
            glClear( GL_COLOR_BUFFER_BIT );
            DKBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for( auto& layer : m_layerStack ){
                layer->OnUpdate(ts);
            }

            m_imGuiLayer->Begin();
            for( auto& layer : m_layerStack ){
                layer->ImGuiRenderer();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();

            // glDisableClientState(GL_NORMAL_ARRAY);
            // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        CoreLog::Error("Window Closed");
    }

    bool Dark::onWindowClose(WindowCloseEvent&){
        m_running = false;
        return true;
    }

    void Dark::PushLayer( Ref<Layer> layer ){
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
        CoreLog::Info("{0} Layer has been attached",layer->GetName());
    }

    void Dark::PushOverlay( Ref<Layer> overlay ){
        m_layerStack.PushLayer(overlay);
        overlay->OnAttach();
    }
}