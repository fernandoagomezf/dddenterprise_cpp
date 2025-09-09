cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(VantagePoint)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")

add_library(VantagePointLib STATIC
    src/domain/common/datetime.cpp
    src/domain/common/domainevent.cpp
    src/domain/common/domainexception.cpp 
    src/domain/common/identifier.cpp
    src/domain/common/valueobject.cpp 
)

target_include_directories(VantagePointLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/doctest
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()

# Keep your original executable
add_executable(VantagePoint
    src/application/program.cpp
)

target_link_libraries(VantagePoint PRIVATE VantagePointLib)
