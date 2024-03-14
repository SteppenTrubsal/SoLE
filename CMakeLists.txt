cmake_minimum_required (VERSION 3.8)

project(SoLE)

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h" "include/*.hpp")
add_executable(SoLE ${SOURCES})

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(SoLE PRIVATE Eigen3::Eigen)

target_include_directories(SoLE PRIVATE "include")
target_include_directories(SoLE PRIVATE Eigen3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoLE PROPERTY CXX_STANDARD 20)
endif()