cmake_minimum_required(VERSION 3.26)
project(Project_Zombiod_Tutorial_series_ep2 C)

set(CMAKE_C_STANDARD 17)

# Specify the path to your SDL include directory
include_directories("dependencies/glfw/include")

# Specify the path to your SDL lib directory
link_directories("dependencies/glfw/lib-vc2022")

add_subdirectory("dependencies/glad")

file(GLOB_RECURSE SOURCES
        RELATIVE ${CMAKE_SOURCE_DIR}
        "src/*.c" "src/*.h"
)

add_executable(Project_Zombiod_Tutorial_series_ep2
    "src/main.c"
#   ${SOURCES}
)

# Link SDL library
target_link_libraries(Project_Zombiod_Tutorial_series_ep2 PRIVATE glad glfw3)
include_directories("dependencies/glad/include")
# include_directories("hoster_zod_src/dependencies/lin_math")