# Declare the executable target built from your sources
add_executable(../../../dist/ex_04.out ex_04.cpp)

# Link your application with OpenCV libraries
target_link_libraries(../../../dist/ex_04.out ${OpenCV_LIBS})
