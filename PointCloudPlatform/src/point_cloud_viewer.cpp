//
//  point_cloud_viewer.cpp
//  PointCloudPlatform
//
//  Created by wuhan on 2020/6/3.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "point_cloud_viewer.hpp"
using namespace wh;
using namespace pcv;
PointCloudViewer::PointCloudViewer(
                                   double background_color_r,
                                   double background_color_g,
                                   double background_color_b,
                                   double point_color_r,
                                   double point_color_g,
                                   double point_color_b,
                                   int point_size):
_point_cloud_ptr(new PointCloudT),
_background_color_r(background_color_r),
_background_color_g(background_color_g),
_background_color_b(background_color_b),
_point_color_r(point_color_r),
_point_color_g(point_color_g),
_point_color_b(point_color_b),
_point_size(point_size){}

PointCloudViewer::PointCloudViewer(pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr,
                                   double background_color_r,
                                   double background_color_g,
                                   double background_color_b,
                                   double point_color_r,
                                   double point_color_g,
                                   double point_color_b,
                                   int point_size):
_point_cloud_ptr(point_cloud_ptr),
_background_color_r(background_color_r),
_background_color_g(background_color_g),
_background_color_b(background_color_b),
_point_color_r(point_color_r),
_point_color_g(point_color_g),
_point_color_b(point_color_b),
_point_size(point_size){_point_cloud_ptr = nullptr;}

PointCloudViewer::~PointCloudViewer(){}

int PointCloudViewer::show(){
    //创建窗口
    pcl::visualization::PCLVisualizer viewer("点云显示中...");
    //建立第一个视窗
    int view_port;
    //视窗参数 x,y最小值，x,y最大值，存入视窗ID的int变量
    viewer.createViewPort(0.0, 0.0, 1.0, 1.0, view_port);
    //设置窗口大小
    viewer.setSize(1280, 1024);
    //添加坐标轴
    viewer.addCoordinateSystem(0.1, 0, 0, 0, "ordinate", view_port);
    //用PointCloudColorHandlerCustom控制颜色
    pcl::visualization::PointCloudColorHandlerCustom<PointT>
    point_cloud_color_handler(_point_cloud_ptr,_point_color_r,_point_color_g,_point_color_b);//点云指针，RGB
    //设置背景颜色
    viewer.setBackgroundColor(_background_color_r, _background_color_r, _background_color_r);
    //viewer.setCameraPosition(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, view_port);//设置相机的位置、朝向、视窗ID
    //相机初始化
    //viewer.initCameraParameters();
    //添加点云 点云、颜色、名称、视窗
    viewer.addPointCloud(_point_cloud_ptr,point_cloud_color_handler,"point_cloud_1",view_port);
    //设置点云的渲染属性在添加点云之后
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, _point_size, "point_cloud_1");
    
    while(!viewer.wasStopped()){
        //使用旋转方法，并且旋转界面
        viewer.spinOnce();
    }
    return 1;
}

//读取显示数据成功返回1，否则-1
int PointCloudViewer::readData(const pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr){
    _point_cloud_ptr = point_cloud_ptr;
    if(point_cloud_ptr->size() == 0){
        return -1;
    }
    return 1;
}

int PointCloudViewer::setBackgroundColor(double r, double g, double b){
    if(r >= 0.0 && r <= 255.0){
        _background_color_r = r;
    }else{
        _background_color_r = 0.0;
    }
    
    if(g >= 0.0 && g <= 255.0){
        _background_color_g = g;
    }else{
        _background_color_g = 0.0;
    }
    
    if(b >= 0.0 && b <= 255.0){
        _background_color_b = b;
    }else{
        _background_color_b = 0.0;
    }
    return 1;
}

int PointCloudViewer::setPointCloudColor(double r, double g, double b){
    if(r >= 0.0 && r <= 255.0){
        _point_color_r = r;
    }else{
        _point_color_r = 255.0;
    }
    
    if(g >= 0.0 && g <= 255.0){
        _point_color_g = g;
    }else{
        _point_color_g = 255.0;
    }
    
    if(b >= 0.0 && b <= 255.0){
        _point_color_b = b;
    }else{
        _point_color_b = 255.0;
    }
    return 1;
}

int PointCloudViewer::setBackgroundColorR(double r){
    if(r >= 0.0 && r <= 255.0){
        _background_color_r = r;
    }else{
        _background_color_r = 0.0;
    }
    return 1;
}

int PointCloudViewer::setBackgroundColorG(double g){
    if(g >= 0.0 && g <= 255.0){
        _background_color_g = g;
    }else{
        _background_color_g = 0.0;
    }
    return 1;
}

int PointCloudViewer::setBackgroundColorB(double b){
    if(b >= 0.0 && b <= 255.0){
        _background_color_b = b;
    }else{
        _background_color_b = 0.0;
    }
    return 1;
}

int PointCloudViewer::setPointCloudColorR(double r){
    if(r >= 0.0 && r <= 255.0){
        _point_color_r = r;
    }else{
        _point_color_r = 255.0;
    }
    return 1;
}

int PointCloudViewer::setPointCloudColorG(double g){
    if(g >= 0.0 && g <= 255.0){
        _point_color_g = g;
    }else{
        _point_color_g = 255.0;
    }
    return 1;
}

int PointCloudViewer::setPointCloudColorB(double b){
    if(b >= 0.0 && b <= 255.0){
        _point_color_b = b;
    }else{
        _point_color_b = 255.0;
    }
    return 1;
}

int PointCloudViewer::setPointSize(int size){
    if(size >= 0 && size <= 10){
        _point_size = size;
    }else{
        _point_size = 10;
    }
    return 1;
}

void PointCloudViewer::clear(){
    //_point_cloud_ptr=nullptr;
    _background_color_r=0.0;
    _background_color_g=0.0;
    _background_color_b=0.0;
    _point_color_r=0;
    _point_color_g=255;
    _point_color_b=0;
    _point_size=3;
}
