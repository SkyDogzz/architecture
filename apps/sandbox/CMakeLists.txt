
add_executable(sandbox
  src/Main.cpp
  src/SandboxLayer.cpp
)

target_include_directories(sandbox PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include
)

target_link_libraries(sandbox PRIVATE core)

