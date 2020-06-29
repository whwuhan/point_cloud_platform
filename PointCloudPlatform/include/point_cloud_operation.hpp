//
//  point_cloud_operation.hpp
//  PointCloudPlatform
//
//  Created by wuhan on 2020/6/3.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef point_cloud_operation_hpp
#define point_cloud_operation_hpp

#include <stdio.h>

#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <float.h>                                      //浮点数的最大最小值
#include <stdio.h>
#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>                              //PCL PLY I/O
#include <pcl/io/pcd_io.h>                              //PCD 读写相关文件
#include <pcl/io/obj_io.h>                              //OBJ 文件读取
#include <pcl/point_types.h>                            //PCL 点类型头文件
#include <pcl/point_cloud.h>                            //点云头文件
#include <pcl/common/common.h>                          //getMinMax3D()函数
#include <pcl/registration/icp.h>                       //ICP算法
#include <pcl/PolygonMesh.h>                            //mesh读取
#include <pcl/io/vtk_lib_io.h>                          //loadPolygonFilePLY
#include <boost/algorithm/string.hpp>                   //boost split()
#include <pcl/filters/voxel_grid.h>                     //降采样
#include <pcl/filters/statistical_outlier_removal.h>    //去噪
//#include <pcl/console/time.h>                         // TicToc 记录时间
#include "typedefs.hpp"                                 //typedef
#include "colors.hpp"
namespace wh{
    namespace pco{
        class PointCloudOperation
        {
        private:
            std::string _file_path;                              //输入点云路径
            std::string _type;                                   //点云格式
            pcl::PointCloud<pcl::PointXYZ>::Ptr _point_cloud_ptr;//点云指针
        public:
            PointCloudOperation();
            PointCloudOperation(const std::string& file_name);
            pcl::PointCloud<PointT>::Ptr getPointCloudPtr()const;                    //获取点云指针
            //pcl::PointCloud<pcl::PointXYZ>::Ptr getOperatedPointCloudPtr()const;
            int readData(const std::string &file_path);                              //读取数据，成功返回1，否则-1
            //int getOriginPointCloud(const std::string &file_in, std::string &file_out="");//放到坐标原点，成功返回1，否则-1
            //归一化点云，成功返回1，否则-1目前采用AABB包围盒做归一化
            int getNormalizedPointCloud();
            //读取PTS文件，成功返回1，否则-1
            int loadPTSFlile(const std::string,pcl::PointCloud<pcl::PointXYZ>::Ptr = nullptr);
            int pst2pcd(const std::string &pst_name, const std::string &pcd_name);
            //降采样，成功返回1，否则-1
            int downSampling(std::string &file_in,std::string &file_out,float precision = 0.1f);
            int outliersRemoval(std::string &file_in, std::string &file_out);           //去噪，成功返回1，否则-1
            int ICP(std::string &file_model,std::string &file_raw,std::string &file_out);//ICP配准，成功返回1，否则-1
            void clear();//清理数据
            virtual ~PointCloudOperation();
        };
    }
}




#endif /* point_cloud_operation_hpp */
