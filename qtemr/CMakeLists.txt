cmake_minimum_required(VERSION 3.19)
project(smartClinic3 VERSION 0.1 LANGUAGES CXX)

set(OPENSSL_USE_STATIC_LIBS true)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)

if (MSVC)
    add_compile_definitions(MEMLEAK=0)
    #add_compile_definitions(/MP)
else()
    add_compile_options()
endif()

set(TARGET_NAME "smartClinic3")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

if(MSVC)
    set(ZLIB ${PROJECT_SOURCE_DIR}/libs/zlib/msvc2019/zlib.lib)
    include_directories("C:\\Program Files (x86)\\Visual Leak Detector\\include")
    set(VLDLIB  "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
    set(OPENSSL_MSVC_STATIC_RT true)

else()
    set(ZLIB ${PROJECT_SOURCE_DIR}/libs/zlib/mingw730/libz.a)
    set(VLDLIB  "")
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



include_directories("src/")


file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE UI src/*.ui)


set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/res/MyApplication.rc")

qt_wrap_ui(UI ${UI})
qt5_add_resources(SOURCES res/resources.qrc)


add_executable(${TARGET_NAME} WIN32 ${UI} ${SOURCES} ${HEADERS} ${APP_ICON_RESOURCE_WINDOWS})

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_precompile_headers(${TARGET_NAME} PRIVATE src/pch.h)

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

