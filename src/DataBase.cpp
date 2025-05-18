#include "DataBase.h"
#include "DatabaseTable.h"
#include <stdexcept>
#include <filesystem>
namespace fs = std::filesystem;

int Database::createTable(std::string tableName){
    if(tables.find(tableName) != tables.end()){
        std::cerr << "Table " << tableName << " already exists." << std::endl;
        return -1;
    }
    DatabaseTable newTable;
    newTable.setTableName(tableName);
    tables[tableName] = newTable;
    std::cout << "Table " << tableName << " created successfully." << std::endl;
    return 0;
}

int Database::dropTable(std::string tableName){
    if(tables.find(tableName) == tables.end()){
        std::cerr << "Table " << tableName << "doesn't exist." << std::endl;
        return -1;
    }
    tables.erase(tableName);
    // 删除对应的文件
    std::string filename = tableName + ".tbl";
    if (fs::exists(filename)) {
        fs::remove(filename);
        std::cout << "File " << filename << " deleted successfully." << std::endl;
    } else {
        std::cerr << "File " << filename << " does not exist." << std::endl;
    }
    std::cout << "Table " << tableName << " dropped successfully." << std::endl;
    return 0;
}

DatabaseTable & Database::getTable(std::string tableName){
    if(tables.find(tableName) != tables.end()){
        return tables[tableName];
    }
    std::cerr << "Table " << tableName << " doesn't exist." << std::endl;
    throw std::runtime_error("Table not found");
}

int Database::printAllTables(){
    if(tables.empty()){
        std::cout << "No tables in the database." << std::endl;
        return -1;
    }
    int index = 0;
    for(auto &table : tables){
        std::cout << "Table " << index++ << ":" << table.first << std::endl;
        table.second.printTable();
        std::cout << "------------------------" << std::endl;
    }
    return 0;
}

int Database::saveDatabase() {
    if (tables.empty()) {
        std::cerr << "No tables to save." << std::endl;
        return -1;
    }
    for (auto& tablePair : tables) {
        const std::string& tableName = tablePair.first;
        const DatabaseTable& table = tablePair.second;
        // 生成文件名（例如：Users.tbl）
        std::string filename = tableName + ".tbl";
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Failed to open file " << filename << " for writing." << std::endl;
            return -2;  // 文件打开失败
        }
        // 写入表名
        outFile << "TableName: " << table.getTableName() << "\n";
        // 写入列定义
        const auto& columns = table.getColumns();
        for (const auto& col : columns) {
            outFile << "Column: " << col.name << "," << col.type << "," << col.isPrimaryKey << "\n";
        }
        // 写入数据行
        const auto& rows = table.getRows();
        for (const auto& row : rows) {
            std::stringstream ss;
            for (size_t i = 0; i < columns.size(); ++i) {
                const std::string& colName = columns[i].name;
                ss << row.at(colName);
                if (i != columns.size() - 1) {
                    ss << ",";  // 用逗号分隔字段
                }
            }
            outFile << ss.str() << "\n";
        }
        outFile.close();
        std::cout << "Table " << tableName << " saved to " << filename << std::endl;
    }
    return 0;
}

int Database::loadDatabase() {
    try {
        // 遍历当前目录下所有 .tbl 文件
        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.path().extension() == ".tbl") {
                std::string filename = entry.path().filename().string();
                if (!loadTableFromFile(filename)) {
                    std::cerr << "Error: Failed to load table from " << filename << std::endl;
                    return -1;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return -2;
    }
    return 0;
}

bool Database::loadTableFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return false;
    }
    std::string line;
    // 读取表名
    std::string tableName;
    if (!std::getline(inFile, line) || line.find("TableName: ") != 0) {
        std::cerr << "Error: Invalid table name in " << filename << std::endl;
        return false;
    }
    tableName = line.substr(11);  // "TableName: " 长度为 11
    // 读取列定义
    std::vector<Column> columns;
    while (std::getline(inFile, line) && line.find("Column: ") == 0) {
        std::string colDef = line.substr(8);  // "Column: " 长度为 8
        std::istringstream ss(colDef);
        std::string name, type, primaryKeyStr;
        if (!std::getline(ss, name, ',') || 
            !std::getline(ss, type, ',') || 
            !std::getline(ss, primaryKeyStr)) {
            std::cerr << "Error: Invalid column format in " << filename << std::endl;
            return false;
        }
        bool isPrimaryKey = (primaryKeyStr == "1");
        Column col;
        col.name = name;
        // 根据类型字符串设置 DATATYPE
        if (type == "INT") {
            col.type = INT;
        } else if (type == "STRING") {
            col.type = STRING;
        } else if (type == "DOUBLE") {
            col.type = DOUBLE;
        } else if (type == "FLOAT") {
            col.type = FLOAT;
        } else {
            std::cerr << "Error: Unknown column type '" << type << "' in " << filename << std::endl;
            return false;
        }
        col.isPrimaryKey = isPrimaryKey;
        columns.push_back(col);
    }
    // 检查列定义是否为空
    if (columns.empty()) {
        std::cerr << "Error: No columns defined in " << filename << std::endl;
        return false;
    }
    // 创建表（假设表不存在）
    if (tables.find(tableName) != tables.end()) {
        std::cerr << "Error: Table " << tableName << " already exists." << std::endl;
        return false;
    }
    DatabaseTable& newTable = tables[tableName];
    newTable.setTableName(tableName);
    for (const auto& col : columns) {
        std::string typeStr;
        if constexpr (std::is_enum<decltype(col.type)>::value) {
            // 假设 col.type 是一个枚举类型
            // 这里需要根据实际的 DATATYPE 枚举值来转换为字符串
            switch (col.type) {
                case INT: typeStr = "INT"; break;
                case STRING: typeStr = "STRING"; break;
                case DOUBLE: typeStr = "DOUBLE"; break;
                case FLOAT: typeStr = "FLOAT"; break;
                default: typeStr = "UNKNOWN"; break;
            }
        } else {
            typeStr = col.type;
        }
        newTable.createColumn(col.name, typeStr, col.isPrimaryKey);
    }
    // 处理当前行（可能已读取到数据行）
    if (!line.empty()) {
        processDataLine(line, newTable, columns);
    }
    // 读取剩余数据行
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            processDataLine(line, newTable, columns);
        }
    }
    inFile.close();
    return true;
}

void Database::processDataLine(const std::string& line, DatabaseTable& table, const std::vector<Column>& columns) {
    std::istringstream ss(line);
    std::string field;
    std::vector<std::string> fields;

    // 分割逗号分隔的字段
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // 检查字段数量是否匹配
    if (fields.size() != columns.size()) {
        std::cerr << "Error: Data line has " << fields.size() 
                  << " fields, expected " << columns.size() << std::endl;
        return;
    }

    // 构建行数据映射
    std::map<std::string, std::string> rowData;
    for (size_t i = 0; i < columns.size(); ++i) {
        rowData[columns[i].name] = fields[i];
    }

    // 插入行并检查主键冲突
    if (table.insertRow(rowData) != 0) {
        std::cerr << "Error: Failed to insert row into table " << table.getTableName() << std::endl;
    }
}


