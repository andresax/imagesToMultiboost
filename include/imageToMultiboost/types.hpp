
#include <iostream>
#include <vector>

enum operationMode {TRAIN, TEST, READ_IMG, READ_POST};

struct Config{
  int window = 3;
  int numClasses = 4;
  operationMode operation = operationMode::TRAIN;
  int firstFrame=0;
  int lastFrame=1000;
  int width=0;
  int height=0;
  std::string pathBase = "";
  std::vector<std::string> folderNames ;
  std::string imagePrefix = "";
  std::string imagePostfix = "";
  std::string segmentationPrefix = "";
  std::string segmentationPostfix = "";
  std::string outputName = "";
  int digits =4;
  bool withGT = true;

  void toString(){
    std::cout << "Config: " << std::endl;
    std::cout << "window : "<< window << std::endl;
    std::cout << "window : "<< numClasses << std::endl;
    std::cout << "operationMode : "<< operation << std::endl;
    std::cout << "firstFrame : "<< firstFrame << std::endl;
    std::cout << "lastFrame : "<< lastFrame << std::endl;
    std::cout << "pathBase : "<< pathBase << std::endl;
    std::cout << "imagePrefix : "<< imagePrefix << std::endl;
    std::cout << "imagePostfix : "<< imagePostfix << std::endl;
    std::cout << "segmentationPrefix : "<< segmentationPrefix << std::endl;
    std::cout << "segmentationPostfix : "<< segmentationPostfix << std::endl;
    std::cout << "digits : "<< digits << std::endl;
    std::cout << "withGT : "<< withGT << std::endl;
  }
};
