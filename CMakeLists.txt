cmake_minimum_required(VERSION 3.27)
project(terraria_clone)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/SDL2_include)
set(SDL2_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/dll)
set(RAPIDXML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/RapidXML)


include_directories(${SDL2_INCLUDE_DIR} ${RAPIDXML_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(terraria_clone main-game.cpp TextureContainer.cpp
        EngineUtilsClass.cpp
        Tiles.cpp
        Grid.h
        Grid.cpp
)

target_link_libraries(${PROJECT_NAME}
        SDL2main
        SDL2
        SDL2_ttf
        SDL2_image
        SDL2_mixer)