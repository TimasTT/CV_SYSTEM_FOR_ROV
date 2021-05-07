add_library(img_processing STATIC
        include/img_processing.hpp
        source/img_processing.cpp
        include/perspective_transformation.h
        source/perspective_transformation.cpp)

target_include_directories(img_processing PUBLIC include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(img_processing ${OpenCV_LIBS})