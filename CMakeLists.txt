cmake_minimum_required(VERSION 3.27)
project(terraria_clone)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR E:/gitrepos/CLionProjects/terraria_clone/lib/include)
set(SDL2_LIB_DIR E:/gitrepos/CLionProjects/terraria_clone/lib/dll)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(terraria_clone main-game.cpp TextureContainer.cpp EngineUtilsClass.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf SDL2_image SDL2_mixer)