
add_library(core STATIC)

target_include_directories(core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

# =========================
# FetchContent
# =========================
include(FetchContent)

# -------- GLFW --------
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.9
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# -------- GLAD --------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)

FetchContent_MakeAvailable(glad)

# -------- GLM --------
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG        1.0.2
)

FetchContent_MakeAvailable(glm)

# =========================
# Core sources
# =========================
file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp
)

target_sources(core PRIVATE ${CORE_SRC})

# =========================
# Link libraries
# =========================
target_link_libraries(core
  PUBLIC
    glfw
    glad
    glm
)

# =========================
# Platform specifics
# =========================
if(APPLE)
  target_link_libraries(core PUBLIC
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
  )
elseif(UNIX)
  target_link_libraries(core PUBLIC
    dl
    pthread
  )
endif()
