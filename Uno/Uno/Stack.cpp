#include "Stack.h"
template <typename T>
Stack<T>::Stack(){
    size = 0;
}

template <typename T>
bool Stack<T>::empty() const{
    return size == 0;
}

template <typename T>
T Stack<T>::peek() const{
    return elements[size-1];
}

template <typename T>
void Stack<T>::push (T value){
    elements[size++] = value;
}

template <typename T>
T Stack<T>::pop(){
    return elements[--size];
}

template <typename T>
int Stack<T>::getSize() const{
    return size;
}