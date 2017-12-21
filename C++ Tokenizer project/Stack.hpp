#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack{
    private:
        vector <T> vec;
    public:
        Stack(){}   //defined here
        void Push(T data);
        T Pop();
        void Print();
        ~Stack(){}  //defined here
};

template <typename T>
void Stack<T>::Push(T data) {
    vec.push_back(data);
}
template <typename T>
T Stack<T>::Pop() {
    if(vec.size() == 0) {
        throw std::out_of_range("Stack Empty!");
    }
    T temp = vec.back();
    vec.pop_back();
    return temp;
}
template <typename T>
void Stack<T>::Print() {
    if (vec.size() != 0) {
        cout << "[ ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] << " ";
        }
        cout << "]" << endl;
    }
    else
        cout << "[]" << endl;
}
