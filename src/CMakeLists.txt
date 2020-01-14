file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${PROJECT_SOURCE_DIR}/include/dark/*.h")

set(GLAD_LIB "${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.cpp")
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/vendor/imgui")


# add_library(GameEngineLib STATIC ${LIB_LIST})
add_executable(GameEngine main.cpp)
target_link_libraries(GameEngine GameEngineLib 
    ${SDL2_LIBRARY} 
    ${OPENGL_LIBRARIES} 
    ${GLAD_LIB} 
    # ${GLEW_LIBRARIES}
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    )

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST} )