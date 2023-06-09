cmake_minimum_required(VERSION 3.19...3.26)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(chip8)

find_package(SDL2 REQUIRED)

add_executable(chip8 main.cpp src/Chip8.cpp src/Instructions.cpp src/Display.cpp)
target_include_directories(chip8 PUBLIC src ${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 PUBLIC ${SDL2_LIBRARIES})
target_compile_features(chip8 PUBLIC cxx_std_17)
set_target_properties(chip8 PROPERTIES CXX_EXTENSIONS OFF)
