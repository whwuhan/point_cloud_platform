//
//  point_cloud_viewer.hpp
//  PointCloudPlatform
//
//  Created by wuhan on 2020/6/3.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef point_cloud_viewer_hpp
#define point_cloud_viewer_hpp
#include <pcl/visualization/pcl_visualizer.h>
#include "typedefs.hpp" 
#include <stdio.h>
namespace wh{
    namespace pcv{
        class PointCloudViewer{
        private:
            pcl::PointCloud<pcl::PointXYZ>::Ptr _point_cloud_ptr;
            double _background_color_r;
            double _background_color_g;
            double _background_color_b;
            double _point_color_r;
            double _point_color_g;
            double _point_color_b;
            int _point_size;        //点的大小
        public:
            PointCloudViewer(double background_color_r=0.0,
                             double background_color_g=0.0,
                             double background_color_b=0.0,
                             double point_color_r=0.0,
                             double point_color_g=255.0,
                             double point_color_b=0.0,
                             int point_size=3);
            PointCloudViewer(pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr,
                             double background_color_r=0.0,
                             double background_color_g=0.0,
                             double background_color_b=0.0,
                             double point_color_r=0,
                             double point_color_g=255,
                             double point_color_b=0,
                             int point_size=3);
            ~PointCloudViewer();
            int readData(const pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr); //读取显示点云成功返回1，否则-1
            int show();         //显示窗口成功return 1否则-1
            int setBackgroundColor(double r, double g, double b);
            int setPointCloudColor(double r, double g, double b);
            int setBackgroundColorR(double r);
            int setBackgroundColorG(double g);
            int setBackgroundColorB(double b);
            int setPointCloudColorR(double r);
            int setPointCloudColorG(double g);
            int setPointCloudColorB(double b);
            int setPointSize(int point_size);
            void clear();
        };
    }
}

#endif /* point_cloud_viewer_hpp */

