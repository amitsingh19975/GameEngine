#include "dark/core/Input.hpp"
#include "dark/platform/WindowsInput.hpp"
namespace dk{

    Scope<Input> Input::s_instance = Input::Create();

    Scope<Input> Input::Create() {
        return CreateScope<WindowsInput>();
    }
    
}