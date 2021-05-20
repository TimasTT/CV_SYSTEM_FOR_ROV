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
    DefinitionPoints();
    SearchInitialPoint();
    AngleDefinition();
}

void P4P::DefinitionPoints() {
    int minLen = 640;
    int curLen;
    for (size_t i = 0; i < cameraPoints.size(); ++i) {
        for (size_t j = i; j < cameraPoints.size(); ++j) {
            curLen = static_cast<int>(boost::geometry::distance(cameraPoints[i], cameraPoints[j]));
            if (curLen < minLen && curLen != 0) {
                minLen = curLen;
                firstPoint = std::move(cameraPoints[i]);
                secondPoint = std::move(cameraPoints[j]);
            }
        }
    }

    auto Comp {[](const int &firstLen, const int &secondLen, const int &thirdLen) {
        if (firstLen > secondLen && firstLen > thirdLen) {
            return 1;
        } else if (firstLen < secondLen && secondLen > thirdLen) {
            return -1;
        } else {
            return 0;
        }
    }};

    int maxLen = 0;
    int curLenP1;
    int curLenP2;
    cv::Point bufSecondPoint;
    for (auto &point : cameraPoints) {
        curLenP1 = static_cast<int>(boost::geometry::distance(firstPoint, point));
        curLenP2 = static_cast<int>(boost::geometry::distance(secondPoint, point));
        int bufComp = Comp(curLenP1, curLenP2, maxLen);
        if (bufComp == -1) {
            maxLen = curLenP2;
            bufSecondPoint = std::move(secondPoint);
            thirdPoint = std::move(point);
        } else if (bufComp == 1) {
            maxLen = curLenP1;
            bufSecondPoint = std::move(firstPoint);
            thirdPoint = std::move(point);
        }
    }

    if (bufSecondPoint != secondPoint) {
        std::swap(firstPoint, secondPoint);
    }

    for (const auto &point : cameraPoints) {
        if (point != firstPoint && point != secondPoint && point != thirdPoint) {
            fourthPoint = point;
        }
    }

    cv::circle(GeometryImg, {firstPoint.x, firstPoint.y}, 8, cv::Scalar(0, 0, 255), -1);
    cv::circle(GeometryImg, {secondPoint.x, secondPoint.y}, 8, cv::Scalar(255, 0, 0), -1);
    cv::circle(GeometryImg, {thirdPoint.x, thirdPoint.y}, 8, cv::Scalar(0, 255, 0), -1);
    cv::circle(GeometryImg, {fourthPoint.x, fourthPoint.y}, 8, cv::Scalar(0, 0, 128), -1);
}

void P4P::SearchInitialPoint() {
    boost::geometry::model::multi_point<cv::Point> CenterPoint;
    boost::geometry::intersection(boost::geometry::model::segment<cv::Point> {firstPoint, fourthPoint}, boost::geometry::model::segment<cv::Point> {secondPoint, thirdPoint},
                                  CenterPoint);

    cv::line(GeometryImg, firstPoint, fourthPoint, (0, 0, 255), 1, cv::LINE_AA);
    cv::line(GeometryImg, secondPoint, thirdPoint, (0, 0, 255), 1, cv::LINE_AA);
    cv::circle(GeometryImg, {CenterPoint.at(0).x, CenterPoint.at(0).y}, 8, cv::Scalar(255, 255, 255), -1);

    InitialPoint.x = CenterPoint.at(0).x;
    InitialPoint.y = CenterPoint.at(0).y;

    cv::imshow("Geometry", GeometryImg);
}

void P4P::AngleDefinition() {
    double k2 = (fourthPoint.y - thirdPoint.y) / (fourthPoint.x - thirdPoint.x);
    double k1 = 0;

    angle = abs(atan((k2 - k1) / (1 + k1 * k2)) * 180.0 / M_PI);

    if (thirdPoint.y <= fourthPoint.y && fourthPoint.x > thirdPoint.x) {

    } else if (thirdPoint.y > fourthPoint.y && fourthPoint.x > thirdPoint.x) {
        angle -= 90;
    } else if (fourthPoint.y > thirdPoint.y && thirdPoint.x > fourthPoint.x) {
        angle += 90;
    } else if (fourthPoint.y <= thirdPoint.y && thirdPoint.x > fourthPoint.x) {
        
    }

    std::cout << angle << std::endl;
}


P3P::P3P() {

}

void P3P::CameraPointsToWorldPointsCombination() {

}
