project(Roos.Math.Vector)

add_library(Roos.Math.Vector INTERFACE)

target_include_directories(Roos.Math.Vector INTERFACE Include)

target_link_libraries(Roos.Math.Vector INTERFACE Roos.Math.Operators)

enable_testing()
add_subdirectory(Test)

