cmake_minimum_required(VERSION 3.28)
project(RayTracingEngine)

set(CMAKE_CXX_STANDARD 17)


# External libraries paths


set(GLFW_PATH "D:/Libs/glfw-3.3.8")
set(GLAD_PATH "D:/Libs/Glad")
set(EIGEN_PATH "D:/Libs/eigen-3.4.0")

# GLFW configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_PATH} ${CMAKE_CURRENT_BINARY_DIR}/glfw_build)

# Catch2
find_package(Catch2 CONFIG REQUIRED)


# Collect all source files
file(GLOB_RECURSE CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Core/src/*.cpp")
file(GLOB_RECURSE GEOMETRY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Geometry/src/*.cpp")
file(GLOB_RECURSE MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Math/src/*.cpp")
file(GLOB_RECURSE RENDERING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Rendering/src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp")

set(ALL_SOURCES
        ${CORE_SOURCES}
        ${GEOMETRY_SOURCES}
        ${MATH_SOURCES}
        ${RENDERING_SOURCES}
        "${GLAD_PATH}/src/glad.c"
)

# Main executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        Math/src/TransformationManager.cpp
        Math/include/TransformationManager.h
        Geometry/src/unitGeometricObjects/UnitCube.cpp
        Geometry/include/unitGeometricObjects/UnitCube.h
        Geometry/src/Matrial/Material.cpp
        Geometry/include/Matrial/Material.h)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/include
        ${GLFW_PATH}/include
        ${GLAD_PATH}/include
        ${EIGEN_PATH}
)

# Test executable
add_executable(RayTracingEngineTests ${ALL_SOURCES} ${TEST_SOURCES}
        Tests/GeomatricObjectsTests.cpp)
target_link_libraries(RayTracingEngineTests PRIVATE
        glfw
        Catch2::Catch2WithMain
)
target_include_directories(RayTracingEngineTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests
        ${Catch2_INCLUDE_DIRS}
        ${GLFW_PATH}/include
        ${GLAD_PATH}/include
        ${EIGEN_PATH}
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -g")
endif()


# CTest and Catch2 test discovery
#enable_testing()
#include(CTest)
#include(Catch)
#catch_discover_tests(RayTracingEngineTests)