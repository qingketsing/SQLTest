# 基于Morden C++的数据库系统

Author : Qingke

Date : 2025/5/18

Description:

本程序为简单的数据库实现，DataBase为数据库的主体，DatabaseTable为数据库的表格(包含多态和重载)，由于本项目使用了新版本C++的文件处理，故本程序需要使用C++ 17 以上的标准编译，同时建议使用CMake。
在项目构建过程中出现问题或存在bug，也欢迎联系作者，将在1-3个工作日内回复。

我的邮箱:ljw329426@163.com

个人主页:qingke12138.top

Github id: QingkeTsing

AI声明：本项目部分内容使用了AI代码补全，补全工具为Github提供的Copilot,使用AI的部分为DataBase.cpp中的loadTableFromFile和processDataLine。可能会影响代码AI使用率，特此声明。

windows系统的构建操作步骤如下:
1. 在该文件的根目录下打开cmd
2. mkdir build
3. cd build
4. cmake .. -G "MinGW Makefiles"
5. mingw32-make

Linux/MacOS 下的构建操作如下:
1. mkdir build
2. cd build
3. cmake ..
4. make

构建完成后，请按照相应的系统运行
```
# Windows
build\database.exe

# Linux/macOS
build/database
```


由于个人能力原因，项目体量不大，学艺不精，仍需努力，后续会在github中持续更新。