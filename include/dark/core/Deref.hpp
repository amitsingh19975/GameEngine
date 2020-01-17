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

}

#endif // DK_DEREFERNCE_HPP
