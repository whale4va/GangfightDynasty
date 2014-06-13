//
//  String.cpp
//  GangfightDynasty
//
//  Created by Foraby.Va on 13-11-10.
//
//

#include "String.h"

int String::increaseSize = 128;
int String::invalidIndex = -1;

String::String(const char* str)
{
    assert(str);
    length = strlen(str);
    if (length == 0)
    {
    	size = 0;
    	data = NULL;
    	return;
    }
    size = (length/increaseSize + 1)*increaseSize;
    data = new char[size];
    assert(data);
    memset(data, 0x00, size);
    memcpy(data, str, length);
}

String::String(const String& str)
{
    const char* pstr = (const char*)(str);
    if (pstr == NULL)
    {
        data = NULL;
        length = size = 0;
    }
    else
    {
        length = strlen(pstr);
        if (length == 0)
        {
        	size = 0;
        	data = NULL;
        	return;
        }
        size = (length/increaseSize + 1)*increaseSize;
        data = new char[size];
        assert(data);
        memset(data, 0x00, size);
        memcpy(data, pstr, length);
    }
}

String& String::operator=(const char* str)
{
    assert(str);
    if (str == data)
        return *this;
    
    if (data)
        delete [] data;
    
    length = strlen(str);
    if (length == 0)
    {
    	size = 0;
    	data = NULL;
    	return *this;
    }
    size = (length/increaseSize + 1)*increaseSize;
    data = new char[size];
    memset(data, 0x00, size);
    memcpy(data, str, length);
    return *this;
}

String& String::operator=(const String& str)
{
    const char* pstr = (const char*)(str);
    if (pstr == NULL)
    {
        if (data)
            delete [] data;
        length = 0;
        size = 0;
        return *this;
    }
    
    if (data == pstr)
        return *this;
    
    if (data)
        delete [] data;
    
    length = strlen(pstr);
    if (length == 0)
    {
    	size = 0;
    	data = NULL;
    	return *this;
    }
    size = (length/increaseSize + 1)*increaseSize;
    data = new char[size];
    assert(data);
    memset(data, 0x00, size);
    memcpy(data, pstr, length);
    return *this;
}

char& String::operator[](int index) throw(ExceptionId)
{
    // index should > 0 && < length
    if (index >= length || index < 0)
        THROW(Invalid_Index);
    
    assert(data);
    return data[index];
}

bool String::operator==(const String& str)
{
    if (length != str.length || size != str.size)
        return false;
    
    const char* pstr = (const char*)(str);
    if (pstr == NULL || data == NULL)
    {
        if (pstr == data)
            return true;
        else
            return false;
    }
    
    if (pstr == data)
        return true;
    else
    {
        for (int i = 0; i < length; i++)
            if (data[i] != str.data[i])
                return false;
    }
    return true;
}

bool String::operator==(const char* str)
{
    if (str == NULL || data == NULL)
    {
        if (str == data)
            return true;
        else
            return false;
    }
    
    if (length != strlen(str))
        return false;
    
    if (str == data)
        return true;
    else
    {
        for (int i = 0; i < length; i++)
            if (data[i] != *(str + i))
                return false;
    }
    return true;
}

String& String::operator+(const String& str)
{
    if (str.length == 0)
        return (*this);
    
    if (size > (length + str.length))
    {	// already has enough buffer, just copy
    	memcpy(&data[length], str.data, str.length);
    	length += str.length;
    	return (*this);
    }

    int len = length + str.length;
    size = (len/increaseSize + 1)*increaseSize;
    char* buf = new char[size];
    assert(buf);
    memset(buf, 0x00, size);
    
    if (length > 0)		// must not empty, then it has content to be copied
        memcpy(buf, data, length);
    assert(str.data);
    memcpy(buf+length, str.data, str.length);
    length = len;
    if (data)
        delete [] data;
    data = buf;
    
    return (*this);
}

String& String::operator+(const char* str)
{
	int appendLength = strlen(str);
    if (str == NULL || appendLength == 0)
        return (*this);
    
    if (size > length + appendLength)
    {
    	memcpy(&data[length], str, appendLength);
    	length += appendLength;
    	return (*this);
    }

    int len = length + strlen(str);
    size = (len/increaseSize + 1)*increaseSize;
    char* buf = new char[size];
    assert(buf);
    memset(buf, 0x00, size);
    
    if (length > 0)		// must not empty, then it has content to be copied
        memcpy(buf, data, length);
    memcpy(buf+length, str, strlen(str));
    length = len;
    if (data)
        delete [] data;
    data = buf;
    
    return (*this);
}

void String::append(const String& str)
{
    this->operator+(str);
    return;
}

void String::append(const char* str)
{
    this->operator+(str);
    return;
}

int String::find(const char c, int startPos) throw(ExceptionId)
{
    if (startPos < 0 || startPos >= length)
	THROW(Invalid_Index);
    
    if (length == 0)
        return invalidIndex;
    assert(data);
    
    for (int i = startPos; i < length; i++)
        if (data[i] == c)
            return i;
    
    return invalidIndex;
}

int String::rfind(const char c, int startPos) throw(ExceptionId)
{
	if (startPos < 0 || startPos >= length)
		THROW(Invalid_Index);

	if (length == 0)
		return invalidIndex;

	if (startPos == 0)
		startPos = length;
	assert(data);

	for (int i = startPos; i >= 0; i--)
		if (data[i] == c)
			return i;

	return invalidIndex;
}

String String::substr(int startPos, int len) throw(ExceptionId)
{
    if (startPos < 0 || startPos >= length)
	THROW(Invalid_Index);
    
    if (length == 0)
        return String();
    
    if (len == 0)
        len = length - startPos;
    assert(data);
    int final_len = len > (length - startPos) ? (length - startPos):len;
    final_len++;    // last '\0' character
    char* buf = new char[final_len];
    assert(buf);
    memset(buf, 0x00, final_len);
    memcpy(buf, &data[startPos], final_len-1);
    String ret(buf);
    delete [] buf;  // release memory since constructed object allocate its own memory.
    
    return ret;
}

void String::insert(const char* str, int startPos) throw(ExceptionId)
{
	int insertLength = strlen(str);

	if (str == NULL || insertLength == 0)
		return;
	if (startPos < 0 || startPos > length)	// can be length, equals as append()
		THROW(Invalid_Index);

	if (size > length + insertLength)
	{	// buffer is enough, directly move and copy
		if (length > 0)		// must not empty, then it has content to be copied
			memcpy(&data[startPos+insertLength], &data[startPos], length-startPos);
		memcpy(&data[startPos], str, insertLength);
		length += insertLength;
		return;
	}

	// buffer is not enough, new allocating
	int len = length + insertLength;
	size = (len/increaseSize + 1)*increaseSize;
	char* buf = new char[size];
	assert(buf);
	memset(buf, 0x00, size);
	if (startPos == 0)
	{
		memcpy(&buf[startPos], str, insertLength);
		if (length > 0)		// must not empty, then it has content to be copied
			memcpy(&buf[startPos+insertLength], &data[startPos], length-startPos);
	}
	else
	{
		if (length > 0)		// must not empty, then it has content to be copied
			memcpy(buf, data, startPos);
		memcpy(&buf[startPos], str, insertLength);
		if (length > 0)		// must not empty, then it has content to be copied
			memcpy(&buf[startPos+insertLength], &data[startPos], length-startPos);
	}

	length += insertLength;
	if (data)
		delete [] data;
	data = buf;

	return;
}

void String::insert(const String& str, int startPos) throw(ExceptionId)
{
	insert((const char*)str, startPos);
	return;
}

/**
 * string are stored as UTF-8 at default
 */
int String::CharNumber() throw(ExceptionId)
{
	if (length == 0)
		return 0;

	assert(data);
	int pos = 0, num = 0;
	while (pos < length)
	{
		unsigned char c = (unsigned char)data[pos];
		unsigned char c1 = c>>4;
		unsigned char c2 = c&0x0F;

		// == high priority than &
		if ( (c&0x80) == 0x00)
		{	// ASCII character
			pos++;
			num++;
		}
		else
		{
			switch (c1)
			{
			case 0x0C:
			case 0x0D:
				pos += 2;
				break;
			case 0x0E:
				pos += 3;
				break;
			case 0x0F:
			{
				if ((c2&0x08) == 0x00)
					pos+=4;
				else if ((c2&0x0C) == 0x08)
					pos+=5;
				else if ((c2&0x0E) == 0x0C)
					pos+=6;
				else
					THROW(String_Not_UTF8);
				break;
			}
			default:
				THROW(String_Not_UTF8);
			}
			num++;
		}
	}

	return num;
}

int String::LocateChar(int index) throw(ExceptionId)
{
	if (length == 0 || index == 0)
		return 0;

	int pos = 0, num = 0;
	while (pos < length)
	{
		unsigned char c = (unsigned char)data[pos];
		unsigned char c1 = c>>4;
		unsigned char c2 = c&0x0F;
		if ((c&0x80) == 0x00)
		{	// ASCII character
			pos++;
			num++;
		}
		else
		{
			switch (c1)
			{
			case 0x0C:
			case 0x0D:
				pos += 2;
				break;
			case 0x0E:
				pos += 3;
				break;
			case 0x0F:
			{
				if ((c2&0x08) == 0x00)
					pos+=4;
				else if ((c2&0x0C) == 0x08)
					pos+=5;
				else if ((c2&0x0E) == 0x0C)
					pos+=6;
				else
					THROW(String_Not_UTF8);
				break;
			}
			default:
				THROW(String_Not_UTF8);
			}
			num++;
		}
		if (num == index)	// fond here.
			break;
	}

	if (pos >= length)
		return String::invalidIndex;
	return pos;
}
