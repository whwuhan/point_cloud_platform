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
_file_path(),_file_type(),_point_cloud_ptr(new PointCloudT){}
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
    //获取格式和名称
    std::vector<std::string> vec_temp;
    boost::split(vec_temp, _file_path, boost::is_any_of("."), boost::token_compress_on);
    _file_type = vec_temp[ vec_temp.size() - 1 ];
    
    
    std::cerr<<GREEN<<"正在读取点云..."<<RESET<<std::endl;
    
    if(_file_type == "pcd"){
        if(pcl::io::loadPCDFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败！！！"<<std::endl;
            return -1;
        }
    }else if(_file_type == "ply"){
        if(pcl::io::loadPLYFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败!!!"<<std::endl;
            return -1;
        }
    }else if(_file_type == "obj"){
        if(pcl::io::loadOBJFile(_file_path, *_point_cloud_ptr) == -1){
            std::cerr<<RED<<"读取点云"<<_file_path<<RESET<<"失败!!！"<<std::endl;
            return -1;
        }
    }else{
        std::cerr<<RED<<"读取点云格式或者文件路径"<<_file_type<<"错误!!!"<<RESET<<std::endl;
        return -1;
    }
    std::cerr<<GREEN<<"读取点云成功!"<<RESET<<std::endl;
    return 1;
}
//写入点云数据
int PointCloudOperation::writeData(const std::string& file_path){
    std::vector<std::string> vec_temp;
    boost::split(vec_temp, file_path, boost::is_any_of("."), boost::token_compress_on);
    std::string type = vec_temp[ vec_temp.size() - 1 ];
    
    if(type == "pcd"){
        if(pcl::io::savePCDFile(file_path,*_point_cloud_ptr) == -1){
            std::cerr<<RED<<"储存点云"<<file_path<<RESET<<"失败！！！"<<std::endl;
            return -1;
        }
    }else if(type == "ply"){
        if(pcl::io::savePLYFile(file_path,*_point_cloud_ptr) == -1){
            std::cerr<<RED<<"储存点云"<<file_path<<RESET<<"失败！！！"<<std::endl;
            return -1;
        }
    }else{
        std::cerr<<RED<<"存储点云格式或者文件路径"<<_file_type<<"错误!!!"<<RESET<<std::endl;
        return -1;
    }
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
//泊松重建
pcl::PolygonMesh::Ptr PointCloudOperation::surfaceReconstructionPoisson(int k,int degree){
    //计算法向量
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);//带法线的点云
    pcl::NormalEstimation<pcl::PointXYZ,pcl::Normal> normal_estimation;//法线估计对象
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);//法线点云
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);//kd树搜索k近邻
    kdtree->setInputCloud(_point_cloud_ptr);
    //设置法线估计对象的参数
    normal_estimation.setInputCloud(_point_cloud_ptr);
    normal_estimation.setSearchMethod(kdtree);//设置法线估计对象k近邻居的搜索方法
    normal_estimation.setKSearch(k);//设置k近邻居的k值
    normal_estimation.compute(*normals);//将法线存入normals
    pcl::concatenateFields(*_point_cloud_ptr,*normals,*cloud_with_normals);//将点云和对应法线放入cloud_with_normals
    //开始泊松重建
    pcl::search::KdTree<pcl::PointNormal>::Ptr kdtree2(new pcl::search::KdTree<pcl::PointNormal>);
    kdtree2->setInputCloud(cloud_with_normals);
    //创建Poisson对象并设置参数
    pcl::Poisson<pcl::PointNormal> poisson;
    poisson.setConfidence(false);//是否采用法向量大小作为置信信息
    poisson.setDegree(degree);//degree值越大越精细，degree值越大越精细,范围[1，5]
    poisson.setDepth(8);//树的最大深度，求解2^d x 2^d x 2^d立方体元。由于八叉树自适应采样密度，指定值仅为最大深度。
    poisson.setIsoDivide(8);//用于提取ISO等值面的算法的深度
    poisson.setManifold(false); //是否添加多边形的重心，当多边形三角化时。设置流行标志，如果设置为true，则对多边形进行细分三角话时添加重心，设置false则不添加
    poisson.setOutputPolygons(false);//是否输出多边形网格（而不是三角化移动立方体的结果）
    poisson.setSamplesPerNode(3.0);//设置落入一个八叉树结点中的样本点的最小数量。无噪声，[1.0-5.0]有噪声[15.0-20.0]平滑
    poisson.setScale(1.25); //设置用于重构的立方体直径和样本边界立方体直径的比率。
    poisson.setSolverDivide(8); //设置求解线性方程组的Gauss-Seidel迭代方法的深度
    //poisson.setIndices();
    //设置搜索方法和输入点云
    poisson.setSearchMethod(kdtree2);
    poisson.setInputCloud(cloud_with_normals);
    
    pcl::PolygonMesh::Ptr res_mesh_ptr(new pcl::PolygonMesh);//创建多边形网格存储结果
    poisson.performReconstruction(*res_mesh_ptr);//泊松重建
    // 显示结果图
    
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D viewer")) ;
    viewer->setBackgroundColor(0 , 0 , 0) ;
    viewer->addPolygonMesh(*res_mesh_ptr , "res_mesh") ;
    viewer->addCoordinateSystem (0.1);
    while(!viewer->wasStopped()){
        viewer->spinOnce(100) ;
        boost::this_thread::sleep(boost::posix_time::microseconds(100000)) ;
    }
    
    //保存网格图
    //pcl::io::savePLYFile("result.ply", mesh);
    return res_mesh_ptr;
}
pcl::PolygonMesh::Ptr PointCloudOperation::surfaceReconstructionGP3(int k,float radius){
    //计算法向量
    pcl::NormalEstimation<pcl::PointXYZ,pcl::Normal> normal_estimation;//法向量估计对象
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
    kdtree->setInputCloud(_point_cloud_ptr);
    normal_estimation.setInputCloud(_point_cloud_ptr);
    normal_estimation.setSearchMethod(kdtree);
    normal_estimation.setKSearch(k);
    normal_estimation.compute(*normals);
    //将法线和点云合在一起
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields(*_point_cloud_ptr,*normals,*cloud_with_normals);
    //创建搜索树
    pcl::search::KdTree<pcl::PointNormal>::Ptr kdtree2(new pcl::search::KdTree<pcl::PointNormal>);
    kdtree2->setInputCloud(cloud_with_normals);
    //开始GP3重建
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh::Ptr res_mesh_ptr(new pcl::PolygonMesh);//重建结果
    //设置参数
    gp3.setSearchRadius(radius);//设置两点之间的最大距离
    gp3.setMu(2.5);
    gp3.setMaximumNearestNeighbors(100);
    gp3.setMaximumSurfaceAngle(M_PI / 4); // 45 degrees
    gp3.setMinimumAngle(M_PI / 18); // 10 degrees
    gp3.setMaximumAngle(2 * M_PI / 3); // 120 degrees
    gp3.setNormalConsistency(false);
    //得到结果
    gp3.setInputCloud(cloud_with_normals);
    gp3.setSearchMethod(kdtree2);
    gp3.reconstruct(*res_mesh_ptr);
    //新增点信息
    std::vector<int> parts = gp3.getPartIDs();
    std::vector<int> states = gp3.getPointStates();
    //显示结果
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D viewer")) ;
    viewer->setBackgroundColor(0 , 0 , 0) ;
    viewer->addPolygonMesh(*res_mesh_ptr , "res_mesh") ;
    viewer->addCoordinateSystem (0.1);
    while(!viewer->wasStopped()){
        viewer->spinOnce(100) ;
        boost::this_thread::sleep(boost::posix_time::microseconds(100000)) ;
    }
    //保存网格图
    //pcl::io::savePLYFile("result.ply", mesh);
    return res_mesh_ptr;
}
//清理点云
void PointCloudOperation::clear(){
    _file_path = "";
    _file_type = "";
    pcl::PointCloud<pcl::PointXYZ>::Ptr temp(new pcl::PointCloud<pcl::PointXYZ>);
    _point_cloud_ptr = temp;
}


