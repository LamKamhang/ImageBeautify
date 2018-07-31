# Image Beautify

## 0. Build Requirements

如果你想自己编译此项目，你需要：

- QT version 5.9+
- OpenCV 3.2+

## 1.需求分析

本项目旨在设计实现一个同时面向专业人士和普通大众的图像处理工具，既实现各种基本的专业图像处理操作，又支持一键美化图片和各种图片滤镜操作，具有功能强大、目标群众广等特点。

## 2.功能实现

**图像基本操作**
- [x] 图像逻辑操作
- [x] 单通道选择
- [x] 灰度变换
- [x] 颜色空间变换
- [x] 图像二值化
- [x] 图像滤波
- [x] 图像边检测算法
- [x] 图像截取
- [x] 图像腐蚀、膨胀、开操作与闭操作
- [x] 图像直方图均衡化

**经典特效**

- [x] 自动增强
- [x] 柔光
- [x] 暖化
- [x] 黑白色
- [x] 锐化
- [x] 去雾
- [x] 柔和
- [x] 对比强烈
- [x] 智能绘色
- [x] 全彩
- [x] 反色

**艺术特效**

- [x] 浮雕
- [x] 雕刻
- [x] 虚幻
- [x] 惊悚
- [x] 磨砂质感
- [x] 手稿
- [x] 油画
- [x] 木刻
- [x] 回忆
- [x] 冰冻
- [x] 熔铸
- [x] 黑白漫画

## 3.项目概况

本项目基于`QT5.9`和`OpenCV3.2`实现。

整体架构基于`MVVM`(`Model-View-ViewModel`)实现。

在开发过程中，使用了`appveyor`工具实现了持续交互。

整体代码相对干净，如果你有意进行二次开发，可以看下面的介绍。

## 4.二次开发

每实现一个新功能需要增加一个对应的`command`类，command本身存在于ViewModel中，并提供get方法给View层进行set方法实现绑定，从而事先View->ViewModel的通信。

ViewModel执行Command的过程是调用Model中对应方法进行数据操作的过程。

在Model层完成数据操作之后，通过一个通知（绑定方式类似于command）来实现model与ViewModel的通信。

在此之后，ViewModel通过通知告诉View更新显示窗口。

二次开发只需增加相应的Command类并在model中实现功能，并讲command和notification绑定好即可。

## 5.框架介绍

较详细介绍在[DOC](https://github.com/LamKamhang/ImageBeautify/tree/master/doc)中。

#### 整体流程

在`View`层进行操作之后，会触发对应槽函数，该槽函数会准备好参数`Parameter`交给对应的`Command`，然后执行`exec()`这个command，exec会解出参数交给`ViewModel`层，`ViewModel`调用`Model`里对应的方法，进行数据操作，`Model`操作完之后会通知`ViewModel`更新显示数据，`ViewModel`会通知`View`刷新显示。

## 6.小组成员

- 组长：
  - **黄文璨**： `MVVM`框架搭建 `View`层以及`ViewModel`层的主要实现
- 组员：
  - **叶昕洋** ：滤镜算法层的主要实现
  - **林锦铿** ：`Appveyor`配置、`Model`层与`ViewModel`层的主要实现

