//
//  pcp_io_point_cloud.cpp
//  pcp
//
//  Created by wuhan on 2020/7/1.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "pcp_io_point_cloud.hpp"
using namespace whpcp;
using namespace io;
IOPointCloud::IOPointCloud()
:IOBase(),_point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>){}

IOPointCloud::IOPointCloud(const std::string& file_path)
:IOBase(file_path),_point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>){
    readData();
}

IOPointCloud::~IOPointCloud(){}

int IOPointCloud::readData(){
    if(_file_type == "" && _file_path ==""){
        return -1;
    }
    if(_file_type == "pcd"){
        if(pcl::io::loadPCDFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else if(_file_type == "ply"){
        if(pcl::io::loadPLYFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else if(_file_type == "obj"){
        if(pcl::io::loadOBJFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else{
        return -1;
    }
    return 1;
}

int IOPointCloud::writeData(const std::string& file_path){
    if(_file_type == "" && _file_path == "" && file_path == ""){
        return -1;
    }
    if(_file_type == "pcd"){
        if(pcl::io::loadPCDFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else if(_file_type == "ply"){
        if(pcl::io::loadPLYFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else if(_file_type == "obj"){
        if(pcl::io::loadOBJFile(_file_path, *_point_cloud_ptr) == -1){
            return -1;
        }
    }else{
        return -1;
    }
    return 1;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr
IOPointCloud::getPointCloudPtr()const{
    return _point_cloud_ptr;
}

void IOPointCloud::setPointCloudPtr(pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr){
    _point_cloud_ptr = point_cloud_ptr;
}
