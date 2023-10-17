cmake_minimum_required(VERSION 3.5.0)
project(HIST3D
    VERSION 0.1.0
)

option(HIST3D_BUILD_EXAMPLES "Build hist3d examples" OFF)

add_library(Hist3d SHARED
    src/include/hist3d.h src/src/hist3d.cpp
)

set_target_properties(Hist3d PROPERTIES VERSION ${HIST3D_VERSION})
target_include_directories(Hist3d PUBLIC src/include)
target_compile_options(Hist3d PUBLIC
    -Werror -pedantic-errors -Wall -Wextra
)

if(HIST3D_BUILD_EXAMPLES)
    add_executable(hist3d-example src/hist3d-example.cpp)
    set_target_properties(hist3d-example PROPERTIES
        INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
    target_link_libraries(hist3d-example Hist3d)
    install(TARGETS hist3d-example DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endif()

install(TARGETS Hist3d DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY src/include DESTINATION ${CMAKE_INSTALL_PREFIX})
