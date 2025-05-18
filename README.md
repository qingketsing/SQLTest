# 基于Morden C++的数据库系统

Author : 刘家蔚

ID :  10242305

Date : 2025/5/18

Description:

本人是数学学院24级本科生刘家蔚，现已转入计算机信息安全系，在学习完C++后，对C++颇为感兴趣，外加之前曾经了解过一些数据库的基本知识，在补充了部分Morden C++知识后决定复现一下基本的数据库。

本程序为简单的数据库实现，DataBase为数据库的主体，DatabaseTable为数据库的表格，由于本项目使用了新版本C++的文件处理，故本程序需要使用C++ 17 以上的标准编译，同时建议使用CMake。

本项目可以保证是由作者一人完成，如有疑惑，可以联系本人，联系方式如下。在项目构建过程中出现问题或存在bug，也欢迎联系作者，将在1-3个工作日内回复。

我的邮箱:ljw329426@163.com

Tele：13371057169

QQ：2660518718

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

感谢老师在本学期的辛勤工作，也感谢您能看到这里。祝您工作顺利，生活愉快。

此致，

敬礼。