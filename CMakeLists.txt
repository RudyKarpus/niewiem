cmake_minimum_required(VERSION 3.28)
project(fml)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)


FetchContent_MakeAvailable(fmt SFML)

add_executable(fml main.cpp
        start_screen.cpp
        start_screen.h
        start_screen.h
        constants.h
        constants.h
        game_screen.cpp
        game_screen.h
        Word.cpp
        Word.h
        Word.h
)
target_link_libraries(fml fmt sfml-graphics)


