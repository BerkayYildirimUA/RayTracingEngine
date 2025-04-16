cmake_minimum_required(VERSION 3.28)
project(RayTracingEngine)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)

# Use vcpkg toolchain if available
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

# Find dependencies via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# -- Collect Source Files -----------------------------------------------------

file(GLOB_RECURSE CORE_SOURCES       "${CMAKE_CURRENT_SOURCE_DIR}/Core/src/*.cpp")
file(GLOB_RECURSE GEOMETRY_SOURCES   "${CMAKE_CURRENT_SOURCE_DIR}/Geometry/src/*.cpp")
file(GLOB_RECURSE MATH_SOURCES       "${CMAKE_CURRENT_SOURCE_DIR}/Math/src/*.cpp")
file(GLOB_RECURSE RENDERING_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/Rendering/src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES       "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp")

set(ALL_SOURCES
        ${CORE_SOURCES}
        ${GEOMETRY_SOURCES}
        ${MATH_SOURCES}
        ${RENDERING_SOURCES}
)

# -- Main Executable ----------------------------------------------------------

add_executable(${PROJECT_NAME}
        ${ALL_SOURCES}
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad::glad
        Eigen3::Eigen
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/include
)

# -- Test Executable ----------------------------------------------------------

add_executable(RayTracingEngineTests
        ${ALL_SOURCES}
        ${TEST_SOURCES}
)

target_link_libraries(RayTracingEngineTests PRIVATE
        glfw
        glad::glad
        Catch2::Catch2WithMain
)

target_include_directories(RayTracingEngineTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests
)

# -- Compiler & Linker Flags --------------------------------------------------

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")

# -- Optional: CTest / Catch2 test discovery ----------------------------------
# enable_testing()
# include(CTest)
# include(Catch)
# catch_discover_tests(RayTracingEngineTests)