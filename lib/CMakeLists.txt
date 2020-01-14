
file(GLOB_RECURSE LIB_LIST CONFIGURE DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.cpp")

add_library(GameEngineLib STATIC ${LIB_LIST})

install(TARGETS GameEngineLib DESTINATION lib)