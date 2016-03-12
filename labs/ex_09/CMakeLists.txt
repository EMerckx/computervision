# Declare the executable target built from your sources
add_executable(../../../dist/ex_09.out ex_09.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_09.out ${OpenCV_LIBS})
