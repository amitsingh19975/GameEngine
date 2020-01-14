file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${PROJECT_SOURCE_DIR}/include/dark/*.h")
# file(GLOB_RECURSE LIB_LIST CONFIGURE DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.cpp")

# add_library(GameEngineLib STATIC ${LIB_LIST})
add_executable(GameEngine main.cpp)
target_link_libraries(GameEngine GameEngineLib ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} "${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.cpp")

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST} )