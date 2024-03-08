#include <iostream>
using namespace std;

template <class T>
class Vector{
    T* arr;
    int lenght;
public:
    Vector();
    explicit Vector(T*);
    explicit Vector(int);
    Vector(const Vector<T>&);
    ~Vector();

    T& operator[](int);
    int getLen();
    void show();
};

template<class T>
Vector<T>::Vector() : arr(nullptr), lenght(0) {};

template<class T>
Vector<T>::Vector(T* staticArr): lenght(sizeof(staticArr)/sizeof(staticArr[0])), arr(new T[lenght]){
    for(int i = 0; i < lenght; i++){
        arr[i] = staticArr[i];
    }
}

template<class T>
Vector<T>::Vector(int len): lenght(len), arr(new T[lenght]){}

template<class T>
Vector<T>::Vector(const Vector<T>& vec): lenght(vec.lenght), arr(new T[lenght]){
    for(int i = 0; i < lenght; i++){
        arr[i] = vec.arr[i];
    }
}

template<class T>
Vector<T>::~Vector(){delete[] arr; lenght = 0;}

template<class T>
T& Vector<T>::operator[](int idx){
    if(idx < lenght){
        return arr[idx];
    }
    
    Vector<T> temp(idx);
    for(int i = 0; i < lenght; i++){
        temp.arr[i] = arr[i];
    }
    for(int i = lenght; i < temp.lenght; i++){
        temp.arr[i] = 0;
    }
    delete[]arr;
    arr = temp.arr;
    lenght = temp.lenght;
    return arr[idx];
}

template<class T>
void Vector<T>::show(){
    for(int i = 0; i < lenght; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<class T>
int Vector<T>::getLen(){
    return lenght;
}