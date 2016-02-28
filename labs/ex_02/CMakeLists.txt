# Declare the executable target built from your sources
add_executable(../../../dist/ex_02.out ex_02.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_02.out ${OpenCV_LIBS})