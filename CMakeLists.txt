cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(VantagePoint)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")
 
add_executable(VantagePoint
    src/domain/core/domainexception.cpp
    src/domain/core/valueobject.cpp

    src/application/program.cpp
)

target_include_directories(VantagePoint PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include  
)
