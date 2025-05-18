#include "DataBase.h"
#include "DatabaseTable.h"


int main(){
    Database db;
    db.createTable("Users");
    db.createTable("Products");

    DatabaseTable& users = db.getTable("Users");
    users.createColumn("id", "INT", true);
    users.createColumn("name", "STRING");
    users.createColumn("age", "INT");

    std::map<std::string, std::string> user1 = {{"id", "1"}, {"name", "Alice"}, {"age", "30"}};
    users.insertRow(user1);

    std::map<std::string, std::string> user2 = {{"id", "2"}, {"name", "Bob"}, {"age", "25"}};
    users.insertRow(user2);

    users.printTable();
    db.printAllTables();
    std::cout << "Here the Products table is empty,so it is normal to output 'ERROR:' twice." << std::endl;
    db.saveDatabase();
    db.loadDatabase();
    return 0;
}