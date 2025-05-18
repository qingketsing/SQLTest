#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include "DatabaseTable.h"

class Database{
private:
    std::map<std::string, DatabaseTable> tables;
    std::string dbName;
    std::string dbPath;
public:
    int createTable(std::string tableName);
    int dropTable(std::string tableName);
    DatabaseTable& getTable(std::string tableName);
    int printAllTables();
    int saveDatabase();
    int loadDatabase();
    bool loadTableFromFile(const std::string& filename);
    void processDataLine(const std::string& line, DatabaseTable& table, const std::vector<Column>& columns);
};

#endif // DATABASE_H