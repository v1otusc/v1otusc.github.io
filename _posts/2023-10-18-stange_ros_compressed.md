---
layout: post
title: ROS 提取 sensor_msgs/CompressedImage
---

提取 SUPS 数据集中 sensor_msgs/CompressedImage 类型图像，rosbag info 的信息如下：

```
$ rosbag info ALoop_fast_disturbed_stereo.bag 
path:        ALoop_fast_disturbed_stereo.bag
version:     2.0
duration:    2:51s (171s)
start:       Mar 22 2022 13:43:11.68 (1647927791.68)
end:         Mar 22 2022 13:46:03.23 (1647927963.23)
size:        3.5 GB
messages:    36874
compression: none [4071/4071 chunks]
types:       nav_msgs/Odometry           [cd5e73d190d741a2f92e81eda573aca7]
             sensor_msgs/CompressedImage [8f7a12909da2c9d3332d540a0977563f]
             sensor_msgs/Imu             [6a62c6daae103f4ff57a132d6f95cec2]
             sensor_msgs/PointCloud2     [1158d486dd51d683ce2f1be655c3c181]
topics:      /camera/depth             2571 msgs    : sensor_msgs/CompressedImage
             /camera/main              3426 msgs    : sensor_msgs/CompressedImage
             /camera/main_right        3426 msgs    : sensor_msgs/CompressedImage
             /camera/main_right_seg    3426 msgs    : sensor_msgs/CompressedImage
             /camera/main_seg          3426 msgs    : sensor_msgs/CompressedImage
             /gps_odom                 5094 msgs    : nav_msgs/Odometry          
             /imu                     14306 msgs    : sensor_msgs/Imu            
             /lidar                    1199 msgs    : sensor_msgs/PointCloud2

```

一般播放包数据后，只需要进行

```
rosrun image_view extract_images _sec_per_frame:=0.5 _image_transport:=compressed image:=/camera/main_seg
```

即可，其中 _sec_per_frame:=0.5 表示时间间隔，_image_transport:=compressed 表示提取压缩图像

但是，我猜 image_transport 会对 topic 名称做判断(不仅是通过 8f7a12909da2c9d3332d540a0977563f 这样的 hash 值)，所以 extract_iamges 这一步不变，但是 rosbag 的时候，需要 rename 一下，进行一步 hack: 

```
rosbag play BLoop_fast_disturbed_stereo.bag /camera/main_seg:=/camera/main_seg/compressed
```

之后 extract_images 的行为才会符合预期...
