//
// Created by timas on 07.05.2021.
//

#ifndef CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_H
#define CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class IPerspectiveTransformation {
public:
    virtual ~IPerspectiveTransformation() = default;

    virtual void CameraPointsToWorldPointsCombination() = 0;
};

class P4P: IPerspectiveTransformation {
    std::vector<cv::Point2f> worldPoints;
    std::vector<cv::Point2f> cameraPoints;

public:
    explicit P4P();

    void CameraPointsToWorldPointsCombination() override;
};

class P3P: IPerspectiveTransformation {
    std::vector<cv::Point2f> worldPoints;
    std::vector<cv::Point2f> cameraPoints;

public:
    explicit P3P();

    void CameraPointsToWorldPointsCombination() override;
};

#endif //CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_H
