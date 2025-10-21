cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-WAll -g -O0)

project(libbst VERSION 0.1)

file(GLOB Lib_SRC CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(Lib ${Lib_SRC})
set_target_properties(Lib PROPERTIES OUTPUT_NAME "libbst")
