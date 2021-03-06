# https://github.com/aminosbh/sdl2-cmake-modules

project(sdl2-maze)
cmake_minimum_required(VERSION 3.5.1)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

include_directories(
    src
    src/lodepng
    src/pixel_world
    src/maze
    src/maze/depth_first
    src/maze/hunt_and_kill
    src/maze/wilson
    src/maze/aldous_broder
    src/maze/binary_tree
)

# Add all c source files under the src directory
set(SOURCES
    src/main.cpp
    src/pixel_world/pixelWorld.cpp
    src/lodepng/lodepng.cpp
    src/maze/depth_first/depthFirstMaze.cpp
    src/maze/hunt_and_kill/huntAndKillMaze.cpp
    src/maze/wilson/wilsonMaze.cpp
    src/maze/wilson/clingyWilsonMaze.cpp
    src/maze/aldous_broder/aldousBroderMaze.cpp
    src/maze/binary_tree/binaryTreeMaze.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
# find_package(SDL2_image REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
#find_package(SDL2_ttf REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)

