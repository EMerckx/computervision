# Declare the executable target built from your sources
add_executable(../../../dist/ex_03.out ex_03.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_03.out ${OpenCV_LIBS})
