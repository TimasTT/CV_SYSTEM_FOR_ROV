//
// Created by timas on 06.05.2021.
//

#ifndef CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
#define CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ImageProcessed {
    cv::Mat Img;
    std::vector<std::vector<cv::Point>> Contours;

public:
    explicit ImageProcessed(const std::string& filename);

    void FilterCompute();
    void CentrePixelCoordinatesDetection();
};

#endif //CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
