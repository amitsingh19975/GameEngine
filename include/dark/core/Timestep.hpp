#if !defined(DK_TIMESTEP_HPP)
#define DK_TIMESTEP_HPP

namespace dk{
    struct Timestep{
        
        Timestep( float time = .0f ): m_time(time){}
        constexpr operator float() const noexcept { return m_time; }
        constexpr float GetSeconds() const noexcept { return m_time; }
        constexpr float GetMilliseconds() const noexcept { return m_time * 1000.0f; }
    private:
        float m_time;
    };
}

#endif // DK_TIMESTEP_HPP
