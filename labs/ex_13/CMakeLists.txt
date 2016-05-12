# Declare the executable target built from your sources
add_executable(../../../dist/ex_13.out ex_13.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_13.out ${OpenCV_LIBS})
