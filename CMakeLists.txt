cmake_minimum_required(VERSION 3.28)
project(RayTracingEngine)

set(CMAKE_CXX_STANDARD 17)

# -- External Libraries --------------------------------------------------------

set(GLFW_PATH "D:/Libs/glfw-3.3.8")
set(GLAD_PATH "D:/Libs/Glad")
set(EIGEN_PATH "D:/Libs/eigen-3.4.0")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_PATH} ${CMAKE_CURRENT_BINARY_DIR}/glfw_build)

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
        "${GLAD_PATH}/src/glad.c"
)

# -- Main Executable ----------------------------------------------------------

add_executable(${PROJECT_NAME}
        ${ALL_SOURCES}
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

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

# -- Test Executable ----------------------------------------------------------

add_executable(RayTracingEngineTests
        ${ALL_SOURCES}
        ${TEST_SOURCES}
)

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
        ${GLFW_PATH}/include
        ${GLAD_PATH}/include
        ${EIGEN_PATH}
)

# -- Compiler & Linker Flags --------------------------------------------------


set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")

# -- (Optional) CTest / Catch2 test discovery ---------------------------------
# enable_testing()
# include(CTest)
# include(Catch)
# catch_discover_tests(RayTracingEngineTests)
