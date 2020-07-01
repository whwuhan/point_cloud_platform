//
//  teat.cpp
//  pcp
//
//  Created by wuhan on 2020/6/30.
//  Copyright © 2020 wuhan. All rights reserved.
//
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include "include/point_cloud_operation.hpp"
#include "include/point_cloud_viewer.hpp"
#include "include/usage.hpp"
#include "include/colors.hpp"
int main(){
    wh::pco::PointCloudOperation pco;           //点云操作对象
    wh::pcv::PointCloudViewer pcv;              //点云显示对象
    pco.readData("/Users/wuhan/wuhan/Code/CppCode/PointCloudPlatform/PointCloudPlatform/1.ply");
    //-------添加测试代码------
    pco.writeData("/Users/wuhan/wuhan/Code/CppCode/PointCloudPlatform/PointCloudPlatform/3.ply");
    //-------测试代码结束------
//    pcv.readData(pco.getPointCloudPtr());
//    pcv.show();
    return 0;
}
