# 开发语言

使用Qt/C++和OpenCV库进行开发。

# 项目管理

|      名称      |      工具       |
| :------------: | :-------------: |
|    版本控制    |   Git, GitHub   |
|    持续集成    |    Appveyor     |
|    构建工具    |  CMake, QMake   |
|    规范检查    |     cpplint     |
|    静态分析    |    cppcheck     |
|   复杂度分析   |     cppncss     |
| 单元测试覆盖率 | OpenCppCoverage |

# 具体实现

### 软件框架

软件整体采用`MVVM`的模式框架，达到多人高效协同的效果。

### GUI图形界面

采用`Qt version 5.9+`实现桌面客户端。具体使用Qt Creator设计师工具，合理搭配QLabel、QWidget、QDialog、QComboBox、QSlider、QVBoxLayout、QHBoxLayout、QGroupBox、QScrollArea、QPushButton等Qt组件，参考了Qt官方关于图像显示的例子`Image Viewer`。

### 图像处理算法

采用`OpenCV 3.2.4`的内置图像处理库，结合专业的图像处理知识，如图像逻辑操作、单通道选择、灰度变换、颜色空间变换、图像二值化、图像滤波、图像边缘检测、图像形态学操作、直方图操作等，在实现专业图像处理工具的同时设计实现多种不同风格的一键美化功能，如浮雕、雕刻、虚幻、惊悚、磨砂质感、手稿、油画、木刻、回忆、冰冻、熔铸、黑白漫画等。