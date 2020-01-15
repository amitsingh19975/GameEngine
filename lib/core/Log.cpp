#include "dark/core/Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace dk{
    
    namespace detail{
        Ref<spdlog::logger> Log::m_coreLogger;
        Ref<spdlog::logger> Log::m_clientLogger;
        
        Ref<spdlog::logger> BaseLog::m_logger;
    }

    void detail::Log::Init(){
        spdlog::set_pattern("%^[%T] %n : %v%$");
        m_coreLogger = spdlog::stdout_color_mt("DARK ENGINE");
        m_coreLogger->set_level(spdlog::level::trace);
        m_clientLogger = spdlog::stdout_color_mt("APP");
        m_clientLogger->set_level(spdlog::level::trace);
        ClientLog::m_logger = m_clientLogger;
        CoreLog::m_logger = m_coreLogger;
    }

}