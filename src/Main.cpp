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


int main(int argc, char const *argv[]){
 
 int W=3;
  std::map<int,cv::Scalar> classColor;
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


  std::cout<<"Convert images for multiboost"<<std::endl;

  std::ifstream file;
  std::vector<std::pair<cv::Mat,cv::Mat>> trainSegmimage;
  std::string pathBase = "/home/andrea/Desktop/Datasets/3DRMS-Challenge2017/training/";
  std::vector<std::string> pathbases = {"train_around_garden_roses","train_around_hedge"};
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


  std::ofstream filetrain("train2017.arff");

  filetrain<<"@relation challenge2017"<<std::endl;
  for (auto c:classColor)  {
    boost::format fmt("%02d");
    fmt % c.first;
    filetrain<<"@attribute a"<<fmt.str()<<" numeric"<<std::endl;
  }
  filetrain<<"@attribute class {";
  for (auto c:classColor)  {
    filetrain<<c.first<<",";
  }
  filetrain<<"}"<<std::endl;

  filetrain<<std::endl<<"@data"<<std::endl<<std::endl;
  for(auto p : trainSegmimage){
    for (int r = W; r < p.first.rows-W; ++r){
      for (int c = W; c < p.first.cols-W; ++c){
        for (int rW = (r - W >= 0 ? r - W : 0); rW < (r + W < p.first.rows ? r + W : p.first.rows); ++rW){
          for (int cW = (c - W >= 0 ? c - W : 0); cW < (c + W < p.first.cols ? c + W : p.first.cols); ++cW){
            filetrain<<p.first.at<cv::Vec3f>(r,c).val[0] <<",";
            filetrain<<p.first.at<cv::Vec3f>(r,c).val[1] <<",";
            filetrain<<p.first.at<cv::Vec3f>(r,c).val[2] << ",";
          }
        }
        bool found=false;
        for (auto color : classColor){
          if(static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[2]) == static_cast<int>(ceil(255.0 * color.second.val[0])) &&
            static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[1]) == static_cast<int>(ceil(255.0 * color.second.val[1])) &&
            static_cast<int>(p.second.at<cv::Vec3f>(r,c).val[0]) == static_cast<int>(ceil(255.0 * color.second.val[2]))){
            found = true;
            filetrain<<" "<<color.first<<std::endl;
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

            filetrain<<" 0"<<std::endl;
        }
      }
    }
  }


  filetrain.close();
  return 0;
}