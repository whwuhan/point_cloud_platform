# PointCloudPlatform
### 1.简介  

这是一个基于PCL的点云处理平台，支持.obj .ply .pcd文件。

---

### 2.macOS下启动程序：   
```
% cd your_path/PointCloudPlatform/Build/Products/Debug  
% ./pcp  
```
![avatar](image/QQ20200630-123927@2x.png)  
---  
### 3.读取点云数据并显示点云数据  
```  
[Point Cloud Platform:]read your_point_cloud_data_path
[Point Cloud Platform:]show
```
![avatar](image/QQ20200630-145641@2x.png)
![avatar](image/QQ20200630-145851@2x.png)
--- 
### 4.归一化点云并显示  
```
[Point Cloud Platform:]read your_point_cloud_data_path
[Point Cloud Platform:]nor
[Point Cloud Platform:]show
```