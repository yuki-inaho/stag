#include "Stag.h"
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat image = cv::imread("../00000.png", cv::IMREAD_GRAYSCALE);

  Stag stag(15, 7, true);

  stag.detectMarkers(image);
  stag.logResults("");

  std::vector<Marker> markers = stag.getMarkerList();
  cv::Mat result_image = stag.drawMarkersWithGrayImage(image);

  cv::imshow("result", result_image);
  cv::waitKey(0);

  return 0;
}