
#include <sstream>
#include <fstream>
#include <iostream>
#include <Configurator.h>

Configurator::Configurator(){

}

Config Configurator:: parse(std::string configFilePath){

  /****************/
  std::ifstream configFile(configFilePath.c_str());
  if (configFile.is_open())
    std::cout << configFilePath << " opened" << std::endl;
  else
    std::cout << "Error reading " << configFilePath << std::endl;

  Config conf;
  /*********************/
  std::string line;
  std::istringstream iss;
  std::string valueStr;
  int valueBool;

  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> valueStr;

  if(valueStr.compare("test")==0){
    conf.operation = operationMode::TEST;
  }else if(valueStr.compare("train")==0){
    conf.operation = operationMode::TRAIN;
  }else if(valueStr.compare("readPost")==0){
    conf.operation = operationMode::READ_POST;
  }else if(valueStr.compare("read")==0){
    conf.operation = operationMode::READ_IMG;
  }else{
    std::cout<<"unknown mode in the configuration file. Choose test, train or read"<<std::endl;
    exit(0);
  }


  line.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.firstFrame;

  line.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.lastFrame;

  line.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.window;

  if(conf.operation == operationMode::READ_POST){
    line.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.numClasses;

  }
    
  if(conf.operation == operationMode::READ_IMG || conf.operation == operationMode::READ_POST){
    line.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.width;

    line.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.height;

  }

  line.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.pathBase;
  if (conf.pathBase.size()>0) {
    if (conf.pathBase.at(0) == '#') {
      conf.pathBase = std::string("");
    }
  }

  if(conf.operation != operationMode::READ_IMG && conf.operation != operationMode::READ_POST){
    std::getline(configFile, line);
    iss.str("");
    iss.str(line.c_str());
    bool end =false;
    while(!end){
      iss >> valueStr;
      if (valueStr.size()>0){
        if (valueStr.at(0) == '#') {
          conf.folderNames.push_back(std::string(""));
          end = true;
        }else{
          conf.folderNames.push_back(valueStr);
        }
      }else{
        conf.folderNames.push_back(std::string(""));
        end = true;
      }
    }

    iss.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.imagePrefix;
    if (conf.imagePrefix.size()>0)
      if (conf.imagePrefix.at(0) == '#') {
        conf.imagePrefix = std::string("");
      }
  }

  iss.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.imagePostfix;
  if (conf.imagePostfix.size()>0)
    if (conf.imagePostfix.at(0) == '#') {
      conf.imagePostfix = std::string("");
    }
  
  if(conf.operation != operationMode::READ_IMG && conf.operation != operationMode::READ_POST){
    iss.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.segmentationPrefix;
    if (conf.segmentationPrefix.size()>0)
      if (conf.segmentationPrefix.at(0) == '#') {
        conf.segmentationPrefix = std::string("");
      }
    
    iss.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> conf.segmentationPostfix;
    if (conf.segmentationPostfix.size()>0)
      if (conf.segmentationPostfix.at(0) == '#') {
        conf.segmentationPostfix = std::string("");
      }
  }

  iss.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.outputName;
  if (conf.outputName.size()>0)
    if (conf.outputName.at(0) == '#') {
      conf.outputName = std::string("");
    }

  iss.clear();
  std::getline(configFile, line);
  iss.str("");
  iss.str(line);
  iss >> conf.digits;


  if(conf.operation != operationMode::READ_IMG && conf.operation != operationMode::READ_POST){
    iss.clear();
    std::getline(configFile, line);
    iss.str("");
    iss.str(line);
    iss >> valueBool;
    if (valueBool == 0) {
      conf.withGT = false;
    } else {
      conf.withGT = true;
    }
  }
  return conf;
}