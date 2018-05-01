project(Roos.Math.Operators)

add_library(Roos.Math.Operators INTERFACE)

target_include_directories(Roos.Math.Operators INTERFACE Include)

enable_testing()
add_subdirectory(Test)
