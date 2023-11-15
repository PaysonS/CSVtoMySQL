#include <iostream>
#include <fstream>
#include "files.h"
#include <mysql_driver.h>      //replace with location of where you downloaded the connector
#include <mysql_connection.h>  //replace with location of where you downloaded the connector
#include <cppconn/resultset.h> //replace with location of where you downloaded the connector
#include <cppconn/statement.h> //replace with location of where you downloaded the connector

int main()
{

    files f;
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    f.connector(); // this connects to your MySql database and creates the table
    f.prompt( *stmt, res);    // this is the main menu for the program
    return 0;
}

void files::connector()
{
    files f; // object of the files class

    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    // creates the driver object
    driver = sql::mysql::get_mysql_driver_instance();

    // creates the connection object
    con = driver->connect("tcp://127.0.0.1:3306", "payson", "password"); // change to the appropriate address port, username, and password
    con->setSchema("csvtosql");                                          // change this to your database name

    stmt = con->createStatement();
    // test code to run to see if you;re connected

    f.createTable(*stmt, res); // creates users table
}

void files::createTable(sql::Statement &statement, sql::ResultSet *res)
{
    std::cout << "What would you like the name of the table to be?" << std::endl;
    std::string tableName;
    std::cin >> tableName;
    std::cout << "How many categories would you like to have?" << std::endl;
    int numCategories;
    std::cin >> numCategories;
    std::string categories[numCategories];

    for (int i = 0; i < numCategories; i++)
    {
        std::cout << "What would you like category " << i + 1 << " to be?" << std::endl;
        std::cin >> categories[i];
    }
    std::cout << "Creating table with " + std::to_string(numCategories) + " categories..." << std::endl;

    statement.execute("CREATE TABLE IF NOT EXISTS " + tableName + " (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id))");
    for (int i = 0; i < numCategories; i++)
    {
        statement.execute("ALTER TABLE " + tableName + " ADD " + categories[i] + " VARCHAR(255)"); // This adds in each additional category/column
    }
    std::cout << "Table created!" << std::endl << std::endl;

    // res = statement.executeQuery("SELECT * FROM " + tableName); //result statement for checking

    // while (res->next())
    // {
    //     int id = res->getInt("id");      Use to debug and see if the table was created/ show whats inside

    //     std::cout << id << std::endl;
    // }
}

void files::prompt(sql::Statement &statement, sql::ResultSet *res)
{
    files f;

    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Display table" << std::endl;
    std::cout << "2. Update entry" << std::endl;
    std::cout << "3. Add entry" << std::endl;
    std::cout << "4. Delete entry" << std::endl;
    std::cout << "5. Total entries" << std::endl;
    std::cout << "6. Exit" << std::endl;
    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        f.displayTable(statement, res);
        break;
    case 2:
        f.updateEntry(statement, res);
        break;
    case 3:
        f.addEntry(statement, res);
        break;
    case 4:
        f.deleteEntry(statement, res);
        break;
    case 5:
        f.totalEntries(statement, res);
        break;
    case 6:
        exit(0);
        break;
    default:
        std::cout << "Invalid choice try again" << std::endl;
        prompt(statement, res);
        break;
    }
}

void files::displayTable(sql::Statement &statement, sql::ResultSet *res)
{
    files f;

    std::cout << "What table would you like to display?" << std::endl;
    std::string tableName;
    std::cin >> tableName;

    res = statement.executeQuery("SELECT * FROM " + tableName);

    while (res->next())
    {
        int id = res->getInt("id"); // Use to debug and see if the table was created/ show whats inside

        std::cout << id << std::endl;
    }
    std::cout << std::endl;
    f.prompt(statement, res);
}

void files::updateEntry(sql::Statement &statement, sql::ResultSet *res)
{
    files f;

    std::cout << "What table would you like to update?" << std::endl;
    std::string tableName;
    std::cin >> tableName;

    std::cout << "What is the id of the entry you would like to update?" << std::endl;
    int id;
    std::cin >> id;

    std::cout << "What category would you like to update?" << std::endl;
    std::string category;
    std::cin >> category;

    std::cout << "What would you like to update it to?" << std::endl;
    std::string update;
    std::cin >> update;

    statement.execute("UPDATE " + tableName + " SET " + category + " = '" + update + "' WHERE id = " + std::to_string(id));

    std::cout << "Entry updated!" << std::endl << std::endl;
    f.prompt(statement, res);
}

void files::addEntry(sql::Statement &statement, sql::ResultSet *res)
{
    files f;

    std::cout << "What table would you like to add to?" << std::endl;
    std::string tableName;
    std::cin >> tableName;

    std::cout << "How many categories does this table have?" << std::endl;
    int numCategories;
    std::cin >> numCategories;

    std::string categories[numCategories];
    std::string values[numCategories];

    for (int i = 0; i < numCategories; i++)
    {
        std::cout << "What is the name of category " << i + 1 << "?" << std::endl;
        std::cin >> categories[i];
    }

    for (int i = 0; i < numCategories; i++)
    {
        std::cout << "What is the value of " << categories[i] << "?" << std::endl;
        std::cin >> values[i];
    }

}