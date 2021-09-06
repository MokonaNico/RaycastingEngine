cmake_minimum_required(VERSION 3.20)
project(RaycastingEngine C)

set(CMAKE_C_STANDARD 99)

set(SDL_DLL "C:/Libraries/SDL/bin/SDL2.dll"
        "C:/Libraries/SDL/bin/SDL2_image.dll"
        "C:/Libraries/SDL/bin/SDL2_net.dll"
        "C:/Libraries/SDL/bin/SDL2_ttf.dll"
        "C:/Libraries/SDL/bin/zlib1.dll"
        "C:/Libraries/SDL/bin/libpng16-16.dll"
        "C:/Libraries/SDL/bin/libfreetype-6.dll")
set(SDL_INCLUDE "C:/Libraries/SDL/include")
set(SDL_LIB "C:/Libraries/SDL/lib")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(PROJECT_FILES src/main.c
        src/DisplayManager.c src/DisplayManager.h
        src/EventHandler.c src/EventHandler.h
        src/Color.h src/Color.c
        src/Raycasting.c src/Raycasting.h
        src/World.c src/World.h
        src/LinearAlgebra.c src/LinearAlgebra.h
        src/TextureManager.c src/TextureManager.h src/FontHandler.c src/FontHandler.h)

include_directories(${SDL_INCLUDE})
add_executable(RaycastingEngine ${PROJECT_FILES})
target_link_libraries(RaycastingEngine -L${SDL_LIB} -Wall -lmingw32 -mconsole
        -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)