
class ProgressBar
{
public:
  ProgressBar();
  ~ProgressBar() = default;
  void reset(int numBins, float maxCount);
  void addIteration();
private:
  int numBins_;
   float numberStarsWritten=0.0;
   float countBar_=0.0, numMaxStars_, maxCount_;

};