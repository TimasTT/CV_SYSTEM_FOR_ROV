//
// Created by timas on 07.05.2021.
//

#ifndef CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_HPP
#define CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/segment.hpp>

class IPerspectiveTransformation {
public:
    virtual ~IPerspectiveTransformation() = default;

    virtual void CameraPointsToWorldPointsCombination() = 0;
};

class P4P: IPerspectiveTransformation {
    cv::Mat GeometryImg;

    std::vector<cv::Point> worldPoints;
    std::vector<cv::Point> cameraPoints;

    cv::Point InitialPoint;

    cv::Point firstPoint;  // red
    cv::Point secondPoint;  // blue
    cv::Point thirdPoint;  // green
    cv::Point fourthPoint;  // brown

    double angle;

    void SearchInitialPoint();

    void DefinitionPoints();

    void AngleDefinition();

public:
    explicit P4P(std::vector<cv::Point> cameraPts, cv::Mat img);

    void CameraPointsToWorldPointsCombination() override;
};

class P3P: IPerspectiveTransformation {
    std::vector<cv::Point2f> worldPoints;
    std::vector<cv::Point2f> cameraPoints;

public:
    explicit P3P();

    void CameraPointsToWorldPointsCombination() override;
};

#endif //CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_HPP
