cmake_minimum_required(VERSION 3.10)  # 要求 CMake 3.10 或更高版本

project(DatabaseProject LANGUAGES CXX)  # 项目名为 DatabaseProject

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(include)

# 查找所有源文件
file(GLOB SOURCES "src/*.cpp")

# 生成可执行文件
add_executable(database ${SOURCES})

# Windows 特定设置
if(WIN32)
    set_target_properties(database PROPERTIES SUFFIX ".exe")
endif()