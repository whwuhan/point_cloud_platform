//
//  pcp_io_base.cpp
//  pcp
//
//  Created by wuhan on 2020/7/1.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "../include/pcp_io_base.hpp"
using namespace whpcp;
using namespace io;
IOBase::IOBase():
_file_path(),_file_type(){}

IOBase::IOBase(const std::string& file_path):_file_path(file_path){
    //获取文件类型
    std::vector<std::string> vec_split;
    boost::split(vec_split,_file_path,boost::is_any_of("."),boost::token_compress_on);
    _file_type = vec_split[vec_split.size() - 1];
}

IOBase::~IOBase(){}

std::string IOBase::getFilePath()const{
    return _file_path;
}

std::string IOBase::getFileType()const{
    return _file_type;
}

void IOBase::setFilePath(std::string& file_path){
    _file_path = file_path;
}

void IOBase::setFileType(std::string& file_type){
    _file_type = file_type;
}
