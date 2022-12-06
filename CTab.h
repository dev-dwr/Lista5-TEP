
#define DEF_TAB_SIZE 10
#include <iostream>
using namespace std;

template <typename T>
class CTab{
public:
    CTab();
    CTab(const CTab& cOther);
    CTab(CTab&& cOther);
    CTab operator=(const CTab& cOther);
    void operator=(CTab&& cOther);
    ~CTab();
    bool bSetSize(int iNewSize);
    int iGetSize();
private:
    void v_copy(const CTab& cOther);
    T* pi_tab;
    int i_size;
};

template <typename T>
CTab<T>::CTab() {
    pi_tab = new T[DEF_TAB_SIZE];
    i_size = DEF_TAB_SIZE;
}

template <typename T>
CTab<T>::CTab(const CTab& cOther) {
    v_copy(cOther);
    cout << "Copy ";
}

template <typename T>
CTab<T>::~CTab() {
    if (pi_tab != NULL)
        delete [] pi_tab;
    std::cout << "Destr size" << i_size << "\n";
}

template <typename T>
CTab<T>::CTab(CTab&& cOther) {
    pi_tab = cOther.pi_tab;
    i_size = cOther.i_size;
    cOther.pi_tab = NULL;
    std::cout << "MOVE ";
}

//zadanie 4
template <typename T>
CTab<T> CTab<T>::operator=(const CTab& cOther) {
    if (pi_tab != NULL)
        delete pi_tab;
    v_copy(cOther);
    std::cout << "op= ";
    return(*this);
}

template <typename T>
void CTab<T> :: operator=(CTab&& cOther) {
    if (pi_tab != NULL) {
        delete [] pi_tab;
    }
    pi_tab = cOther.pi_tab;
    i_size = cOther.i_size;
    cOther.pi_tab = NULL;
    std::cout << "op= &&";
}

template <typename T>
bool CTab<T>::bSetSize(int iNewSize) {
    if (iNewSize <= 0)
        return false;

    T* new_table = new T[iNewSize];

    if (i_size < iNewSize) {
        for (int i = 0; i < i_size; i++) {
            new_table[i] = pi_tab[i];
        }
    }
    else {
        for (int i = 0; i < iNewSize; i++) {
            new_table[i] = pi_tab[i];
        }
    }

    i_size = iNewSize;

    delete[] pi_tab;
    pi_tab = new_table;

    return true;
}

template <typename T>
void CTab<T> :: v_copy(const CTab& cOther) {
    pi_tab = new T[cOther.i_size];
    i_size = cOther.i_size;
    for (int ii = 0; ii < cOther.i_size; ii++)
        pi_tab[ii] = cOther.pi_tab[ii];
}

template <typename T>
int CTab<T> :: iGetSize() {
    return(i_size);
}

