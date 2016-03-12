# Declare the executable target built from your sources
add_executable(../../../dist/ex_08.out ex_08.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_08.out ${OpenCV_LIBS})
