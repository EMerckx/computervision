# Declare the executable target built from your sources
add_executable(../../../dist/ex_10.out ex_10.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_10.out ${OpenCV_LIBS})
