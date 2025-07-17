cmake_minimum_required(VERSION 3.10)
project(SimpleSFMLGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

file(GLOB_RECURSE SYSTEMS_SRC src/systems/*.cpp)
file(GLOB_RECURSE ENTITIES_SRC src/entities/*.cpp)

add_executable(simple_game
    src/main.cpp
    ${SYSTEMS_SRC}
    ${ENTITIES_SRC}
)

target_link_libraries(simple_game sfml-graphics sfml-window sfml-system)