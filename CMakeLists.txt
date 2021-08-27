cmake_minimum_required(VERSION 3.20)
project(RaycastingEngine)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories("C:/Libraries/SDL/include")

add_executable(RaycastingEngine WIN32 main.cpp)
target_link_libraries(RaycastingEngine C:/Libraries/SDL/lib -Wall -lmingw32 -lSDL2main -lSDL2)

