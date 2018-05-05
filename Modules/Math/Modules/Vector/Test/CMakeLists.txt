add_executable(VectorUnitTests VectorUnitTests.cpp VectorTest.cpp)

target_link_libraries(VectorUnitTests Roos.Math.Vector)

add_test(VectorUnitTests VectorUnitTests)