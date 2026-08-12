cmake_minimum_required(VERSION 3.10.0)
project(test_game VERSION 0.1.0 LANGUAGES C CXX)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wshadow -Wunreachable-code")

include_directories(src)

add_executable(test_game 
    main.cpp
    src/actor.cpp
    src/player.cpp
    src/enemy.cpp
    src/action.cpp)

target_include_directories(test_game PRIVATE headers)