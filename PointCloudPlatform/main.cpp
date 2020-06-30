#include <iostream>
#include <string>
#include <vector>
#include "include/point_cloud_operation.hpp"
#include "include/point_cloud_viewer.hpp"
#include "include/usage.hpp"
#include "include/colors.hpp"
int main(){
    std::string command("");                    //输入的命令和参数
    std::vector<std::string> command_split;     //分解命令和参数
    unsigned long command_size = 0;             //命令行size
    wh::pco::PointCloudOperation pco;           //点云操作对象
    wh::pcv::PointCloudViewer pcv;              //点云显示对象
    wh::ua::Usage ua;                           //使用手册管理对象
    ua.openUseage("./usage/introduction");
    ua.showUseage();
    do{
        std::cerr<<WHITE<<"[Point Cloud Platform:] "<<RESET;
        //获取命令
        getline(cin, command);
        boost::split(command_split, command, boost::is_any_of(" "), boost::token_compress_on);
        command_size = command_split.size();    //命令行size
        //打开手册
        if(command_split[0] == ""){
            ua.openUseage("./usage/introduction");
            ua.showUseage();
            continue;
        }
        //罗列所有命令
        if(command_split[0] == "commands"){
            ua.openUseage("./usage/commands");
            ua.showUseage();
            continue;
        }
        //man
        if(command_split[0] == "man"){
            if(command_size == 1){
                ua.openUseage("./usage/man");
                ua.showUseage();
                continue;
            }
            for(int i = 1;i < command_size;i++){
                if(ua.openUseage("./usage/"+command_split[i]) == 1){
                    ua.showUseage();
                }else{
                    std::cerr<<RED<<"\""<<command_split[i]<<"\""<<" THIS COMMAND DOES NOT EXISTS!!!"<<RESET<<std::endl;
                }
            }
            continue;
        }
        //read
        if(command_split[0] == "read" || command_split[0] == "rd"){
            for(int i = 1;i < command_size;i++){
                if(i == 1 && pco.readData(command_split[1]) == 1){
                    continue;
                }
                if(command_split[i]=="-pr" && (++i<command_size)){pcv.setPointCloudColorR(atof(command_split[i].c_str()));}
                if(command_split[i]=="-pg" && (++i<command_size)){pcv.setPointCloudColorG(atof(command_split[i].c_str()));}
                if(command_split[i]=="-pb" && (++i<command_size)){pcv.setPointCloudColorB(atof(command_split[i].c_str()));}
                if(command_split[i]=="-bgr" && (++i<command_size)){pcv.setBackgroundColorR(atof(command_split[i].c_str()));}
                if(command_split[i]=="-bgg" &&   (++i<command_size)){pcv.setBackgroundColorG(atof(command_split[i].c_str()));}
                if(command_split[i]=="-bgb" && (++i<command_size)){pcv.setBackgroundColorB(atof(command_split[i].c_str()));}
            }
            continue;
        }
        //show
        if(command_split[0] == "show"){
            if(pco.getPointCloudPtr()->size() == 0){
                std::cerr<<RED<<"PLEASE READ POINTCLOUD DATA FIRST!!!"<<RESET<<std::endl;
                continue;
            }
            pcv.readData(pco.getPointCloudPtr());//读取显示点云
            pcv.show();
            continue;
        }
        //nor归一化点云
        if(command_split[0] == "nor"){
            if(pco.getPointCloudPtr()->size() == 0){
                std::cerr<<RED<<"PLEASE READ POINTCLOUD DATA FIRST!!!"<<RESET<<std::endl;
                continue;
            }
            if(pco.getNormalizedPointCloud() == 1){
                std::cerr<<YELLOW<<"Point cloud has been normalized!!!"<<RESET<<std::endl;
                continue;
            }
        }
        //clear清除点云
        if(command_split[0] == "clear"){
            pco.clear();
            pcv.clear();
            std::cerr<<YELLOW<<"Clear all!"<<RESET<<std::endl;
            continue;
        }
        //exit退出程序
        if(command_split[0] == "exit"){
            std::cerr<<YELLOW<<"Bye~"<<RESET<<std::endl;
            continue;
        }
        //所有命令都不匹配
        for(int i = 0;i < command_size;i++){
                std::cerr<<RED<<"\""<<command_split[i]<<"\""<< " THIS COMMAND DOES NOT EXISTS!!!"<<RESET<<std::endl;
        }
    }while(command_split[0] != "exit");
    return 0;
}



