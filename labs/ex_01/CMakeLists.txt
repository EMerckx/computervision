# Declare the executable target built from your sources
add_executable(../../../dist/ex_01.out ex_01.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_01.out ${OpenCV_LIBS})