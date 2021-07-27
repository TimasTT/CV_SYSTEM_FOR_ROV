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

/**
 * \brief Class for finding the angle of rotation of a special marker on the image.
 *
 * This class this class determines the angle of rotation of a special marker on the image
 * by identifying special beacons that are located in the form of an asymmetrical figure.
 */

class P4P {
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
    P4P();

    /**
     * \brief Constructor of the class
     *
     * \param[in] cameraPts Coordinates of special beacons
     * \param[in] img Filtered image
     */

    explicit P4P(std::vector<cv::Point> cameraPts, const cv::Mat& img);

    /**
     * \brief Defining the angle of rotation of the special marker
     *
     * The angle is determined using the found coordinates of special beacons
     * and transferred to the ROV control system.
     */

    void CameraPointsToWorldPointsCombination();
};

#endif //CV_SYSTEM_FOR_ROV_PERSPECTIVE_TRANSFORMATION_HPP
