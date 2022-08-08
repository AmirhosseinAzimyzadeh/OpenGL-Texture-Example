cmake_minimum_required(VERSION 3.0.0)
project(OPEN_GL VERSION 0.1.0)

include(CTest)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
enable_testing()

add_executable(OPEN_GL main.cpp)

target_link_libraries(OPEN_GL ${CONAN_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
