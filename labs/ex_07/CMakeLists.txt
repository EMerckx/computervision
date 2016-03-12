# Declare the executable target built from your sources
add_executable(../../../dist/ex_07.out ex_07.cpp)
add_executable(../../../dist/test.out test.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_07.out ${OpenCV_LIBS})
target_link_libraries(../../../dist/test.out ${OpenCV_LIBS})
