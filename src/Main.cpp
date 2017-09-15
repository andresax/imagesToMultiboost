#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <vector>

#include <string>
#include <Configurator.h>
#include <ProgressBar.h>
#include <map>

std::map<int,cv::Scalar> classColor;
std::map<int,int> colorGray;

void writeHeader(int W, std::ofstream &file);
void writePatch(const cv::Mat &img, int r, int c, int W, std::ofstream &file);
void writePatchColorwise(const cv::Mat &img, int r, int c, int W, std::ofstream &file);
int train(Config &conf);
int test(Config &conf);
int read(Config &conf);
int readPosterior(Config &conf);

int main(int argc, char const *argv[]){
  /*classColor[0]=cv::Scalar(0,0,0);
  classColor[1]=cv::Scalar(0,0.8,0);
  classColor[2]=cv::Scalar(0.3,0.5,0);
  classColor[3]=cv::Scalar(0.7, 0.8, 0.9);
  classColor[4]=cv::Scalar(0.5, 0.5, 0);
  classColor[5]=cv::Scalar(0, 0.7, 0.7);
  classColor[6]=cv::Scalar(0.9, 0, 0);
  classColor[7]=cv::Scalar(0.2, 0.2, 0.9);
  classColor[8]=cv::Scalar(0.3, 0.7, 0.1);
  classColor[9]=cv::Scalar(0.1, 0.1, 0.1);*/
  classColor[0]=cv::Scalar(1.0,0.0,0.0);
  classColor[1]=cv::Scalar(0.0,1.0,0.0);
  classColor[2]=cv::Scalar(0.0,0.0,1.0);
  //classColor[3]=cv::Scalar(1.0,1.0,1.0);

  colorGray[0]=0;
  colorGray[1]=1;
  colorGray[2]=2;
  colorGray[3]=3;
  colorGray[4]=4;
  colorGray[5]=5;
  colorGray[6]=6;
  colorGray[7]=7;
  colorGray[8]=8;
  colorGray[9]=9;


  Configurator c;
  Config conf = c.parse(std::string(argv[1]));
  conf.toString();

  switch (conf.operation){
    case operationMode::TRAIN:
      train(conf);
      break;
    case operationMode::TEST:
      test(conf);
      break;
    case operationMode::READ_IMG:
      read(conf);
      break;
    case operationMode::READ_POST:
      readPosterior(conf);
      break;
    default:
      break;
  }
}


void writeHeader(int W, std::ofstream &file){
    file<<"@relation fountain"<<std::endl;
    int i=0;
    for (int rW = - W ; rW <=  W ; ++rW){
      for (int cW = - W ; cW <=  W; ++cW){
        boost::format fmt("%04d");
        fmt % i;
        file<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//R
        i++;
        fmt % i;
        file<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//G
        i++;
        fmt % i;
        file<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//b
        i++;
      }
    }
    file<<"@attribute class {";

    for (auto c:classColor)  {
      if(c.first == classColor.size()-1)
        //if(c.first == 9)
        file<<c.first<<"";
      else
        file<<c.first<<",";
    }
    file<<"}"<<std::endl;

    file<<std::endl<<"@data"<<std::endl;

}

void writePatch(const cv::Mat &img, int r, int c, int W, std::ofstream &file){
  for (int rW = (r - W >= 0 ? r - W : 0); rW <= (r + W < img.rows ? r + W : img.rows); ++rW){
    for (int cW = (c - W >= 0 ? c - W : 0); cW <= (c + W < img.cols ? c + W : img.cols); ++cW){
      file<<img.at<cv::Vec3f>(rW,cW).val[0] <<",";
      file<<img.at<cv::Vec3f>(rW,cW).val[1] <<",";
      file<<img.at<cv::Vec3f>(rW,cW).val[2] << ",";
    }
  }
}

void writePatchColorwise(const cv::Mat &img, int r, int c, int W, std::ofstream &file){
   for (int rW = (r - W >= 0 ? r - W : 0); rW <= (r + W < img.rows ? r + W : img.rows); ++rW){
    for (int cW = (c - W >= 0 ? c - W : 0); cW <= (c + W < img.cols ? c + W : img.cols); ++cW){
      file<<img.at<cv::Vec3f>(rW,cW).val[0] <<",";
    }
  }

  for (int rW = (r - W >= 0 ? r - W : 0); rW <= (r + W < img.rows ? r + W : img.rows); ++rW){
    for (int cW = (c - W >= 0 ? c - W : 0); cW <= (c + W < img.cols ? c + W : img.cols); ++cW){
      file<<img.at<cv::Vec3f>(rW,cW).val[1] <<",";
    }
  }

  for (int rW = (r - W >= 0 ? r - W : 0); rW <= (r + W < img.rows ? r + W : img.rows); ++rW){
    for (int cW = (c - W >= 0 ? c - W : 0); cW <= (c + W < img.cols ? c + W : img.cols); ++cW){
      file<<img.at<cv::Vec3f>(rW,cW).val[2] << ",";
    }
  }
}


int train(Config &conf){
  int W = conf.window;
  std::ofstream filetrain;
  std::stringstream formatStr;
  ProgressBar progress;
  formatStr << '%'<<"0"<<conf.digits<<"d";


  std::cout<<"Convert images for multiboost"<<std::endl;

  filetrain.open(conf.outputName + ".arff");
  
  boost::format fmt(formatStr.str().c_str());

  std::ifstream file,fileSeg;
  std::vector<std::pair<cv::Mat,cv::Mat>> trainSegmimage;
  
  for (auto p : conf.folderNames){
    for (int i = conf.firstFrame; i < conf.lastFrame; ++i){
      
      fmt % i;
      std::string simage = conf.pathBase + p + conf.imagePrefix + fmt.str() + conf.imagePostfix;
      std::string ssegm = conf.pathBase + p + conf.segmentationPrefix+ fmt.str() + conf.segmentationPostfix;

      file.open(simage);
      fileSeg.open(ssegm);
      if(file.good() && fileSeg.good()){
        cv::Mat im = cv::imread(simage);
        cv::Mat se = cv::imread(ssegm);

        std::cout<<simage<<std::endl;
        std::cout<<ssegm<<std::endl;
        cv::Mat seOK,imOk;
        se.convertTo(seOK,CV_32F);
        im.convertTo(imOk, CV_32F);
        trainSegmimage.push_back(std::pair<cv::Mat,cv::Mat>(imOk,seOK));
      }
      file.close();
      fileSeg.close();
   }
    
  }


  writeHeader(W,filetrain);
  for(auto p : trainSegmimage){
    std::cout<<"Processing new image"<<std::endl;
    int count=0;
    /**/
    progress.reset(40,p.first.rows - 2*W);
    /**/
    for (int r = W; r < p.first.rows-W; ++r){
      for (int c = W; c < p.first.cols-W; ++c){

          int idClass;
          bool found=false;
          for (auto color : classColor){
            if(static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[2]) == static_cast<int>(ceil(255.0 * color.second.val[0])) &&
              static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[1]) == static_cast<int>(ceil(255.0 * color.second.val[1])) &&
              static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[0]) == static_cast<int>(ceil(255.0 * color.second.val[2]))){
              found = true;
              idClass = color.first;
            }
          }

          if(found){
            // std::cout<<p.second.at<cv::Vec3f>(r,c).val[0]<<" ";
            // std::cout<<p.second.at<cv::Vec3f>(r,c).val[1]<<" ";
            // std::cout<<p.second.at<cv::Vec3f>(r,c).val[2]<<std::endl;
            // std::cout<<p.first.at<cv::Vec3f>(r-W,c-W).val[0]<<" ";
            // std::cout<<p.first.at<cv::Vec3f>(r-W,c-W).val[1]<<" ";
            // std::cout<<p.first.at<cv::Vec3f>(r-W,c-W).val[2]<<std::endl;
            // std::cout<<idClass<<std::endl;

            // exit(0);
            if(count%8==0||idClass==2){
              writePatch(p.first,r,c,W,filetrain);
              filetrain<<""<<idClass<<std::endl;
            }
            count++;
          }
      }
      
      progress.addIteration();
    }
  }
    

  std::cout<<"Ended"<<std::endl;
   filetrain.close();
  return 0;

}



int test(Config &conf){

  int W = conf.window;
  std::ofstream filetrain;
  std::stringstream formatStr;
  ProgressBar progress;
  formatStr << '%'<<"0"<<conf.digits<<"d";

  std::cout<<"Convert images for multiboost"<<std::endl;
  for (int cur = conf.firstFrame; cur < conf.lastFrame; ++cur) {
    boost::format fmt(formatStr.str().c_str());
    fmt % cur;

    filetrain.open(conf.outputName+ fmt.str()+".arff");

    std::ifstream file,fileSeg;
    std::vector<std::pair<cv::Mat,cv::Mat>> trainSegmimage;
    
    for (auto p : conf.folderNames){

      std::string simage = conf.pathBase + p + conf.imagePrefix + fmt.str() + conf.imagePostfix;
      std::string ssegm = conf.pathBase + p + conf.segmentationPrefix+ fmt.str() + conf.segmentationPostfix;
      
      if(!conf.withGT) {
        ssegm=simage;
      }

      file.open(simage);
      fileSeg.open(ssegm);
      if(file.good() && fileSeg.good()){
        cv::Mat im = cv::imread(simage);
        cv::Mat se = cv::imread(ssegm);
        std::cout<<simage<<std::endl;
        std::cout<<ssegm<<std::endl;

        cv::Mat seOK,imOk;
        se.convertTo(seOK,CV_32F);
        im.convertTo(imOk, CV_32F);

        trainSegmimage.push_back(std::pair<cv::Mat,cv::Mat>(imOk,seOK));
      }
      file.close();
      fileSeg.close();
       
    }

    writeHeader(W,filetrain);
    for(auto p : trainSegmimage){
      std::cout<<"Processing new imGW"<<std::endl;
      int count=0;
      /**/
      progress.reset(40,p.first.rows - 2*W);
      /**/
      
      for (int r = W; r < p.first.rows-W; ++r){
        for (int c = W; c < p.first.cols-W; ++c){
          int idClass = 0;
          bool found=false;
          if(conf.withGT) {
            for (auto color : classColor){
              if(static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[2]) == static_cast<int>(ceil(255.0 * color.second.val[0])) &&
                static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[1]) == static_cast<int>(ceil(255.0 * color.second.val[1])) &&
                static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[0]) == static_cast<int>(ceil(255.0 * color.second.val[2]))){
                found = true;
                idClass =color.first;
              }
            }
          }
          writePatch(p.first,r,c,W,filetrain);
          if(found)  {
            filetrain<<""<<idClass<<std::endl;  
          }else{
            filetrain<<""<<classColor.size()<<std::endl;  
          } 
        }
        progress.addIteration();
        
      }
    }
    filetrain.close();

  }
}


int read(Config &conf){
  int W = conf.window;
  std::ifstream file;
  std::stringstream formatStr;
  formatStr << '%'<<"0"<<conf.digits<<"d";
  for (int cur = conf.firstFrame; cur < conf.lastFrame; ++cur) {
    boost::format fmt(formatStr.str().c_str());
    fmt % cur;
    std::string p = conf.pathBase + fmt.str() + "";
    std::cout<<p<<std::flush;
    file.open(p);
    if(file.good()){
      std::cout<<" found"<<std::endl;
      std::string line;
      std::getline(file, line);
      cv::Mat imageCur = cv::Mat::zeros(conf.height, conf.width, CV_8UC3);

      int id, classLabel;
      for (int aaa = 0;aaa < 1; aaa++){
        for (int r = W; r < imageCur.rows-W; ++r){
          for (int c = W; c < imageCur.cols-W; ++c){
            std::string line;
            std::getline(file, line);

            std::istringstream iss(line);
            iss >> id >> classLabel;
            imageCur.at<cv::Vec3b>(r,c).val[0] = round(classColor[classLabel].val[0]*255.0);
            imageCur.at<cv::Vec3b>(r,c).val[1] = round(classColor[classLabel].val[1] *255.0);
            imageCur.at<cv::Vec3b>(r,c).val[2] = round(classColor[classLabel].val[2] *255.0);
            
          }
        }
        std::stringstream ss;
        ss<<conf.outputName<<fmt.str()<<".png";
        cv::imwrite(ss.str(),imageCur);
      }
    }else{
      std::cout<<" not found"<<std::endl;
    }
    file.close();
  }
}



int readPosterior(Config &conf){
  int W = conf.window;
  std::ifstream file;
  std::stringstream formatStr;
  formatStr << '%'<<"0"<<conf.digits<<"d";
  for (int cur = conf.firstFrame; cur < conf.lastFrame; ++cur) {
    boost::format fmt(formatStr.str().c_str());
    fmt % cur;
    std::string p = conf.pathBase + fmt.str() + "";
    std::cout<<p<<std::flush;
    file.open(p);
    if(file.good()){
      std::cout<<" found"<<std::endl;
      std::string line;
      std::getline(file, line);
      cv::Mat imageCur = cv::Mat::zeros(conf.height, conf.width, CV_8UC3);
      /*std::vector<cv::Mat> imagesClass;
      for (int i = 0; i < classColor.size(); ++i) {
        imagesClass.push_back(cv::Mat::zeros(conf.height, conf.width, CV_32FC3));
      }*/
      
      std::vector<std::ofstream> filesPost(classColor.size());
      for (int i = 0; i < classColor.size(); ++i) {
        boost::format fmt2(formatStr.str().c_str());
        fmt2 % cur;
        std::stringstream ss;
        ss<<conf.outputName<<"Post"<<fmt2.str() << "-" << i << ".txt";
        filesPost[i].open(ss.str().c_str());
        //cv::imwrite(ss.str(),imagesClass[i]);
      }

      for (int aaa = 0;aaa < 1; aaa++){
        for (int r = W; r < imageCur.rows-W; ++r){
          for (int c = W; c < imageCur.cols-W; ++c){
            std::string line;
            std::getline(file, line);

            int classLabel;
            float maxValue;

            std::istringstream iss(line);
            int cur;
            for (int i = 0; i < classColor.size(); ++i) {
              float id;
              char c;
              iss >> id>>c;

              if(i==0){
                classLabel = i;
                maxValue = id;
              }else if (id > maxValue){
                maxValue = id;
                classLabel = i;
              }

              /*imagesClass[i].at<cv::Vec3f>(r,c).val[0] = id;
              imagesClass[i].at<cv::Vec3f>(r,c).val[1] = id;
              imagesClass[i].at<cv::Vec3f>(r,c).val[2] = id;*/
              filesPost[i] << id <<" " << std::endl;
            }

            imageCur.at<cv::Vec3b>(r,c).val[0] = round(classColor[classLabel].val[0] * 255.0);
            imageCur.at<cv::Vec3b>(r,c).val[1] = round(classColor[classLabel].val[1] * 255.0);
            imageCur.at<cv::Vec3b>(r,c).val[2] = round(classColor[classLabel].val[2] * 255.0);
            
          }
        }
        std::stringstream ss;
        ss<<conf.outputName<<fmt.str()<<".png";
        cv::imwrite(ss.str(),imageCur);
        for (int i = 0; i < classColor.size(); ++i) {
          filesPost[i]<<std::endl;
        }
        
      }
    }else{
      std::cout<<" not found"<<std::endl;
    }
    file.close();
  }
}




// void toGrayImages(){
//   std::string basepahth = "/home/andrea/Desktop/Datasets/3DRMS-Challenge2017/testing/seg/";

//   for (int j = 0; j < 2; ++j)
//   for (int i = 0; i < 123; ++i){
//       std::stringstream pathOrigFile, pathGrayFile;
//       boost::format fmt("%04d");
//       fmt % i;
//       pathOrigFile<<basepahth<<j<<"-"<<fmt.str()<<"_rgb.png";
//       pathGrayFile<<basepahth<<j<<"-"<<fmt.str()<<".png";
//       cv::Mat image = cv::imread(pathOrigFile.str());
//       // cv::imshow("image",image);
//       // cv::waitKey(0);
//       std::cout<<"Processing image: "<<pathOrigFile.str()<<std::endl;

//       cv::Mat imageCur(image.size(),CV_8UC1);
//       int count =0;
//       for (int r = 0; r < image.rows; ++r){
//         for (int c = 0; c < image.cols; ++c){
//           cv::Scalar color( static_cast<float>(image.at<cv::Vec3b>(r,c).val[0]),
//                             static_cast<float>(image.at<cv::Vec3b>(r,c).val[1]),
//                             static_cast<float>(image.at<cv::Vec3b>(r,c).val[2]));

//           //std::cout<<color<<" comparing to: "<<std::flush;
//           int id = 255;
//           for (auto it = classColor.begin(); it != classColor.end(); ++it ){
//           //std::cout<< it->second*255.0<<" "<<std::flush;
//             if (round(it->second.val[0]*255.0) == (int)color.val[0] && 
//                 round(it->second.val[1]*255.0) == (int)color.val[1] && 
//                 round(it->second.val[2]*255.0) == (int)color.val[2]){
//                 id =  it->first;
//                 count++;
//                 break;
//             }
//           }
//           //std::cout <<id<<std::endl;

//           if(id ==255){
//             imageCur.at<unsigned char>(r,c) = 255;
//           }else{
//             imageCur.at<unsigned char>(r,c) = colorGray[id];
//           }
//         }
//       }
//       std::cout<<"Num found: "<< count<<std::endl;
//       //exit(0);

//       cv::imwrite(pathGrayFile.str(),imageCur);
//   }
// }
