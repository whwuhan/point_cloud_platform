//
//  Useage.cpp
//  pcp
//
//  Created by wuhan on 2020/6/7.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "../include/usage.hpp"
using namespace wh;
using namespace ua;
Usage::Usage():_usage_path(),_fstream(){}

Usage::Usage(std::string file_path):
_usage_path(file_path),
_fstream(file_path, std::ios::in | std::ios::out){}

int Usage::openUseage(const std::string& usage_path){//打开使用手册
    _usage_path = usage_path;
    _fstream.open(usage_path, std::ios::in);
    if(_fstream.is_open()){
        return 1;
    }
    return -1;
}

int Usage::showUseage(){//显示使用手册
    if(!_fstream.is_open()){
        return -1;
    }
    std::string str_temp;
    std::cout<<YELLOW<<std::endl;
    while(getline(_fstream,str_temp)){
        std::cout<<str_temp<<std::endl;
    }
    std::cout<<RESET<<std::endl;
    _usage_path = "";
    _fstream.close();
    return 1;
}
