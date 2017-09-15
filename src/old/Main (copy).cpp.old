#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <vector>

#include <string>
#include <map>

  std::map<int,cv::Scalar> classColor;

 int W=3;
int generate(){
 


  std::cout<<"Convert images for multiboost"<<std::endl;

  std::ofstream filetrain("test2017_boxwood_row.arff");
  std::ifstream file;
  std::vector<std::pair<cv::Mat,cv::Mat>> trainSegmimage;
  std::string pathBase = "/home/andrea/Desktop/Datasets/3DRMS-Challenge2017/training/";
  std::vector<std::string> pathbases = {"train_boxwood_row"};
  //std::vector<std::string> pathbases = {"train_around_garden_roses","train_around_hedge"};
  //std::vector<std::string> pathbases = {"train_around_garden_roses","train_around_hedge","train_boxwood_row","train_boxwood_slope"};
  //std::vector<std::string> pathbases = {"train_around_garden_roses","train_around_hedge","train_boxwood_row","train_boxwood_slope"};
  std::vector<std::string> initFileName = {"uvc_camera_cam_0/uvc_camera_cam_0_f"};
  //std::vector<std::string> initFileName = {"uvc_camera_cam_0/uvc_camera_cam_0_f","uvc_camera_cam_2/uvc_camera_cam_2_f"};
  std::string endFileNameImage = "_undist.png";
  std::string endFileNameSegm = "_gtr.png";

  for (auto p:pathbases){
    for (auto n:initFileName){
      for (int i = 0; i < 10000; ++i){
        boost::format fmt("%05d");
        fmt % i;
        std::string simage = pathBase + p + "/"+ n + fmt.str() + endFileNameImage;
        std::string ssegm = pathBase + p + "/"+ n + fmt.str() + endFileNameSegm;
        file.open(simage);
        if(file.good()){
          cv::Mat im = cv::imread(simage);
          cv::Mat se = cv::imread(ssegm);

          cv::Mat seOK,imOk;
          se.convertTo(seOK,CV_32F);
          im.convertTo(imOk, CV_32F);
          /*std::cout<<seOK.at<cv::Vec3f>(10,10).val[0] <<" - "<< seOK.type() <<std::endl;
          std::cout<<seOK.at<cv::Vec3f>(10,10).val[1] <<" - "<< seOK.type() <<std::endl;
          std::cout<<seOK.at<cv::Vec3f>(10,10).val[2] <<" - "<< seOK.type() <<std::endl;
          std::cout<<simage <<" - "<< seOK.channels() <<std::endl;
          std::cout<<imOk.at<cv::Vec3f>(10,10).val[0] <<" - "<< imOk.type() <<std::endl;
          std::cout<<imOk.at<cv::Vec3f>(10,10).val[1] <<" - "<< imOk.type() <<std::endl;
          std::cout<<imOk.at<cv::Vec3f>(10,10).val[2] <<" - "<< imOk.type() <<std::endl;
          std::cout<<simage <<" - "<< imOk.channels() <<std::endl;
          exit(0);*/

          trainSegmimage.push_back(std::pair<cv::Mat,cv::Mat>(imOk,seOK));
        }
        file.close();
      }
    }
  }



  filetrain<<"@relation challenge2017"<<std::endl;
  int i=0;
  for (int rW = -W ; rW <=  W ; ++rW){
    for (int cW = - W ; cW <=  W; ++cW){
      boost::format fmt("%03d");
      fmt % i;
      filetrain<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//R
      i++;
      fmt % i;
      filetrain<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//G
      i++;
      fmt % i;
      filetrain<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;//b
      i++;
    }
  }
  filetrain<<"@attribute class {";

  for (auto c:classColor)  {
    if(c.first == 9)
      filetrain<<c.first<<"";
    else
      filetrain<<c.first<<",";
  }
  filetrain<<"}"<<std::endl;

int count=0;
  filetrain<<std::endl<<"@data"<<std::endl;
  for(auto p : trainSegmimage){
    for (int r = W; r < p.first.rows-W; ++r){
      for (int c = W; c < p.first.cols-W; ++c){
        if(count%2==0){
          for (int rW = (r - W >= 0 ? r - W : 0); rW < (r + W+1 < p.first.rows ? r + W+1 : p.first.rows); ++rW){
            for (int cW = (c - W >= 0 ? c - W : 0); cW < (c + W+1 < p.first.cols ? c + W+1 : p.first.cols); ++cW){
              filetrain<<p.first.at<cv::Vec3f>(rW,cW).val[0] <<",";
              filetrain<<p.first.at<cv::Vec3f>(rW,cW).val[1] <<",";
              filetrain<<p.first.at<cv::Vec3f>(rW,cW).val[2] << ",";
            }
          }
          bool found=false;
          for (auto color : classColor){
            if(static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[2]) == static_cast<int>(ceil(255.0 * color.second.val[0])) &&
              static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[1]) == static_cast<int>(ceil(255.0 * color.second.val[1])) &&
              static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[0]) == static_cast<int>(ceil(255.0 * color.second.val[2]))){
              found = true;
              filetrain<<""<<color.first<<std::endl;
            }
          }
          if(!found){
            std::cout<<"ERROR"<<std::endl;
            std::cout<<p.second.at<cv::Vec3f>(r,c).val[2]<<", ";
            std::cout<<p.second.at<cv::Vec3f>(r,c).val[1]<<", ";
            std::cout<<p.second.at<cv::Vec3f>(r,c).val[0]<<std::endl;
            for (auto color : classColor){
            std::cout<<"color"<<color.first<<" ";
              std::cout<<ceil(255.0 * color.second.val[0])<<", ";
              std::cout<<ceil(255.0 * color.second.val[1])<<", ";
              std::cout<<ceil(255.0 * color.second.val[2])<<std::endl;              
            }

              filetrain<<"0"<<std::endl;
          }
        }
        count++;
      }
    }
  }


  filetrain.close();
  return 0;
}




void read(){
  std::ifstream file;
  std::string simage = "/home/andrea/Desktop/Datasets/3DRMS-Challenge2017/training/train_boxwood_row/uvc_camera_cam_0/uvc_camera_cam_0_f00490_undist.png";

  cv::Mat image = cv::imread(simage);
  int width = image.cols;
  int height = image.rows;
  boost::filesystem::path dir("res");
  boost::filesystem::create_directories(dir);

  file.open("/home/andrea/myLib/MultiBoost-1.2.02/outChallengeRes");
  std::string line;
  std::getline(file, line);
  int i=0;
  while(!file.eof()){
    cv::Mat imageCur = cv::Mat::zeros(image.size(), CV_8UC3);
    int count=0;
          int id, classLabel;
      for (int r = W; r < image.rows-W; ++r){
        for (int c = W; c < image.cols-W; ++c){
          if(count%2==0){
          std::string line;
          std::getline(file, line);

          std::istringstream iss(line);
          iss >> id >> classLabel;
          imageCur.at<cv::Vec3b>(r,c).val[0] = classColor[classLabel].val[0]*255.0;
          imageCur.at<cv::Vec3b>(r,c).val[1] = classColor[classLabel].val[1] *255.0;
          imageCur.at<cv::Vec3b>(r,c).val[2] = classColor[classLabel].val[2] *255.0;
        }else{
          imageCur.at<cv::Vec3b>(r,c).val[0] = classColor[classLabel].val[0]*255.0;
          imageCur.at<cv::Vec3b>(r,c).val[1] = classColor[classLabel].val[1] *255.0;
          imageCur.at<cv::Vec3b>(r,c).val[2] = classColor[classLabel].val[2] *255.0;
        }
        ++count;
      }
    }
    std::stringstream ss;
    ss<<"culo_"<<i<<".png";
    cv::imwrite(ss.str(),imageCur);
    ++i;
  }
}

int main(int argc, char const *argv[]){
  classColor[0]=cv::Scalar(0,0,0);
  classColor[1]=cv::Scalar(0,0.8,0);
  classColor[2]=cv::Scalar(0.3,0.5,0);
  classColor[3]=cv::Scalar(0.7, 0.8, 0.9);
  classColor[4]=cv::Scalar(0.5, 0.5, 0);
  classColor[5]=cv::Scalar(0, 0.7, 0.7);
  classColor[6]=cv::Scalar(0.9, 0, 0);
  classColor[7]=cv::Scalar(0.2, 0.2, 0.9);
  classColor[8]=cv::Scalar(0.3, 0.7, 0.1);
  classColor[9]=cv::Scalar(0.1, 0.1, 0.1);
  //generate();
  read();
}
