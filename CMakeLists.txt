#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
#target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

#find_package(wxWidgets REQUIRED COMPONENTS core base)
#include(${wxWidgets_USE_FILE})
#target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

cmake_minimum_required(VERSION 3.0)

project(myproject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Widgets REQUIRED)

add_executable(myproject main.cpp)

target_link_libraries(myproject Qt5::Widgets)