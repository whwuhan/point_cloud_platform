//
//  polygon_operation.hpp
//  pcp
//
//  Created by wuhan on 2020/6/30.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef polygon_operation_hpp
#define polygon_operation_hpp

#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>                              //PCL PLY I/O
#include <pcl/io/pcd_io.h>                              //PCD 读写相关文件
#include <pcl/io/obj_io.h>                              //OBJ 文件读取
namespace wh{
    namespace plgo{
        class PolygonOperation{
        private:
            std::string _file_path;//mesh路径
            std::string _file_type;//mesh格式
            pcl::PolygonMesh::Ptr _polygon_mesh_ptr;//mesh指针
        public:
            PolygonOperation();
            PolygonOperation(const std::string& file_name);
            pcl::PolygonMesh::Ptr getPolygonMeshPtr()const;//获取Mesh指针
            int readData(const std::string& file_path);//读取数据，成功返回1，否则-1
            int writeData(const std::string& file_path);//将操作后的点云数据写入硬盘，成功返回1，否则返回-1
        };
    }
}

#endif /* polygon_operation_hpp */
