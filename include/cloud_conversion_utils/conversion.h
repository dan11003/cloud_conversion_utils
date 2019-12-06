#ifndef IO_H
#define IO_H
#include <Eigen/Eigen>
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "iostream"
#include "ros/ros.h"
#include <fstream>
#include <pcl/io/pcd_io.h>
#include "pcl/filters/voxel_grid.h"
using std::cout;
using std::cerr;
using std::endl;
using std::string;
namespace cloud_conversion_utils {
typedef enum { ChallangingRegistrationDatasetCsv, PCD} pcd_types;
//void ReadCloudsFromFile(const std::string directory, const std::string prefix, std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr > &clouds);

//void ReadPosesFromFile(const std::string &filepath, std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > &poses);
class ConvertPointCloud
{
public:

  ConvertPointCloud(const std::string &directory, const std::string &prefix, pcd_types file_type=ChallangingRegistrationDatasetCsv);

  void WriteAll(const std::string &directory, const std::string &prefix, pcd_types pcd_type=PCD);

private:

  void ReadAll();

  bool ReadCsvChallangingDataset(const std::string &filename);

  void WritePcd(const std::string &filename, pcl::PointCloud<pcl::PointXYZ> cloud);

  std::string directory_, prefix_;
  pcd_types file_type_;
  std::vector<pcl::PointCloud<pcl::PointXYZ> > clouds_;



};



}
#endif // IO_H
