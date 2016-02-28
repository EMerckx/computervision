# Declare the executable target built from your sources
add_executable(../../../dist/ex_05.out ex_05.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_05.out ${OpenCV_LIBS})
