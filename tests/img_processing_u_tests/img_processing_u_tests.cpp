//
// Created by timas on 06.05.2021.
//

#include <gtest/gtest.h>

#include <img_processing.hpp>

TEST(ImgBinarisation, FilterTest) {
    std::string filename = "../../../images/image1.png";
    ImageProcessed myImg(filename);
    myImg.FindWorldCoordinates();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}