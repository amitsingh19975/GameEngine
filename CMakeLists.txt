cmake_minimum_required(VERSION 3.10)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR 
       "FATAL: In-source builds are not allowed.
        You should create a separate directory for build files."
    )
    EXIT(1)
endif()


project(GameEngine  VERSION 1.0
                    DESCRIPTION "Game Engine in openGL"
                    LANGUAGES CXX)

set(GLAD_PATH "${PROJECT_SOURCE_DIR}/vendor/glad/include")
set(SPDLOG_PATH "${PROJECT_SOURCE_DIR}/vendor/spdlog/include")
set(IMGUI_PATH "${PROJECT_SOURCE_DIR}/vendor/imgui")
set(STB_PATH "${PROJECT_SOURCE_DIR}/vendor/stb")
set(GLM_PATH "${PROJECT_SOURCE_DIR}/vendor/glm")
set(INCLUDE_PATH "-I/usr/local/include -I${GLAD_PATH} -I${SPDLOG_PATH} -I${IMGUI_PATH} -I${GLM_PATH} -I{STB_PATH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS 
    "-Wall -Wextra ${INCLUDE_PATH}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/vendor/cmake_module)
include_directories(include ${GLAD_PATH} ${SPDLOG_PATH} ${IMGUI_PATH} ${GLM_PATH} ${STB_PATH})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)
    # find_package(Doxygen)

    # if(DOXYGEN_FOUND)
    #     add_subdirectory(docs)
    # else()
    #     message(STATUS "DOXYGEN NOT FOUND")
    # endif()

    # find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
    # find_library(SDL2_LIBRARY NAME SDL2)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    # find_package(GLEW REQUIRED)
    # include_directories(${GLEW_INCLUDE_DIRS})
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})

endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_compile_definitions(DEBUG)
add_compile_definitions(GL_SILENCE_DEPRECATION)

add_subdirectory(lib)
add_subdirectory(src)
file(COPY include/dark DESTINATION include)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(test)
endif()




