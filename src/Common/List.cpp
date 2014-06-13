//
//  List.cpp
//  GangfightDynasty
//
//  Created by Foraby.Va on 13-11-10.
//
//

#include "List.h"
/**
template<typename T>
void List<T>::Add(const T& var)
{
    if (length == 0)
    {
        assert(data == NULL);
        length++;
        size = (length/increaseSize + 1)*increaseSize;
        data = new T [size];
        *(data + length -1) = var;
    }
    else
    {
        assert(data);
        if (length == size)
        {   // allocate new memory again
            size += increaseSize;
            T* buf = new T[size];
            for (int i = 0; i < length; i++)
            {
                *(buf +i) = *(data + i);
            }
            delete [] data;
            data = buf;
        }
        length++;
        *(data + length -1) = var;
    }
    
    return;
}

template <typename T>
T& List<T>::operator[](int index)
{
    if (index < 0 || index >= length)
        THROW(Invalid_Index);
    
    assert(data);
    return *(data + index);
}

template <typename T>
int List<T>::find(const T& var, int startPos)
{
    if (length == 0 || startPos >= length || startPos < 0)
        return invalidIndex;
    
    assert(data);
    for (int i = startPos; i < length; i++)
        if (*(data + i) == var)
            return i;
    
    return invalidIndex;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst)
{
    if (data == lst.data)
    {
        assert(length == lst.length);
        assert(size == lst.size);
        return (*this);
    }
    
    if (data)
    {
        delete [] data;
        data = NULL;
    }
    
    length = lst.length;
    size = lst.size;
    isPointers = lst.isPointers;
    
    if (size > 0)
        data = new T[size];
    
    for (int i = 0; i < length; i++)
        *(data + i) = *(lst.data + i);
    
    return (*this);
}

template <typename T>
List<T>::List(const List<T>& lst)
{
    size = lst.size;
    length = lst.length;
    isPointers = lst.isPointers;
    
    if (size > 0)
        data = new T[size];
    
    for (int i = 0; i < length; i++)
        *(data + i) = *(lst.data + i);
}
 
 **/


