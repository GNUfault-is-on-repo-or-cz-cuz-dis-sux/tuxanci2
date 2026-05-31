cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_definitions(_BSD_SOURCE)

project(tuxanci2 LANGUAGES C)

option(ENABLE_DEBUG "Enable debug menus and stuff" OFF)
option(ENABLE_SERVER "Enable building server" OFF)

include(ExternalProject)

find_program(OBJCOPY_TOOL NAMES objcopy)

file(GLOB CORE_SOURCES "${CMAKE_SOURCE_DIR}/src/core/*.c")
file(GLOB CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/src/game/*.c")
file(GLOB SERVER_SOURCES "${CMAKE_SOURCE_DIR}/src/server/*.c")

if(ENABLE_DEBUG)
    message(STATUS "ENABLE_DEBUG is ON")
    add_compile_options(-Oz -g -Wall -Wextra -pedantic -pipe)
    target_compile_definitions(${TARGET_NAME} PRIVATE ENABLE_DEBUG=1)

    execute_process(
        COMMAND ${CMAKE_C_COMPILER} -print-file-name=libbacktrace.a
        OUTPUT_VARIABLE LIBBACKTRACE_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${CMAKE_C_COMPILER} -print-file-name=include
        OUTPUT_VARIABLE GCC_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    message(STATUS "ENABLE_DEBUG is OFF")
    add_compile_options(-Oz -Wall -Wextra -pedantic -pipe)
endif()

if(NOT ENABLE_SERVER)
    # raylib
    set(CMAKE_BUILD_TYPE Release)
    set(CUSTOMIZE_BUILD ON)
    set(USE_EXTERNAL_GLFW OFF)
    set(PLATFORM Desktop)
    set(OPENGL_VERSION 2.1)
    set(BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_WAYLAND ON)
    set(GLFW_BUILD_X11 ON)
    set(WITH_PIC OFF)
    set(BUILD_SHARED_LIBS OFF)
    set(INCLUDE_EVERYTHING OFF)
    set(USE_AUDIO ON)
    set(SUPPORT_MODULE_RSHAPES ON)
    set(SUPPORT_MODULE_RTEXTURES ON)
    set(SUPPORT_MODULE_RTEXT ON)
    set(SUPPORT_MODULE_RMODELS ON)
    set(SUPPORT_MODULE_RAUDIO ON)
    set(SUPPORT_BUSY_WAIT_LOOP OFF)
    set(SUPPORT_CAMERA_SYSTEM ON)
    set(SUPPORT_GESTURES_SYSTEM OFF)
    set(SUPPORT_RPRAND_GENERATOR OFF)
    set(SUPPORT_MOUSE_GESTURES OFF)
    set(SUPPORT_SSH_KEYBOARD_RPI OFF)
    set(SUPPORT_WINMM_HIGHRES_TIMER ON)
    set(SUPPORT_PARTIALBUSY_WAIT_LOOP ON)
    set(SUPPORT_GIF_RECORDING OFF)
    set(SUPPORT_COMPRESSION_API ON)
    set(SUPPORT_AUTOMATION_EVENTS OFF)
    set(SUPPORT_CUSTOM_FRAME_CONTROL OFF)
    set(SUPPORT_CLIPBOARD_IMAGE OFF)
    set(SUPPORT_QUADS_DRAW_MODE ON)
    set(SUPPORT_FILEFORMAT_PNG ON)
    set(SUPPORT_FILEFORMAT_BMP OFF)
    set(SUPPORT_FILEFORMAT_TGA OFF)
    set(SUPPORT_FILEFORMAT_JPG ON)
    set(SUPPORT_FILEFORMAT_GIF ON)
    set(SUPPORT_FILEFORMAT_QOI OFF)
    set(SUPPORT_FILEFORMAT_PSD OFF)
    set(SUPPORT_FILEFORMAT_DDS OFF)
    set(SUPPORT_FILEFORMAT_HDR OFF)
    set(SUPPORT_FILEFORMAT_PIC OFF)
    set(SUPPORT_FILEFORMAT_KTX OFF)
    set(SUPPORT_FILEFORMAT_ASTC OFF)
    set(SUPPORT_FILEFORMAT_PKM OFF)
    set(SUPPORT_FILEFORMAT_PVR OFF)
    set(SUPPORT_IMAGE_EXPORT OFF)
    set(SUPPORT_IMAGE_GENERATION ON)
    set(SUPPORT_IMAGE_MANIPULATION ON)
    set(SUPPORT_DEFAULT_FONT ON)
    set(SUPPORT_FILEFORMAT_TTF ON)
    set(SUPPORT_FILEFORMAT_FNT OFF)
    set(SUPPORT_FILEFORMAT_BDF OFF)
    set(SUPPORT_TEXT_MANIPULATION OFF)
    set(SUPPORT_FONT_ATLAS_WHITE_REC ON)
    set(SUPPORT_FILEFORMAT_OBJ OFF)
    set(SUPPORT_FILEFORMAT_MTL OFF)
    set(SUPPORT_FILEFORMAT_IQM OFF)
    set(SUPPORT_FILEFORMAT_GLTF ON)
    set(SUPPORT_FILEFORMAT_VOX OFF)
    set(SUPPORT_FILEFORMAT_M3D OFF)
    set(SUPPORT_MESH_GENERATION ON)
    set(SUPPORT_FILEFORMAT_WAV ON)
    set(SUPPORT_FILEFORMAT_OGG ON)
    set(SUPPORT_FILEFORMAT_MP3 OFF)
    set(SUPPORT_FILEFORMAT_QOA OFF)
    set(SUPPORT_FILEFORMAT_FLAC OFF)
    set(SUPPORT_FILEFORMAT_XM OFF)
    set(SUPPORT_FILEFORMAT_MOD OFF)
    set(SUPPORT_STANDARD_FILEIO ON)
    set(SUPPORT_SAVE_PNG OFF)
    set(SUPPORT_SAVE_BMP OFF)
    set(SUPPORT_TRACELOG ON)
    set(SUPPORT_SCREEN_CAPTURE OFF)

    find_package(PkgConfig REQUIRED)
    find_package(Gettext REQUIRED)
    pkg_check_modules(ZSTD REQUIRED libzstd)

    add_subdirectory(raylib)
    
    set(TARGET_NAME ${PROJECT_NAME})
    add_executable(${TARGET_NAME} ${CORE_SOURCES} ${CLIENT_SOURCES})
else()
    set(TARGET_NAME ${PROJECT_NAME}_server)
    add_executable(${TARGET_NAME} ${CORE_SOURCES} ${SERVER_SOURCES})
endif()

if(NOT ENABLE_SERVER)
    add_dependencies(${TARGET_NAME} raylib)

    target_include_directories(${TARGET_NAME} PRIVATE include ${GCC_INCLUDE_DIR})

    target_link_libraries(${TARGET_NAME} PRIVATE ${ZSTD_LIBRARIES} raylib ${LIBBACKTRACE_PATH})

    set(POT_FILE ${CMAKE_SOURCE_DIR}/po/tuxanci2.pot)
    set(PO_DIR ${CMAKE_SOURCE_DIR}/po)
    set(LOCALE_DIR ${CMAKE_SOURCE_DIR}/locale)

    add_custom_target(update-pot
        COMMAND ${GETTEXT_XGETTEXT_EXECUTABLE}
            --keyword=_ --language=C
            --output=${POT_FILE}
            ${CMAKE_SOURCE_DIR}/src/*.c
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Extracting translatable strings into tuxanci2.pot"
    )

    set(LANGUAGES cs)

    foreach(LANG ${LANGUAGES})
        set(PO_FILE ${PO_DIR}/${LANG}.po)

        set(MO_DIR ${CMAKE_BINARY_DIR}/data/locale/${LANG}/LC_MESSAGES)
        set(MO_FILE ${MO_DIR}/tuxanci2.mo)

        add_custom_command(
            OUTPUT ${MO_FILE}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${MO_DIR}
            COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} ${PO_FILE}
            DEPENDS ${PO_FILE}
            COMMENT "Compiling ${LANG}.po to build/data/locale/${LANG}/LC_MESSAGES/tuxanci2.mo"
        )

        add_custom_target(mo-${LANG} ALL DEPENDS ${MO_FILE})
    endforeach()
else()
    target_compile_definitions(${TARGET_NAME} PRIVATE ENABLE_SERVER=1)
    
    target_include_directories(${TARGET_NAME} PRIVATE include)

    target_link_libraries(${TARGET_NAME} PRIVATE)
endif()

if(NOT ENABLE_DEBUG)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --strip-all $<TARGET_FILE:${TARGET_NAME}>
        COMMENT "Stripping ${TARGET_NAME}..."
        VERBATIM
    )
endif()

set(DATA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(DATA_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/data")

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DATA_SRC_DIR}"
        "${DATA_DEST_DIR}"
    COMMENT "Copying data directory to build directory..."
)
