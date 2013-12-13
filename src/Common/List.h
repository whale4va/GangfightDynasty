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

    List () : isPointers(false), data(NULL), length(0),
    		size(0), increaseSize(32), invalidIndex(-1) {}

    ~List()
    {
        if (data)
            delete [] data;
    }
    
    /** @brief add element at the last of the list */
    inline void Add(const T& var)
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
    
    /** @brief remove element at specific position and replace it with the last element */
    inline void Remove(int index) throw (ExceptionId)
    {
        if (index < 0 || index >= length)
            THROW(Invalid_Index);
        
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
    inline T& operator[](int index) throw (ExceptionId)
    {
        if (index < 0 || index >= length)
            THROW(Invalid_Index);

        assert(data);
        return *(data + index);
    }
    
    /** @brief find dedicate element in list */
    inline int Find(const T& var, int startPos=0)
    {
        if (length == 0 || startPos >= length || startPos < 0)
            return invalidIndex;

        assert(data);
        for (int i = startPos; i < length; i++)
            if (*(data + i) == var)
                return i;

        return invalidIndex;
    }
    
    /** @brief release memory of every dynamic memory elements in the list */
    inline void Release()
    {
        if (isPointers)
        {
            for (int i = 0; i < length; i++)
            {
                delete (T)(data[i]);
                *(data+i) = NULL;
            }
            length = 0;
        }
    }
    
    inline int GetLength() { return length; }
    inline bool Empty() { return length == 0; }
    
    inline List& operator=(const List& lst)
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

    inline List(const List& lst)
    {
        size = lst.size;
        length = lst.length;
        isPointers = lst.isPointers;

        if (size > 0)
            data = new T[size];

        for (int i = 0; i < length; i++)
            *(data + i) = *(lst.data + i);
    }
    
private:
//    List() {}   // block default constructor.
    T* data;
    int length;
    int size;
    bool isPointers;
    
    /** increase string buffer size for every allocate memory */
    const int increaseSize;
    const int invalidIndex;
};

#endif
