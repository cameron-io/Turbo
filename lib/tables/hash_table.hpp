#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <tuple>
#include <iostream>

struct Record 
{
    Record(std::string k, std::string v)
    : key(k)
    , value(v)
    {}
    std::string key;
    std::string value;
    bool is_deleted = false;
}

typedef Record;

typedef std::shared_ptr<Record> record_t;
typedef std::tuple<std::string, error_t> result_t;

class HashTable {
public:
    int width = 0;
    int depth = 0;

    HashTable(int width, int depth);
    int create_item(std::string key, std::string value);
    int update_item(std::string key, std::string value);
    record_t query_item(std::string key);
    // int delete_item(std::string key);
    void print_table();
private:
    std::vector<std::vector<record_t>> table;
};

#endif