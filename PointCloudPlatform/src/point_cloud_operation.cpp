//
//  point_cloud_operation.cpp
//  PointCloudPlatform
//
//  Created by wuhan on 2020/6/3.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "../include/point_cloud_operation.hpp"
using namespace wh;
using namespace pco;
//空构造函数
PointCloudOperation::PointCloudOperation():
_file_path(),_type(),_point_cloud_ptr(new PointCloudT){}
//读取数据构造函数
PointCloudOperation::PointCloudOperation(const std::string& file_name):
_point_cloud_ptr(new PointCloudT){
    readData(file_name);
}
//析构函数
PointCloudOperation::~PointCloudOperation(){};
//获取点云数据指针
pcl::PointCloud<PointT>::Ptr
PointCloudOperation::getPointCloudPtr()const{
    return _point_cloud_ptr;
}
//读取文件
int PointCloudOperation::readData(const std::string& file_path){
    _file_path = file_path;
    
    //获取格式
    std::vector<std::string> vec_temp;
    boost::split(vec_temp, _file_path, boost::is_any_of("."), boost::token_compress_on);
    _type = vec_temp[ vec_temp.size() - 1 ];
    
    std::cerr<<GREEN<<"正在读取点云..."<<RESET<<std::endl;
    
    if(_type == "pcd"){
        if(pcl::io::loadPCDFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败！！！"<<std::endl;
            return -1;
        }
    }else if(_type == "ply"){
        if(pcl::io::loadPLYFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败!!!"<<std::endl;
            return -1;
        }
    }else if(_type == "obj"){
        if(pcl::io::loadOBJFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败!!！"<<std::endl;
            return -1;
        }
    }else{
        std::cerr<<RED<<"读取点云格式或者文件路径"<<_type<<"错误!!!"<<RESET<<std::endl;
        return -1;
    }
    std::cerr<<GREEN<<"读取点云成功!"<<RESET<<std::endl;
    return 1;
}
//写入点云数据
int PointCloudOperation::writeData(){
    
    return 1;
}
//点云归一化
int PointCloudOperation::getNormalizedPointCloud(){
    if(_point_cloud_ptr->size() == 0){
        std::cerr<<RED<<"PLEASE READ POINTCLOUD DATA FIRST!!!"<<RESET<<std::endl;
        return -1;
    }
    //获取点云x,y,z轴的最大最小值
    PointT min_x_y_z;
    PointT max_x_y_z;
    pcl::getMinMax3D(*_point_cloud_ptr,min_x_y_z,max_x_y_z);
    //包围盒中心
    PointT center;
    center.x = (max_x_y_z.x + min_x_y_z.x) / 2.0;
    center.y = (max_x_y_z.y + min_x_y_z.y) / 2.0;
    center.z = (max_x_y_z.z + min_x_y_z.z) / 2.0;
    //点云放回坐标原点
    for(auto iter = _point_cloud_ptr->begin();iter != _point_cloud_ptr->end();iter++){
        iter->x = iter->x - center.x;
        iter->y = iter->y - center.y;
        iter->z = iter->z - center.z;
    }
    //归一化坐标到[0,1]
    //包围盒边长
    float x_ = max_x_y_z.x - min_x_y_z.x;
    float y_ = max_x_y_z.y - min_x_y_z.y;
    float z_ = max_x_y_z.z - min_x_y_z.z;
    //获取最长边
    float max_ = (x_>y_) ? x_ : y_;
    max_ = (max_>z_) ? max_ : z_;
    //放缩
    float scale = max_ / 2.0;
    for(auto iter = _point_cloud_ptr->begin();iter != _point_cloud_ptr->end();iter++){
        iter->x = iter->x / scale;
        iter->y = iter->y / scale;
        iter->z = iter->z / scale;
    }
    return 1;
}
//体素化降采样点云数据
int PointCloudOperation::downSamplingVoxel(float precision){
    if(_point_cloud_ptr->size() == 0){
        std::cerr<<RED<<"PLEASE READ POINTCLOUD DATA FIRST!!!"<<RESET<<std::endl;
        return -1;
    }
    //体素化降采样
    PointCloudT::Ptr cloud_filterd(new PointCloudT);//降采样后的点云
    pcl::VoxelGrid<PointT> vox;//注意模板参数是点类型，不是点云类型
    vox.setInputCloud(_point_cloud_ptr);
    vox.setLeafSize(precision,precision,precision);
    vox.filter(*cloud_filterd);
    _point_cloud_ptr=cloud_filterd;
    return 1;
}
//清理点云
void PointCloudOperation::clear(){
    _file_path = "";
    _type = "";
}


