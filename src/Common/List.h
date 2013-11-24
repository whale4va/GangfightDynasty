//
//  List.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 13-11-10.
//
//

#ifndef GangfightDynasty_List_h
#define GangfightDynasty_List_h

#include "types.h"

template<typename T>
class List
{
public:
    List(bool ptrsornot) : isPointers(ptrsornot), data(NULL), length(0),
                size(0), increaseSize(32), invalidIndex(-1) {}
    ~List()
    {
        if (data)
            delete [] data;
    }
    
    /** @brief add element at the last of the list */
    void Add(const T& var);
    
    /** @brief remove element at specific position and replace it with the last element */
    inline void Remove(int index) throw (ExceptionId)
    {
        if (index < 0 || index >= length)
            throw (Invalid_Index);
        
        if (index == length -1)
        {
            length--;
            return;
        }
        
        *(data + index) = *(data + length -1);
        length--;
        return;
    }
    
    /** @brief retrieve element at specific position */
    T& operator[](int index);
    
    /** @brief find dedicate element in list */
    int find(const T& var, int startPos=0);
    
    /** @brief relase memory of every dynamic memory elements in the list */
    inline void release()
    {
        if (isPointers)
            for (int i = 0; i < length; i++)
                delete (T)(data[i]);
    }
    
    inline int GetLength() { return length; }
    
    List& operator=(const List& lst);
    List(const List& lst);
    
private:
    List() {}   // block default constructor.
    T* data;
    int length;
    int size;
    bool isPointers;
    
    /** increase string buffer size for every allocate memory */
    const int increaseSize;
    const int invalidIndex;
};

#endif
