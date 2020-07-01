//
//  pcp_io_point_cloud.hpp
//  pcp
//
//  Created by wuhan on 2020/7/1.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef pcp_io_point_cloud_hpp
#define pcp_io_point_cloud_hpp
#include "pcp_io_base.hpp"
namespace whpcp{
    namespace io{
        class IOPointCloud : public IOBase{
        public:
            IOPointCloud();
            IOPointCloud(const std::string& file_path);
            virtual ~IOPointCloud();
            virtual int readData();
            virtual int writeData(const std::string& file_path);
            pcl::PointCloud<pcl::PointXYZ>::Ptr getPointCloudPtr()const;
            void setPointCloudPtr(pcl::PointCloud<pcl::PointXYZ>::Ptr _point_cloud_ptr);
        private:
            pcl::PointCloud<pcl::PointXYZ>::Ptr _point_cloud_ptr;//点云指针
        };
    }
}
#endif /* pcp_io_point_cloud_hpp */
