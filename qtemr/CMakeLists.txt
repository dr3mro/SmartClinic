cmake_minimum_required(VERSION 3.19)
project(smartClinic3 VERSION 0.1 LANGUAGES CXX)

set(OPENSSL_USE_STATIC_LIBS true)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

if (MSVC)
    add_compile_definitions(MEMLEAK=0)
    #add_compile_definitions(/MP)
else()
    add_compile_options()
endif()

set(TARGET_NAME "smartClinic3")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

get_filename_component(DIR_ONE_ABOVE ../ ABSOLUTE)
#message(STATUS ${DIR_ONE_ABOVE})


set(CMAKE_CURRENT_BINARY_DIR "${DIR_ONE_ABOVE}/build/${CMAKE_CXX_COMPILER_ID}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)




if(MSVC)
    set(ZLIB ${PROJECT_SOURCE_DIR}/libs/zlib/msvc2019/zlib.lib)
    include_directories("C:\\Program Files (x86)\\Visual Leak Detector\\include")
    set(VLDLIB  "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
    set(OPENSSL_USE_STATIC_LIBS true)
    set(OPENSSL_MSVC_STATIC_RT true)

else()
    set(ZLIB ${PROJECT_SOURCE_DIR}/libs/zlib/mingw730/libz.a)
    set(VLDLIB  "")
    set(OPENSSL_USE_STATIC_LIBS true)
    set(OPENSSL_MSVC_STATIC_RT true)
    set(OPENSSL_ROOT_DIR "C:\\Qt\\Tools\\OpenSSL\\MinGW_x86")
    set(CMAKE_EXE_LINKER_FLAGS " -static")
endif()


find_package(OpenSSL)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Printsupport REQUIRED)

#message(${OPENSSL_INCLUDE_DIR})

include_directories("src/")
include_directories("ui/")
#include_directories("${DIR_ONE_ABOVE}/build/${CMAKE_CXX_COMPILER_ID}")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE UI ui/*.ui)


set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/res/MyApplication.rc")

qt_wrap_ui(UI ${UI})
qt_add_resources(SOURCES res/resources.qrc)


add_executable(${TARGET_NAME} WIN32 ${UI} ${SOURCES} ${HEADERS} ${APP_ICON_RESOURCE_WINDOWS})

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_precompile_headers(${TARGET_NAME} PRIVATE src/pch.h)
if(MSVC)
    target_link_libraries(${TARGET_NAME}
        Qt5::Widgets
        Qt5::Network
        Qt5::Multimedia
        Qt5::Sql
        Qt5::Concurrent
        Qt5::Xml
        Qt5::PrintSupport
        ${ZLIB}
        ${VLDLIB}
        ${OPENSSL_LIBRARIES}
        )
else()
    target_link_libraries(${TARGET_NAME}
        Qt5::Widgets
        Qt5::Network
        Qt5::Multimedia
        Qt5::Sql
        Qt5::Concurrent
        Qt5::Xml
        Qt5::PrintSupport
        ${ZLIB}
        ${VLDLIB}
        ${OPENSSL_LIBRARIES}
        -static-libgcc
        -static-libstdc++
        )
endif()
