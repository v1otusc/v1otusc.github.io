---
layout: post
title: ROS 中常见 sensor_msgs
---

[VINS-Mono代码解读——各种数据结构 sensor_msgs](https://blog.csdn.net/qq_41839222/article/details/86030962)

<!-- TOC -->

- [标准数据结构](#标准数据结构)
  - [1. std_msgs/Header](#1-std_msgsheader)
  - [2. sensor_msgs::ImageConsterPtr](#2-sensor_msgsimageconsterptr)
  - [3. sensor_msgs::PointCloudPtr (feature_points)](#3-sensor_msgspointcloudptr-feature_points)
  - [4. sensor_msgs::PointCloudPtr (vins mono --> msg_match_points)](#4-sensor_msgspointcloudptr-vins-mono----msg_match_points)
  - [5. sensor_msgs::ImuConstPtr](#5-sensor_msgsimuconstptr)
- [vins 代码中的组合数据结构](#vins-代码中的组合数据结构)
  - [1. measurements](#1-measurements)
  - [2. map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> image](#2-mapint-vectorpairint-eigenmatrixdouble-7-1-image)
  - [3. map<double, ImageFrame> all_image_frame](#3-mapdouble-imageframe-all_image_frame)

<!-- /TOC -->

## 标准数据结构

### 1. std_msgs/Header

对应文件 std_msgs/Header.msg，Image/PointCloud/IMU 等各种传感器数据结构中都会出现的头信息。

```yaml
# sequence ID: consecutively increasing ID 
uint32 seq 
# 时间戳  stamp.sec: seconds since epoch / stamp.nsec: nanoseconds since stamp_secs
time stamp 
#坐标系ID
string frame_id 
```

### 2. sensor_msgs::ImageConsterPtr

对应文件 sensor_msgs/Image.msg，是 vins(feature_trackers_node.cpp) 中回调函数 img_callback() 的输入，表示一幅图像。

```yaml
# 头信息
std_msgs/Header header
# image height, number of rows 
uint32 height         
# image width, number of columns
uint32 width          
# Encoding of pixels -- channel meaning, ordering, size
# taken from the list of strings in include/sensor_msgs/image_encodings.h
string encoding       
#大端 big endian(从低地址到高地址的顺序存放数据的高位字节到低位字节)和小端 little endian                      
uint8 is_bigendian    
# Full row length in bytes
uint32 step           
# actual matrix data, size is (step * rows)
uint8[] data          
```

### 3. sensor_msgs::PointCloudPtr (feature_points)

对应文件 sensor_msgs/Image.msg，在 feature_trackers.cpp 中 img_callback() 中创建 feature_points 并封装，在 main() 中发布为话题 “/feature_tracker/feature”，包含一帧图像中特征点信息。

```yaml
# 头信息
std_msgs/Header header
# 在 vins 中的使用为
# feature_points->header = img_msg->header;
# feature_points->header.frame_id = "world";

# 3D 点 (x,y,z)
geometry_msgs/Point32[]

# [特征点的 ID, 像素坐标 u,v, 速度 vx,vy]
sensor_msgs/ChannelFloat32[] channels
# 在 vins 中的使用为
# feature_points->channels.push_back(id_of_point);
# feature_points->channels.push_back(u_of_point);
# feature_points->channels.push_back(v_of_point);
# feature_points->channels.push_back(velocity_x_of_point);
# feature_points->channels.push_back(velocity_y_of_point);
```

### 4. sensor_msgs::PointCloudPtr (vins mono --> msg_match_points)

数据格式和之前的 feature_points 一样，但是 channels 不一样，在 keyframe.cpp 中的 findConnection() 中建立并封装成 msg_match_points，在 pose_graph_node.cpp 的 main() 中发布话题 “/pose_graph/match_points”
主要包含重定位的两帧间匹配点和匹配关系（变换矩阵）

```yaml
# 头信息
std_msgs/Header header 
# 在 vins 中
# msg_match_points.header.stamp = ros::Time(time_stamp);

# 3D 点 (x,y,z)
geometry_msgs/Point32[] points 

# [重定位帧的平移向量 T 的 x,y,z，旋转四元数 w,x,y,z 和索引值]
sensor_msgs/ChannelFloat32[] channels  
# t_q_index.values.push_back(T.x());
# t_q_index.values.push_back(T.y());
# t_q_index.values.push_back(T.z());
# t_q_index.values.push_back(Q.w());
# t_q_index.values.push_back(Q.x());
# t_q_index.values.push_back(Q.y());
# t_q_index.values.push_back(Q.z());
# t_q_index.values.push_back(index);
# msg_match_points.channels.push_back(t_q_index);
```

### 5. sensor_msgs::ImuConstPtr

对应文件 sensor_msgs/Imu.msg，IMU 信息的标准数据结构

```yaml
# 头信息
Header header
# 四元数[x,y,z,w]
geometry_msgs/Quaternion orientation
# 为什么是 [9] 而不是 [16] 对应的协方差矩阵，自由度为 3?
float64[9] orientation_covariance
# 角速度[x,y,z]轴
geometry_msgs/Vector3 angular_velocity
# 对应协方差矩阵，Row major(行主序) about x, y, z axes
float64[9] angular_velocity_covariance
# 线性加速度[x,y,z]
geometry_msgs/Vector3 linear_acceleration
# 对应协方差矩阵 Row major x, y z 
float64[9] linear_acceleration_covariance
```

## vins 代码中的组合数据结构

### 1. measurements

```c++
std::vector<std::pair<std::vector<sensor_msgs::ImuConstPtr>, sensor_msgs::PointCloudConstPtr>> measurements;
```

estimator_node.cpp 中 getMeasurements() 函数将对 imu 和图像数据进行初步对齐得到的数据结构，确保图像关联着对应时间戳内的所有 IMU 数据
sensor_msgs::PointCloudConstPtr 表示某一帧图像的 feature_points，
std::vector<sensor_msgs::ImuConstPtr> 表示当前帧和上一帧时间间隔中的所有IMU数据
将两者组合成一个数据结构，并构建元素为这种结构的 vector 进行存储。

### 2. map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> image

在 estimator.cpp 中的 process() 中被建立，在 Estimator::processImage() 中被调用
作用是建立每个特征点 (camera_id,[x,y,z,u,v,vx,vy]) 构成的 map，索引为 feature_id。

```c++
for (unsigned int i = 0; i < img_msg->points.size(); i++) {
  // 一个四舍五入的 trick, double / float 到 int 转换时直接取整数，为了让小数部分大于 0.5 可以进位（小于 0.5 被舍去）
  int v = img_msg->channels[0].values[i] + 0.5;
  int feature_id = v / NUM_OF_CAM;
  int camera_id = v % NUM_OF_CAM;
  double x = img_msg->points[i].x;
  double y = img_msg->points[i].y;
  double z = img_msg->points[i].z;
  double p_u = img_msg->channels[1].values[i];
  double p_v = img_msg->channels[2].values[i];
  double velocity_x = img_msg->channels[3].values[i];
  double velocity_y = img_msg->channels[4].values[i];
  ROS_ASSERT(z == 1);
  Eigen::Matrix<double, 7, 1> xyz_uv_velocity;
  xyz_uv_velocity << x, y, z, p_u, p_v, velocity_x, velocity_y;
  image[feature_id].emplace_back(camera_id,  xyz_uv_velocity);
}
```

### 3. map<double, ImageFrame> all_image_frame

在 estimator.h 中作为 class Estimator 的属性，key 是图像帧的时间戳，value 是图像帧类。

图像帧类可由图像帧的特征点与时间戳构造，此外还保存了位姿 R t，预积分对象 pre_integration，是否是关键帧。

```c++
class ImageFrame
{
  public:
    ImageFrame(){};
    ImageFrame(const map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>>& _points, double _t):t{_t},is_key_frame{false} {
      points = _points;
    };
    map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> points;
    double t;
    Matrix3d R;
    Vector3d T;
    IntegrationBase *pre_integration;
    bool is_key_frame;
};
```