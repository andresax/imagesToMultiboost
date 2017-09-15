#include <string>
#include <ProgressBar.h>
#include <sstream>
#include <iostream>
#include <fstream>


ProgressBar::ProgressBar(){

};
  

void ProgressBar::reset(int numBins, float maxCount){
  numMaxStars_ = static_cast<float>(numBins);
  maxCount_ = maxCount;
  std::cout<<std::endl<<"|";
  for (int num = 0; num < numMaxStars_; ++num) {
    std::cout<<"-";
  }
  std::cout<<"|100%"<<std::endl;
  std::cout<<"|"<<std::flush;
  countBar_=0;
  numberStarsWritten=0.0;
} 

void ProgressBar::addIteration(){

  while((numberStarsWritten/numMaxStars_) < (countBar_/maxCount_)){
    std::cout<<"*"<<std::flush;
    numberStarsWritten++;
  }
  countBar_++;

}