#if !defined(DK_DEREFERNCE_HPP)
#define DK_DEREFERNCE_HPP

#include "dark/core/Log.hpp"
#include "dark/core/SmartPointer.hpp"

namespace dk{


    template<typename T>
    constexpr T& Deref( Scope<T> const& ref ){
        CoreAssert(ref != nullptr, "Deref: Pointer is Null");
        return *ref;
    }

    template<typename T>
    constexpr T& Deref( Ref<T> const& ref ){
        CoreAssert(ref != nullptr || !ref.use_count(), "Deref: Pointer is Null");
        return *ref;
    }

    namespace detail{
        template<typename T>
        struct is_Ref : std::false_type{};

        template<typename T>
        struct is_Ref< Ref<T> > : std::true_type{};
        
        template<typename T>
        struct is_Scope : std::false_type{};

        template<typename T>
        struct is_Scope< Scope<T> > : std::true_type{};
    }

    template<typename T,
        std::enable_if_t< 
            std::is_pointer_v<T>
        , int
        > = 0
    >
    constexpr auto& Deref( T const& ptr ){
        CoreAssert(ptr != nullptr , "Deref: Pointer is Null");
        return *ptr;
    }

}

#endif // DK_DEREFERNCE_HPP
