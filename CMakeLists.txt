cmake_minimum_required(VERSION 3.24)

project(ImacDigger)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# if (MSVC)
#     add_compile_options(/W3)
# else()
#     add_compile_options(-Wall -Wextra -Wpedantic )
# endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE "src/")

# Librairies

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad third_party/glad/src/glad.c)
include_directories(third_party/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)

# ---Add glbasimac---
add_subdirectory(third_party/glbasimac)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glbasimac)
include_directories(third_party/glbasimac/)

target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIBRARIES})