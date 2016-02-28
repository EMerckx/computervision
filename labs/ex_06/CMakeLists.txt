# Declare the executable target built from your sources
add_executable(../../../dist/ex_06.out ex_06.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_06.out ${OpenCV_LIBS})
