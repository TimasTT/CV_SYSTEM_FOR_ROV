//
// Created by timas on 06.05.2021.
//

#ifndef CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
#define CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "perspective_transformation.hpp"

/**
 * \brief Class for image filtering
 *
 * In this class, the image is filtered, blurred, binarized,
 * and the contours of special beacons are searched on it.
 */

class ImageProcessed {
    cv::Mat Img;
    std::vector<std::vector<cv::Point>> Contours;
    std::vector<cv::Point> Centers;

    std::shared_ptr<P4P> PerspectiveTransformation;

    void FilterCompute();

    void CentrePixelCoordinatesDetection();

public:
    ImageProcessed();

    /**
     * \brief Constructor of the class
     *
     * \param[in] filename Path to your image
     */

    ImageProcessed(const std::string &filename);

    /**
     * \brief Image filtering and coordinates searching
     *
     * Filtering for more successful finding the special marker on it.
     * Searching contours of special beacons of marker and theirs coordinates on image.
     */

    void FindWorldCoordinates();

    /**
     * \brief Receiving processed image.
     *
     * \return Processed image with searched contours of special beacons.
     */

    const cv::Mat &GetImg();
};

#endif //CV_SYSTEM_FOR_ROV_IMG_PROCESSING_HPP
