//
//  pcp_io_base.hpp
//  pcp
//
//  Created by wuhan on 2020/7/1.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef pcp_io_base_hpp
#define pcp_io_base_hpp
#include <string>
#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>                              //PCL PLY I/O
#include <pcl/io/pcd_io.h>                              //PCD 读写相关文件
#include <pcl/io/obj_io.h>                              //OBJ 文件读取
#include <pcl/point_types.h>                            //PCL 点类型头文件
#include <pcl/point_cloud.h>                            //点云头文件
#include <pcl/PolygonMesh.h>                            //mesh读取
#include "colors.hpp"
namespace whpcp{
    namespace io{
        class IOBase{
        public:
            IOBase();
            IOBase(const std::string& file_path);
            virtual ~IOBase();
            virtual int readData()=0;
            virtual int writeData(const std::string& file_path)=0;
            virtual std::string getFilePath()const;
            virtual std::string getFileType()const;
            virtual void setFilePath(std::string& file_path);
            virtual void setFileType(std::string& file_type);
        protected:
            std::string _file_path;//文件路径，包含文件路径，名称，类型
            std::string _file_type;//文件类型
        };
    }
}
#endif /* pcp_io_base_hpp */
