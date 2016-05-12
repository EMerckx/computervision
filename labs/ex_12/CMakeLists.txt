# Declare the executable target built from your sources
add_executable(../../../dist/ex_12.out ex_12.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_12.out ${OpenCV_LIBS})
