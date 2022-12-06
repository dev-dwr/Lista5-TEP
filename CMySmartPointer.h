#include <vector>

#include <iostream>

//zadanie 1
class CRefCounter {
public:
    CRefCounter() { i_count; }

    int iAdd();

    int iDec();

    int iGet();

private:
    int i_count;
};


int CRefCounter::iAdd(){
    return(++i_count);
}

int CRefCounter::iDec() {
    return(--i_count);
}

int CRefCounter::iGet() {
    return(i_count);
}


template <typename T>
class CMySmartPointer
{
public:
    CMySmartPointer(T* pcPointer);
    CMySmartPointer(const CMySmartPointer& pcOther);
    ~CMySmartPointer();
    T& operator*();
    T* operator->();
    void operator=(const CMySmartPointer &pcOther);
    CMySmartPointer<T> cDuplicate();
private:
    CRefCounter* pc_counter;
    T* pc_pointer;
};

template <typename T>
CMySmartPointer<T> :: CMySmartPointer(T* pcPointer){
    pc_pointer = pcPointer;
    pc_counter = new CRefCounter();
    pc_counter->iAdd();
}

template <typename T>
CMySmartPointer<T> :: CMySmartPointer(const CMySmartPointer& pcOther){
    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
    pc_counter->iAdd();
}

template <typename T>
CMySmartPointer<T> :: ~CMySmartPointer(){
    if (pc_counter->iDec() == 0)
    {
        delete pc_pointer;
        delete pc_counter;

        cout << "deleting pointer...";
    }
    cout << "destructor...";
}

template <typename T>
T& CMySmartPointer<T> :: operator*() {
    return(*pc_pointer);
}

template <typename T>
T* CMySmartPointer<T> :: operator->() {
    return(pc_pointer);
}

//zadanie 2
template <typename T>
void CMySmartPointer<T> :: operator=(const CMySmartPointer& pcOther) {
    if (pc_counter->iDec() == 0){
        delete pc_pointer;
        delete pc_counter;
        cout << "deleting unused pointer...";
    }

    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
    pc_counter->iAdd();
}

