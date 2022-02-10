#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <iostream>
template <typename T>
class Heap
{
public:
    std::vector<T*> arr;
    int size;
    void insert(T* data);
    T* peek();
    T* extractMin();
    void display();
    Heap(std::vector<T*>& arr);
private:
    void heapify(int nodePos);
    void swap(int posA, int posB);
    int parentPos(int childPos);
    int leftPos(int parentPos);
    int rightPos(int parentPos);
};



template <typename T>
Heap<T>::Heap(std::vector<T*>& arr)
{
    this->arr=arr;
    size=arr.size();
    for(int i=size/2-1;i>-1;--i)
    {
        heapify(i);
    }
}

template <typename T>
void Heap<T>::heapify(int nodePos)
{
    int leftChild=leftPos(nodePos);
    int rightChild=rightPos(nodePos);
    if(nodePos>size/2-1)
    {
        return;
    }
    if(rightChild==size)
    {
        if(*arr[leftChild]<*arr[nodePos])
        {
            swap(nodePos,leftChild);
        }
    }
    else if(*arr[leftChild]<*arr[nodePos]&&*arr[leftChild]<= *arr[rightChild])
    {
        swap(nodePos,leftChild);
        heapify(leftChild);
    }
    else if(*arr[rightChild]<*arr[nodePos]&&*arr[rightChild]<= *arr[leftChild])
    {
        swap(nodePos,rightChild);
        heapify(rightChild);
    }
}

template <typename T>
void Heap<T>::display()
{
    int z=1;
    for(int i=0;i<size;++i)
    {
        if(i==z)
        {
            std::cout<<std::endl;
            z+=i+1;
        }
        std::cout<<*arr[i]<<"\t";
    }
}

template <typename T>
int Heap<T>::parentPos(int childPos)
{
    return (childPos-1)/2;
}

template <typename T>
int Heap<T>::leftPos(int parentPos)
{
    return parentPos*2+1;
}

template <typename T>
int Heap<T>::rightPos(int parentPos)
{
    return parentPos*2+2;
}

template <typename T>
void Heap<T>::swap(int posA, int posB)
{
    T* temp=arr[posA];
    arr[posA]=arr[posB];
    arr[posB]=temp;
}

template <typename T>
T* Heap<T>::peek()
{
    return arr[0];
}

template <typename T>
T* Heap<T>::extractMin()
{
    swap(0,size-1);
    T* temp=arr[size-1];
    arr.pop_back();
    size=arr.size();
    heapify(0);
    return temp;
}

template <typename T>
void Heap<T>::insert(T* data)
{
    arr.push_back(data);
    size=arr.size();
    int nodePos=size-1;
    int parent=parentPos(nodePos);
    while(*arr[parent]>*arr[nodePos])
    {
        swap(parent,nodePos);
        nodePos=parent;
        parent=parentPos(nodePos);
    }
}

#endif // HEAP_H
