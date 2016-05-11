# Declare the executable target built from your sources
add_executable(../../../dist/ex_11.out ex_11.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_11.out ${OpenCV_LIBS})
