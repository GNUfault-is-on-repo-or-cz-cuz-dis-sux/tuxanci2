cmake_minimum_required(VERSION 3.10)

project(tuxanci2 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

find_program(OBJCOPY_TOOL NAMES objcopy)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include ../raygui/src)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib m)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} --strip-all $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Stripping ${PROJECT_NAME}..."
    VERBATIM
)

set(DATA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(DATA_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/data")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DATA_SRC_DIR}"
        "${DATA_DEST_DIR}"
    COMMENT "Copying data directory to build directory..."
)
