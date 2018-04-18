project(Roos.Math)

set(EXECUTABLE_OUTPUT_PATH Build)

include_directories(Include)

enable_testing()
add_subdirectory(Modules)
add_subdirectory(Example)
add_subdirectory(Test)