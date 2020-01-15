#if !defined(DK_MOUSE_CODE_HPP)
#define DK_MOUSE_CODE_HPP

namespace dk{
    enum MouseCode{
        DK_BUTTON_LEFT      = 1,
        DK_BUTTON_MIDDLE    = 2,
        DK_BUTTON_RIGHT     = 3,
        DK_BUTTON_X1        = 4,
        DK_BUTTON_X2        = 5,
        DK_BUTTON_LMASK     = DK_BUTTON_LEFT,
        DK_BUTTON_MMASK     = DK_BUTTON_MIDDLE,
        DK_BUTTON_RMASK     = DK_BUTTON_RIGHT,
        DK_BUTTON_X1MASK    = DK_BUTTON_X1,
        DK_BUTTON_X2MASK    = DK_BUTTON_X2
    };

    static char const* MouseCodeToString[] = {
        nullptr,
        "BUTTON_LEFT",
        "BUTTON_MIDDLE",
        "BUTTON_RIGHT",
        "BUTTON_X1",
        "BUTTON_X2",
        "BUTTON_LMASK",
        "BUTTON_MMASK",
        "BUTTON_RMASK",
        "BUTTON_X1MASK",
        "BUTTON_X2MASK"
    };

}   
// auto& operator<<(std::ostream& os, dk::MouseCode const& k){
//     return os<<dk::MouseCodeToString[static_cast<size_t>(k)];
// }

#endif // DK_MOUSE_CODE_HPP
