#include "Stag.h"
#include <opencv2/opencv.hpp>
#include <boost/program_options.hpp>

using namespace boost::program_options;
int main(int argc, char **argv)
{
  /*
    Get camera id with argument parser
  */
  std::string movie_path;
  options_description args("Required input parameters");
  args.add_options()("camera-id,i", value<std::string>(&movie_path)->required(), "Camera index for live capture (0, 1...)");
  variables_map vm;
  try
  {
    store(parse_command_line(argc, argv, args), vm);
    if (vm.count("help") || (argc == 1))
    {
      std::cout << args << std::endl;
      return false;
    }
    notify(vm);
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  /*
    Setup a camera module and marker detector
  */
  cv::VideoCapture camera = cv::VideoCapture();
  camera.open(movie_path);
  if (!camera.isOpened())
  {
    std::cerr << "Unable to open the movie: " << movie_path << std::endl;
    return EXIT_FAILURE;
  }
  Stag stag(15, 7, false); // HD:15

  char key;
  while (true)
  {
    cv::Mat frame_raw, frame_gray;

    camera.read(frame_raw);
    if (frame_raw.empty())
      break;
    cv::cvtColor(frame_raw, frame_gray, cv::COLOR_BGR2GRAY);

    stag.detectMarkers(frame_gray);
    std::vector<Marker> markers = stag.getMarkerList();
    cv::Mat result_image = stag.drawMarkers(frame_raw);

    std::cout << "Number of detected markers:" << markers.size() << std::endl;
    cv::imshow("result", result_image);
    key = cv::waitKey(10);

    if (key == 27)
      break;

    stag.clear();
  }

  camera.release();
  cv::destroyAllWindows();

  return 0;
}