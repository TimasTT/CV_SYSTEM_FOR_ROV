add_library(img_processing STATIC
        include/img_processing.hpp
        source/img_processing.cpp
        include/perspective_transformation.hpp
        source/perspective_transformation.cpp)

target_include_directories(img_processing PUBLIC include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Boost 1.59 COMPONENTS)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

target_link_libraries(img_processing ${OpenCV_LIBS} ${Boost_LIBRARIES})