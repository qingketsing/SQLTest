#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <string>
#include <optional>
#include <vector>

enum DATATYPE {INT,STRING,DOUBLE,FLOAT};

struct Column
{
    std::string name;
    DATATYPE type;
    bool isPrimaryKey;
};

class DatabaseTable {
private:
    std::string tableName;
    std::vector<Column> columns;
    std::vector<std::map<std::string, std::string>> rows;
    int next_id = 0;

    bool isVaildDataType(DATATYPE type);
public:
    int setTableName(std::string name);
    int createColumn(std::string colName,std::string type,bool isPrimaryKey=false);
    int insertRow(std::map<std::string, std::string> rowData);
    int deleteRow(int id);
    std::optional<std::map<std::string, std::string>> findRow(int id);
    int updateRow(int id, std::map<std::string, std::string> rowData);
    void printTable();
    std::string getTableName() const { return tableName; }
    std::vector<Column> getColumns() const { return columns; }
    std::vector<std::map<std::string, std::string>> getRows() const { return rows; }
};

#endif // DATABASE_TABLE_H

