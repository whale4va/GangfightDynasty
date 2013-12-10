//
//  String.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 13-11-10.
//
//

#ifndef GangfightDynasty_String_h
#define GangfightDynasty_String_h

#include "types.h"

/**
 @brief self using String class, only content UTF-8 content
 */
class String
{
public:
    String() : data(NULL), length(0), size(0) {}
    String(const char* str);
    String(const String& str);
    
    String& operator=(const String& str);
    String& operator=(const char* str);
    
    ~String()
    {
        if (data)
            delete [] data;
    }
    
    /**
     Gets the String's data as a C string pointer.  IMPORTANT:  The
     returned pointer refers to memory owned by the String object.  The
     caller must not free this memory.  The returned pointer is valid only
     until the String object is destructed or reassigned.  Use of this
     operator on a temporary String object may result in a memory error.
     
     @return Returns a const char pointer to the String's data.
     */
    operator const char*() const
    { return data; }
    
    char& operator[](int index) throw(ExceptionId);
    
    bool operator==(const String& str);
    bool operator==(const char* str);
    
    String& operator+(const String& str);
    String& operator+(const char* str);
    
    inline void clear()
    {
        length = 0;
    }
    inline int GetLength()
    {
        return length;
    }
    inline bool empty()
    {
        return (length == 0);
    }
    
    void append(const String& str);
    void append(const char* str);
    int find(const char c, int startPos = 0) throw(ExceptionId);
    int rfind(const char c, int startPos = 0) throw(ExceptionId);
    String substr(int startPos, int length = 0) throw(ExceptionId);
    void insert(const char* str, int startPos) throw(ExceptionId);
    void insert(const String& str, int startPos) throw(ExceptionId);

    /**
     * @brief compute the string containing characters number.
     * since UTF-8 has many bytes for only one character
     * @return int the UTF-8 characters number in the string.
     */
    int CharNumber() throw(ExceptionId);

    /**
     * @brief compute specific character (UTF-8) inside string array index.
     * convert from character index to array index
     */
    int LocateChar(int index) throw(ExceptionId);

    /**
     * @brief static method to convert string from UTF-8 to Unicode.
     */
    static void ConvertUnicode();

    /*
     * @brief static method to convert string from Unicode. to UTF-8
     */
    static void ConvertUTF8();


    /** increase string buffer size for every allocate memory */
    static int increaseSize;
    static int invalidIndex;
    
private:
    char* data;
    int length;
    int size;
};

bool operator==(const String& str1, const String& str2);
bool operator==(const String& str1, const char* str2);
bool operator==(const char* str1, const String& str2);

#endif
