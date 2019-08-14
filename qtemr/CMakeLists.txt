cmake_minimum_required(VERSION 3.15)

project(Smartclinic3)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5 REQUIRED COMPONENTS network)
find_package(Qt5 REQUIRED COMPONENTS printsupport)
find_package(Qt5 REQUIRED COMPONENTS sql)
find_package(Qt5 REQUIRED COMPONENTS concurrent)
find_package(Qt5 REQUIRED COMPONENTS xml)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB UIFORMS "*.ui")

add_executable(Smartclinic3 ${SOURCES})
target_link_libraries(Smartclinic3 Qt5::Widgets)
