cmake_minimum_required(VERSION 3.10)
project(mdx LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
enable_testing()
endif()

add_library(mdx INTERFACE)
target_include_directories(mdx INTERFACE ${CMAKE_SOURCE_DIR}/include/)
target_link_libraries(mdx INTERFACE project_options project_warnings)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
