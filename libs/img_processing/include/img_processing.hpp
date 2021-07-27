//
// Created by timas on 06.05.2021.
//

#ifndef CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
#define CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "perspective_transformation.hpp"

class ImageProcessed {
    cv::Mat Img;
    std::vector<std::vector<cv::Point>> Contours;
    std::vector<cv::Point> Centers;

    std::shared_ptr<P4P> PerspectiveTransformation;

    void FilterCompute();

    void CentrePixelCoordinatesDetection();

public:
    ImageProcessed();
    ImageProcessed(const std::string &filename);

    void FindWorldCoordinates();

    const cv::Mat &GetImg();
};

#endif //CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
