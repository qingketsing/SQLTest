#include "DatabaseTable.h"

int DatabaseTable::setTableName(std::string name) {
    tableName = name;
    return 0;
}

bool DatabaseTable::isVaildDataType(DATATYPE type) {
    switch (type) {
        case INT:
            return true;
        case STRING:
            return true;
        case DOUBLE:
            return true;
        case FLOAT:
            return true;
        default:
            return false;
    }
}

int DatabaseTable::createColumn(std::string colName,std::string type,bool isPrimaryKey) {
    DATATYPE dataType;
    if (type == "INT") {
        dataType = INT;
    } else if (type == "STRING") {
        dataType = STRING;
    } else if (type == "DOUBLE") {
        dataType = DOUBLE;
    } else if (type == "FLOAT") {
        dataType = FLOAT;
    } else {
        throw std::invalid_argument("Invalid data type");
        return -1;
    }

    if (!isVaildDataType(dataType)) {
        throw std::invalid_argument("Invalid data type");
    }

    Column newColumn;
    newColumn.name = colName;
    newColumn.type = dataType;
    newColumn.isPrimaryKey = isPrimaryKey;

    columns.push_back(newColumn);
    return 0;
}

int DatabaseTable::deleteRow(int id){
    for(auto row : rows){
        if(row.at("id") == std::to_string(id)){
            rows.erase(std::remove(rows.begin(), rows.end(), row), rows.end());
            return 0;
        }
    }
    return 0;
}

int DatabaseTable::insertRow(std::map<std::string, std::string> rowData) {
    Column* primaryKeyColumn = nullptr;
    for(const auto& col : columns){
        if(col.isPrimaryKey){
            primaryKeyColumn = const_cast<Column*>(&col);
            break;
        }
    }

    if(primaryKeyColumn){
        if(rowData.find(primaryKeyColumn->name) == rowData.end()){ // 无主键
            std::cerr << "Primary key column " << primaryKeyColumn->name << " not found in row data." << std::endl;
            return -1;
        }

        const std::string& pkVal = rowData[primaryKeyColumn->name];
        for(const auto& row : rows){
            if(row.at(primaryKeyColumn->name) == pkVal){ // 主键冲突
                std::cerr << "Duplicate primary key value: " << pkVal << std::endl;
                return -1;
            }
        }
    }

    rows.push_back(rowData);
    return 0;
}

std::optional<std::map<std::string, std::string>> DatabaseTable::findRow(int id) {
    for (const auto& row : rows) {
        if (row.at("id") == std::to_string(id)) {
            return row;
        }
    }
    return std::nullopt; // 如果没有找到，返回空值
}

int DatabaseTable::updateRow(int id, std::map<std::string, std::string> rowData) {
    for(auto& row : rows){ // 注意这里是引用
        if(row.at("id") == std::to_string(id)){
            for(auto col : columns){
                if(rowData.find(col.name) != rowData.end()){
                    row[col.name] = rowData[col.name]; // 更新数据
                }
            }
            return 0;
        }
    }
    return -1;
}

void DatabaseTable::printTable() {
    if(columns.empty()) {
        std::cout << "No columns in the table." << std::endl;
        return;
    }
    std::cout << std::setw(10) << "ID";
    for (const auto& col : columns) {
        std::cout << std::setw(15) << col.name;
    }
    std::cout << std::endl;

    for (const auto& row : rows) {
        std::cout << std::setw(10) << row.at("id");
        for (const auto& col : columns) {
            std::cout << std::setw(15) << row.at(col.name);
        }
        std::cout << std::endl;
    }
}
