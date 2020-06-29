//
//  Useage.hpp
//  pcp
//
//  Created by wuhan on 2020/6/7.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef Useage_hpp
#define Useage_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "colors.hpp"
namespace wh{
    namespace ua{
        class Usage{
        private:
            std::string _usage_path;
            std::fstream _fstream;
        public:
            Usage();
            Usage(std::string usage_path);
            int openUseage(const std::string& usage_path);       //打开使用手册文件，成功返回1，否则返回-1
            int showUseage();       //显示命令使用手册，成功读取返回1，否则返回-1
        };
    }
}


#endif /* Useage_hpp */
