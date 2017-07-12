#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

namespace imageTomultiboost{
  struct Config{
    int sizeWin =5;
    std::string pathImages;
    std::string imagePrefix;
    std::string imagePostfix;
    std::string pathSegmentation;
    std::string segmentationPrefix;
    std::string segmentationPostfix;
  }


}
