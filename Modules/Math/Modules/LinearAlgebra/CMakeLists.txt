project(Roos.Math.LinearAlgebra)

add_library(Roos.Math.LinearAlgebra INTERFACE)

target_include_directories(Roos.Math.LinearAlgebra INTERFACE Include)

target_link_libraries(Roos.Math.LinearAlgebra INTERFACE Roos.Math.Operators)

enable_testing()
add_subdirectory(Test)

