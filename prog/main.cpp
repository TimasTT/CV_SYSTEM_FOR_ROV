#include <iostream>
#include <img_processing.hpp>

int main() {
    std::string filename = "../../images/ang9deg.png";
    ImageProcessed myImg(filename);
    myImg.FindWorldCoordinates();
    return 0;
}
