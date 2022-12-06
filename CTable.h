#pragma once
#include <string>
#include <iostream>
using namespace std;

#define TABLE_DEFAULT_NAME  "table_0"
const int DEFAULT_TABLE_SIZE = 10;

class CTable {
private:
    string s_name;
    int i_length;
    int* pi_table;
public:
    CTable();
    CTable(string name, int tableLength);
    CTable(const CTable& pcOther);
    CTable(CTable&& pcOther);
    ~CTable();

    bool setValueAt(int iOffset, int iNewVal);
    void setName(string name);
    void operator=(const CTable& pcOther);
    CTable operator+(CTable& pcOther);
    void operator=(CTable&& pcOther);
    int getSize();
    bool setNewSize(int tableLength);
    void vPrint();
    CTable* pcClone();
};
