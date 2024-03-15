cmake_minimum_required (VERSION 3.8)

project(SoLE)

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h" "include/*.hpp")
add_executable(SoLE ${SOURCES})

#--------find_packages------------#
find_package(Eigen3 CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
#--------find_packages------------#

target_link_libraries(SoLE PRIVATE Eigen3::Eigen imgui::imgui  sfml-system sfml-network sfml-graphics sfml-window  implot::implot ImGui-SFML::ImGui-SFML)

target_include_directories(SoLE PRIVATE "include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoLE PROPERTY CXX_STANDARD 20)
endif()