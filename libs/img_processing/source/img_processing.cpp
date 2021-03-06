//
// Created by timas on 06.05.2021.
//

#include <iostream>
#include <img_processing.hpp>

#include "perspective_transformation.hpp"

ImageProcessed::ImageProcessed() = default;

ImageProcessed::ImageProcessed(const std::string &filename): Img(cv::imread(filename, 0)) {
    //cv::resize(Img, Img, cv::Size(640, 640));
}

void ImageProcessed::FindWorldCoordinates() {
    FilterCompute();
    CentrePixelCoordinatesDetection();

    if (Centers.size() != 4) {
        return;
    }

    PerspectiveTransformation = std::make_shared<P4P>(Centers, Img);
    PerspectiveTransformation->CameraPointsToWorldPointsCombination();

    cv::waitKey(0);
}

void ImageProcessed::FilterCompute() {
    cv::imshow("StartImg", Img);

    //cv::GaussianBlur(Img, Img, cv::Size_(7, 7), 0, 0); - ...!
    cv::blur(Img, Img, cv::Size_(7, 7));
    //cv::imshow("BlurImg", Img);

    int bins_num = 256;
    std::vector<int> histogram(bins_num);
    std::fill(histogram.begin(), histogram.end(), 0);

    for (int y = 0; y < Img.rows; ++y) {
        for (int x = 0; x < Img.cols; ++x) {
            histogram[Img.at<uchar>(y, x)]++;
        }
    }

    auto max_bin = std::max_element(histogram.begin() + 200, histogram.end());
    int cnt = 0;

    cnt = std::count_if(histogram.begin() + 200, histogram.end(), [&](const auto& i){
        return i * 10 > *max_bin;
    });

    for (int y = 0; y < Img.rows; y++) {
        for (int x = 0; x < Img.cols; x++) {
            if (Img.at<uchar>(y, x) < 255 - cnt) {
                Img.at<uchar>(y, x) = 0;
            } else {
                Img.at<uchar>(y, x) = 255;
            }
        }
    }

    //cv::imshow("FilterImg", Img);
}

void ImageProcessed::CentrePixelCoordinatesDetection() {
    cv::findContours(Img, Contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    cv::Mat contourImg(Img.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < Contours.size(); i++) {
        cv::drawContours(contourImg, Contours, i, cv::Scalar(255, 0, 0));
    }

    for (const auto &contour : Contours) {
        cv::Moments m = cv::moments(contour);
        int x = int(m.m10 / m.m00);
        int y = int(m.m01 / m.m00);
        cv::circle(contourImg, {x, y}, 1, cv::Scalar(255, 0, 0), -1);
        Centers.emplace_back(x, y);
    }

    cv::imshow("Contours", contourImg);
    //GeometryImg = std::move(contourImg);
}

const cv::Mat &ImageProcessed::GetImg() {
    return Img;
}


