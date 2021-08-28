cmake_minimum_required(VERSION 3.20)
project(RaycastingEngine C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories("C:/Libraries/SDL/include")
add_executable(RaycastingEngine WIN32 main.c DisplayManager.c DisplayManager.h EventHandler.c EventHandler.h Color.h Color.c Raycasting.c Raycasting.h World.c World.h LinearAlgebra.c LinearAlgebra.h)
target_link_libraries(RaycastingEngine C:/Libraries/SDL/lib -Wall -lmingw32 -lSDL2main -lSDL2 -mconsole)