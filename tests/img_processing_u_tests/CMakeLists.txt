add_executable(img_processing_tests img_processing_u_tests.cpp)

target_link_libraries(img_processing_tests img_processing gtest ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME img_processing_tests
        COMMAND img_processing_tests)