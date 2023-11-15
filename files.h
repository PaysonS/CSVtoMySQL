#ifndef FILES_H_
#define FILES_H_
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class files
{

public:
   
    void connector();
    void prompt(sql::Statement &statement, sql::ResultSet *res);
    void createTable(sql::Statement &statement, sql::ResultSet *res);
    void displayTable(sql::Statement &statement, sql::ResultSet *res);
    void updateEntry(sql::Statement &statement, sql::ResultSet *res);
    void addEntry(sql::Statement &statement, sql::ResultSet *res);
    void deleteEntry(sql::Statement &statement, sql::ResultSet *res);
    double totalEntries(sql::Statement &statement, sql::ResultSet *res);
};

#endif