#include <Eigen/Eigen>
#include "eigen_conversions/eigen_msg.h"
#include <tf_conversions/tf_eigen.h>


#include "sensor_msgs/PointCloud2.h"
#include "pcl/io/pcd_io.h"

#include <fstream>
#include "message_filters/subscriber.h"
#include "tf/message_filter.h"
#include <tf/transform_broadcaster.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>


#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <time.h>
#include <fstream>

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <boost/program_options.hpp>

#include "pcl_conversions/pcl_conversions.h"
#include "pcl_ros/publisher.h"
#include "pcl_ros/point_cloud.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include "pcl/features/normal_3d_omp.h"
#include "pcl/filters/filter.h"
#include "pcl/point_cloud.h"
#include "pcl/common/transforms.h"

#include "tf_conversions/tf_eigen.h"
#include "cloud_conversion_utils/conversion.h"
namespace po = boost::program_options;
namespace ccu= cloud_conversion_utils;
using std::cout;
using std::endl;
using std::string;


//!
//! \brief vectorToAffine3d
//! \param v x y z ex yz ez
//! \return
//!





int main(int argc, char **argv)
{
  string directory_clouds, output_dir;

  ros::init(argc, argv, "pcd_conversion_node");
  po::options_description desc("Allowed options");
  std::string cloud_prefix;
  desc.add_options()
      ("help", "produce help message")
      ("input-dir", po::value<std::string>(&directory_clouds)->default_value(std::string("")),"directory of clouds")
      ("cloud-prefix",po::value<std::string>(&cloud_prefix)->default_value(std::string("PointCloud")),"prefix of cloud names")
      ("output-dir",po::value<std::string>(&output_dir)->default_value(std::string("")),"output directory");

  //Boolean parameres are read through notifiers
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cout << desc << "\n";
    return false;
  }
  if(directory_clouds.size()==0){
    std::cerr<<"No directory"<<std::endl;
    exit(0);
  }
  if(output_dir.size()<=1){
    output_dir=directory_clouds+"output/";
  }

  ccu::ConvertPointCloud convert(directory_clouds, cloud_prefix);

  convert.WriteAll(output_dir,"cloud_");


  return 0;
}



