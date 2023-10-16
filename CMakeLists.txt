cmake_minimum_required(VERSION 3.5.0)
project(HIST3D
    VERSION 0.1.0
)

# Set flags for errors and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -pedantic-errors -Wall -Wextra")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

add_library(Hist3d SHARED
    src/include/hist3d.h src/src/hist3d.cpp
)

set_target_properties(Hist3d PROPERTIES VERSION ${HIST3D_VERSION})
target_include_directories(Hist3d PUBLIC src/include)

add_executable(example src/example.cpp)
target_link_libraries(example Hist3d)
install(TARGETS example DESTINATION bin)

install(TARGETS Hist3d DESTINATION lib)
install(DIRECTORY src/include DESTINATION .)
