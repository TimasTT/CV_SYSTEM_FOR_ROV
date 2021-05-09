//
// Created by timas on 07.05.2021.
//

#include "perspective_transformation.hpp"

BOOST_GEOMETRY_REGISTER_POINT_2D(cv::Point, int, boost::geometry::cs::cartesian, x, y)

P4P::P4P(std::vector<cv::Point> cameraPts, cv::Mat img) {
    cv::Mat gImg(img.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    GeometryImg = std::move(gImg);

    cameraPoints = std::move(cameraPts);
    worldPoints.emplace_back(16, 16);
    worldPoints.emplace_back(0, 16);
    worldPoints.emplace_back(16, 0);
    worldPoints.emplace_back(0, 0);
}

void P4P::CameraPointsToWorldPointsCombination() {
    SearchInitialPoint();
}

void P4P::SearchInitialPoint() {
    for (const auto &C : cameraPoints) {
        cv::circle(GeometryImg, {C.x, C.y}, 8, (0, 0, 255), -1);
    }

    int max = 0, min = 1280;
    size_t maxInd = 0, minInd = 0;
    for (size_t i = 0; i < cameraPoints.size(); ++i) {
        if (cameraPoints[i].x + cameraPoints[i].y > max) {
            max = cameraPoints[i].x + cameraPoints[i].y;
            maxInd = i;
        }
        if (cameraPoints[i].x + cameraPoints[i].y < min) {
            min = cameraPoints[i].x + cameraPoints[i].y;
            minInd = i;
        }
    }

    size_t otherInd1 = -1, otherInd2 = -1;
    for (size_t i = 0; i < cameraPoints.size(); ++i) {
        if (i != maxInd && i != minInd) {
            otherInd1 = i;
        }
    }

    for (size_t i = 0; i < cameraPoints.size(); ++i) {
        if (i != maxInd && i != minInd && i != otherInd1) {
            otherInd2 = i;
        }
    }

    boost::geometry::model::multi_point<cv::Point> CenterPoint;
    boost::geometry::intersection(boost::geometry::model::segment<cv::Point> {cameraPoints[maxInd], cameraPoints[minInd]},
                                  boost::geometry::model::segment<cv::Point> {cameraPoints[otherInd1], cameraPoints[otherInd2]}, CenterPoint);

    cv::line(GeometryImg, cameraPoints[otherInd1], cameraPoints[otherInd2], (0, 0, 255), 1, cv::LINE_AA);
    cv::line(GeometryImg, cameraPoints[maxInd], cameraPoints[minInd], (0, 0, 255), 1, cv::LINE_AA);
    cv::circle(GeometryImg, {CenterPoint.at(0).x, CenterPoint.at(0).y}, 8, (0, 0, 255), -1);

    InitialPoint.x = CenterPoint.at(0).x;
    InitialPoint.y = CenterPoint.at(0).y;

    cv::imshow("Geometry", GeometryImg);
}


P3P::P3P() {

}

void P3P::CameraPointsToWorldPointsCombination() {

}
