project(Roos.Math)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)

include_directories(Include)

enable_testing()
add_subdirectory(Modules)
add_subdirectory(Example)
add_subdirectory(Test)