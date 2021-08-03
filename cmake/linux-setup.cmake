set(CMAKE_PREFIX_PATH $ENV{HOME}/.local)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(UNIT_TEST ON)
endif ()

add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic
        $<$<STREQUAL:CMAKE_BUILD_TYPE,Debug>:-g>
        $<$<STREQUAL:CMAKE_BUILD_TYPE,Release>:-O3>)
