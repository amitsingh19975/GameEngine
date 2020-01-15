#if !defined(DK_LOG_HPP)
#define DK_LOG_HPP

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "dark/core/Core.hpp"

namespace dk{

    namespace detail {
        
        struct Log{
        public:
            Log() = delete;
            static void Init();

            inline static Ref<spdlog::logger>& GetCoreLogger() { return m_coreLogger;}
            inline static Ref<spdlog::logger>& GetClientLogger() { return m_clientLogger;}
        private:
            static Ref<spdlog::logger> m_coreLogger;
            static Ref<spdlog::logger> m_clientLogger;
        };

        struct BaseLog{
            template<typename... Args>
            inline static void Warn(Args&&... args){
                if constexpr( Config::is_debug )
                    m_logger->warn(std::forward<Args>(args)...);
            }

            template<typename... Args>
            inline static void Error(Args&&... args){
                if constexpr( Config::is_debug )
                    m_logger->error(std::forward<Args>(args)...);
            }

            template<typename... Args>
            inline static void Info(Args&&... args){
                if constexpr( Config::is_debug )
                    m_logger->info(std::forward<Args>(args)...);
            }

            template<typename... Args>
            inline static void Trace(Args&&... args){
                if constexpr( Config::is_debug )
                    m_logger->trace(std::forward<Args>(args)...);
            }

            template<typename... Args>
            inline static void Fatal(Args&&... args){
                if constexpr( Config::is_debug ){
                    Error("( Fatal ) {0}",std::forward<Args>(args)...);
                    abort();
                }
            }
            static Ref<spdlog::logger> m_logger;
        };
    }

    struct ClientLog : detail::BaseLog{
        using BaseLog::m_logger;
        using BaseLog::Error;
        using BaseLog::Warn;
        using BaseLog::Info;
        using BaseLog::Fatal;
        ClientLog() = delete;
    };
    struct CoreLog : detail::BaseLog{
        using BaseLog::m_logger;
        using BaseLog::Error;
        using BaseLog::Warn;
        using BaseLog::Info;
        using BaseLog::Fatal;
        CoreLog() = delete;
    };

    template<typename... Args>
    auto CoreAssert(bool cond, Args&... args){
        if constexpr( Config::is_debug ){
            if( !cond ){
                CoreLog::Fatal(std::forward<Args>(args)...);   
                return false;
            }else{
                return true;
            }
        }
    }

    template<typename... Args>
    auto ClientAssert(bool cond, Args&... args){
        if constexpr( Config::is_debug ){
            if( !cond ){
                CoreLog::Fatal(std::forward<Args>(args)...);   
                return false;
            }else{
                return true;
            }
        }
    }
}

#endif // DK_LOG_HPP
