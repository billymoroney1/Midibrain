cmake_minimum_required(VERSION 4.0.2)

include(FetchContent)

FetchContent_Declare(
    libremidi
    GIT_REPOSITORY https://github.com/celtera/libremidi
    GIT_TAG        v5.2.0
)

FetchContent_MakeAvailable(libremidi)


project(Midibrain)
add_executable(Midibrain main.cpp)

target_link_libraries(Midibrain PRIVATE libremidi)
