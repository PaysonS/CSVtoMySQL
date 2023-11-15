-- Active: 1699500823557@@127.0.0.1@3306@csvtosql
USE csvtosql;

CREATE TABLE IF NOT EXISTS test_table (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    age INT
);

SELECT * FROM test_table;


DROP TABLE IF EXISTS test;
