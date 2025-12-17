
add_executable(sandbox
  src/Main.cpp
  src/SandboxLayer.cpp
)

target_link_libraries(sandbox PRIVATE core)

