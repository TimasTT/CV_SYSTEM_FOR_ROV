//
// Created by timas on 06.05.2021.
//

#include <iostream>
#include <img_processing.hpp>

ImageProcessed::ImageProcessed(const std::string &filename) {
    Img = cv::imread(filename, 0);
}

void ImageProcessed::FilterCompute() {
    cv::imshow("StartImg", Img);

    cv::GaussianBlur(Img, Img, cv::Size_(7, 7), Img.rows, Img.rows);
    cv::imshow("BlurImg", Img);

    int bins_num = 256;
    std::vector<int> histogram(bins_num);
    for (auto &i : histogram) {
        i = 0;
    }

    for (int y = 0; y < Img.rows; ++y) {
        for (int x = 0; x < Img.cols; ++x) {
            histogram[Img.at<uchar>(y, x)]++;
        }
    }

    auto max_bin = std::max_element(histogram.begin() + 200, histogram.end());
    int cnt = 0;
    for (int i = 220; i < histogram.size(); ++i) {
        if (histogram[i] * 10 > *max_bin) {
            cnt++;
        }
    }

    for (int y = 0; y < Img.rows; y++) {
        for (int x = 0; x < Img.cols; x++) {
            if (Img.at<uchar>(y, x) < 255 - cnt) {
                Img.at<uchar>(y, x) = 0;
            } else {
                Img.at<uchar>(y, x) = 255;
            }
        }
    }

    cv::threshold(Img,Img, 0, 255, cv::THRESH_OTSU);

    cv::imshow("FilterImg", Img);
}

void ImageProcessed::CentrePixelCoordinatesDetection() {
    cv::findContours( Img, Contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE );

    cv::Mat contourImg(Img.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t i = 0; i < Contours.size(); i++) {
        cv::drawContours(contourImg, Contours, i, colors[i % 3]);
    }

    std::vector<cv::Point> Centers;
    for (auto & contour : Contours) {
        int x = 0, y = 0;
        for (auto & point : contour){
            x += point.x;
            y += point.y;
        }
        Centers.emplace_back(x /= contour.size(), y /= contour.size());
    }
    for (auto & Center : Centers) {
        contourImg.at<uchar>(131, 68) = 255;
    }

    cv::imshow("Contours", contourImg);
    cv::waitKey(0);
}
