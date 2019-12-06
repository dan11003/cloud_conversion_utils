#include "cloud_conversion_utils/conversion.h"

namespace cloud_conversion_utils {

ConvertPointCloud::ConvertPointCloud(const std::string &directory, const std::string &prefix, pcd_types file_type){

  directory_ = directory;
  prefix_ = prefix;
  file_type_ = file_type;
  cout<<"input directory: "<<directory_<<endl;
  cout<<"prefix: "<<prefix<<endl;
  ReadAll();

}
void ConvertPointCloud::ReadAll(){


  int i=0;
  bool found = true;
  while(found){
    std::string filename = directory_+prefix_+std::to_string(i++);
    if(file_type_ == ChallangingRegistrationDatasetCsv)
      found = ReadCsvChallangingDataset(filename+".csv");
    else
      found = false;
  }
}
bool ConvertPointCloud::ReadCsvChallangingDataset(const std::string &filename){
  std::cout<<"Opening : "<<filename;

  int linecount = 1;
  string line;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  std::ifstream myfile (filename);
  if (!myfile.is_open()){
    std::cerr<<", Could not open: "<<filename<<endl;
    return false;
  }

  while ( getline (myfile,line) ){

    if(linecount++==1)
      continue;

    std::vector<double> pose_compoments;
    std::vector<std::string> tokens;
    boost::split( tokens, line, boost::is_any_of(",") );
    for(int i=1;i<tokens.size();i++)
      pose_compoments.push_back((double)atof(tokens[i].c_str()));
    if(pose_compoments.size()==0){
      cerr<<", file content unexpected"<<endl;
      return false;
    }

    pcl::PointXYZ p;
    p.x = pose_compoments[0];
    p.y = pose_compoments[1];
    p.z = pose_compoments[2];
    cloud.push_back(p);
  }
  cout<<", Found "<<linecount-1<<" points"<<endl;

  myfile.close();
  if(linecount>1){
    cloud.header.stamp=0;
    cloud.header.frame_id="/world";
    clouds_.push_back(cloud);
    return true;
  }
  else return false;
}
void ConvertPointCloud::WriteAll(const std::string &directory, const std::string &prefix, pcd_types pcd_type){
  cout<<"Output directory: "<<directory<<endl;
  for (int i = 0; i < clouds_.size(); ++i) {

    std::string output_filename = directory+prefix+std::to_string(i);
    std::cout<<"Writing to : "<<output_filename<<std::endl;
    if(pcd_type==PCD)
      WritePcd(output_filename,clouds_[i]);
  }
}
void ConvertPointCloud::WritePcd(const std::string &filename, pcl::PointCloud<pcl::PointXYZ> cloud){
  std::string path = filename+".pcd";
  pcl::io::savePCDFileBinary (path, cloud);
}

}
