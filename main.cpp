#include "CTab.h"
#include "CMySmartPointer.h"
#include "CTable.h"
#include <iostream>

//zadanie 5
using namespace std;
CTable::CTable() {
    s_name = TABLE_DEFAULT_NAME;
    pi_table = new int[DEFAULT_TABLE_SIZE];
    i_length = DEFAULT_TABLE_SIZE;

    cout << "bezp: " + s_name + "\n";
}
CTable::CTable(string sName, int iTableLen) {

    s_name = sName;
    i_length = iTableLen;
    pi_table = new int[iTableLen];

    cout << "parametr: " + s_name + "\n";
}

CTable::CTable(const CTable& pcOther) {

    s_name = pcOther.s_name + "_copy\n";
    i_length = pcOther.i_length;
    pi_table = new int[pcOther.i_length];

    for (int i = 0; i < i_length; i++) {
        pi_table[i] = pcOther.pi_table[i];
    }

    cout << "kopiuj: " + s_name;
}

CTable::CTable( CTable&& pcOther) {

    s_name = pcOther.s_name + "_\n";
    i_length = pcOther.i_length;
    pi_table = pcOther.pi_table;

    pcOther.pi_table = NULL;

    cout << "move: " + s_name;
}

CTable :: ~CTable() {
    if(pi_table != NULL)
        delete[] pi_table;

    cout << "destrukcja: " + s_name + "\n";
}
void CTable::setName(string sName) {
    s_name = sName;
}

bool CTable::setNewSize(int iTableLen) {
    if (iTableLen <= 0)
        return false;

    int* new_table = new int[iTableLen];

    if (i_length < iTableLen) {
        for (int i = 0; i < i_length; i++) {
            new_table[i] = pi_table[i];
        }
    }
    else {
        for (int i = 0; i < iTableLen; i++) {
            new_table[i] = pi_table[i];
        }
    }

    i_length = iTableLen;

    if (pi_table != NULL)
        delete[] pi_table;
    pi_table = new_table;

    return true;
}
//zadanie 5
void CTable :: operator=(const CTable& pcOther) {
    if(pi_table != NULL)
        delete[] pi_table;
    s_name = pcOther.s_name;
    pi_table = new int[pcOther.i_length];
    i_length = pcOther.i_length;

    for (int i = 0; i < i_length; i++) {
        pi_table[i] = pcOther.pi_table[i];
    }
    cout << "operator =&\n";

}
//zadanie 5
void CTable :: operator=(CTable&& pcOther) {
    if(pi_table != NULL)
        delete[] pi_table;

    pi_table = pcOther.pi_table;
    i_length = pcOther.i_length;
    s_name = pcOther.s_name;

    pcOther.pi_table = NULL;

    cout << "operator =&&\n";
}



//zadanie 5
CTable CTable :: operator+(CTable& pcOther) {
    CTable concat("result", i_length + pcOther.i_length);

    for (int i = 0; i < i_length + pcOther.i_length; i++) {
        if (i < i_length)
            concat.setValueAt(i, pi_table[i]);
        else {
            concat.setValueAt(i, pcOther.pi_table[i - i_length]);
        }
    }
    cout << "operator +\n";
    return move(concat);
}

bool CTable::setValueAt(int iOffset, int iNewVal) {
    if (iOffset >= i_length || iOffset < 0)
        return false;

    pi_table[iOffset] = iNewVal;

    return true;
}

void CTable::vPrint() {
    cout << "| ";

    for (int i = 0; i < i_length; i++) {
        cout << pi_table[i] << " | ";
    }
    cout << "\n";
}
int CTable::getSize() {
    return i_length;
}

CTable* CTable::pcClone() {
    CTable* clone = new CTable(*this);
    return clone;
}


CTab<string> cCreateTab() {
    CTab<string> c_result;
    c_result.bSetSize(8);
    return (std::move(c_result));
}

int i_ms_test() {

    CTab<string> ctab1, ctab2, ctab3;

    CTab<string> ms1 = cCreateTab();
    ctab2.bSetSize(5);
    ctab3.bSetSize(7);

    ctab2 = std::move(ctab3);

    return 0;
}

void v_smartPointer_test() {
    int *ipoint = new int[3];
    CMySmartPointer<int> point1(ipoint);
    CMySmartPointer<int> point2(point1);
    CMySmartPointer<int> point3(new int[7]);
    point3 = point2;
}


void v_ctableMS_test() {
    CTable tab1("one", 1);
    CTable tab2("two", 2);
    CTable tab3("three", 3);

    CTable tab4;

    tab4 = tab2 + tab3;

}

//Zastanów się co się stanie, gdy inteligentny wskaźnik będzie przechowywać wskaźnik
//na pamięć zaalokowaną statycznie. ??????


//Sprawdź o ile spadła liczba wykonanych kopii przy użyciu move
//semantcis i bez nich ????
int main() {
    cout<<"\nI_MS_TEST"<<endl;
    i_ms_test();

    cout<<"\nv_smartPointer_test"<<endl;
    v_smartPointer_test();
    cout<<"\nv_ctableMS_test\n"<<endl;
    v_ctableMS_test();
    return 0;
}
