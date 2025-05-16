/*
Date : 2025/5/15
Author : Liu jiawei
Description : Table类的实现头文件
*/
#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include "BPTree.h"

enum class DataType {
    INT,
    FLOAT,
    STRING
};

struct Column{
    std::string name; // 列名
    DataType type; // 数据类型
    bool isPrimaryKey; // 是否主键
};

class Table{
private:
    
};

#endif