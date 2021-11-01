cmake_minimum_required(VERSION 3.20)
project(jx3_tools)

# $ENV{Qt5_DIR} = where_is_qt_installed/lib/cmake/Qt5
string(REPLACE "shared" "static" CMAKE_PREFIX_PATH "$ENV{Qt5_DIR}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_options("-MTd")
else ()
    add_compile_options("-MT")
endif ()

set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)

file(GLOB_RECURSE srcs "3rdparty/*.[h,c]**" "app/*.[h,c]**")
add_executable(${PROJECT_NAME} main.cpp ${srcs})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
