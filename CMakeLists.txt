add_executable(task01-01 task01-01.cpp)
target_link_libraries(task01-01 PRIVATE semcv ${OpenCV_LIBS})
add_executable(task01-02 task01-02.cpp)
target_link_libraries(task01-02 PRIVATE semcv ${OpenCV_LIBS})