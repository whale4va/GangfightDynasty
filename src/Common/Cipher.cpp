//
//  Cipher.cpp
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-9-11.
//
//

#include "Cipher.h"

const String Cipher::kingString = String("Foraby.Va-King-Of-Universe");
const Uint8 Cipher::kingByte = 0x57;        // 87 = XOR(kingString)
Uint8 Cipher::encodeTable[256];
Uint8 Cipher::decodeTable[256];

/**
 * define MD5 calculate macros
 **/

#define MD5_F(X,Y,Z) (((X)&(Y))|((~X)&(Z)))
#define MD5_G(X,Y,Z) (((X)&(Z))|((Y)&(~Z)))
#define MD5_H(X,Y,Z) ((X)^(Y)^(Z))
#define MD5_I(X,Y,Z) ((Y)^((X)|(~Z)))

// FF(a,b,c,d,Mj,s,ti) = b + ((a + F(b,c,d) + Mj + ti)<<s)
#define MD5_FF(ret,a,b,c,d,Mj,s,ti) do { \
    ret = MD5_F(b,c,d); \
    ret += ((a) + (Mj) + (ti)); \
    ret = (ret << (s))|(ret >> (32-s)); \
    ret += (b); \
    a = ret; \
} while(0)

// GG(a,b,c,d,Mj,s,ti) = b + ((a + G(b,c,d) + Mj + ti)<<s)
#define MD5_GG(ret,a,b,c,d,Mj,s,ti) do { \
    ret = MD5_G(b,c,d); \
    ret += ((a) + (Mj) + (ti)); \
    ret = (ret << (s))|(ret >> (32-s)); \
    ret += (b); \
    a = ret; \
} while(0)

// HH(a,b,c,d,Mj,s,ti) = b + ((a + H(b,c,d) + Mj + ti)<<s)
#define MD5_HH(ret,a,b,c,d,Mj,s,ti) do { \
    ret = MD5_H(b,c,d); \
    ret += ((a) + (Mj) + (ti)); \
    ret = (ret << (s))|(ret >> (32-s)); \
    ret += (b); \
    a = ret; \
} while(0)

// II(a,b,c,d,Mj,s,ti) = b + ((a + I(b,c,d) + Mj + ti)<<s)
#define MD5_II(ret,a,b,c,d,Mj,s,ti) do { \
    ret = MD5_I(b,c,d); \
    ret += ((a) + (Mj) + (ti)); \
    ret = (ret << (s))|(ret >> (32-s)); \
    ret += (b); \
    a = ret; \
} while(0)

// calculate one group of MD5, calculate 512bits(16*32) of original date
static void MD5_CalculateGroup(Uint32* group, Uint32* result)
{
    Uint32 a = result[0];
    Uint32 b = result[1];
    Uint32 c = result[2];
    Uint32 d = result[3];
    
    Uint32 ret;
    // round 1
    MD5_FF(ret, a,b,c,d,group[0],7,0xd76aa478);	
    MD5_FF(ret, d,a,b,c,group[1],12,0xe8c7b756);
    MD5_FF(ret, c,d,a,b,group[2],17,0x242070db);
    MD5_FF(ret, b,c,d,a,group[3],22,0xc1bdceee);
    MD5_FF(ret, a,b,c,d,group[4],7,0xf57c0faf);		
    MD5_FF(ret, d,a,b,c,group[5],12,0x4787c62a);
    MD5_FF(ret, c,d,a,b,group[6],17,0xa8304613);
    MD5_FF(ret, b,c,d,a,group[7],22,0xfd469501);
    MD5_FF(ret, a,b,c,d,group[8],7,0x698098d8);	
    MD5_FF(ret, d,a,b,c,group[9],12,0x8b44f7af);
    MD5_FF(ret, c,d,a,b,group[10],17,0xffff5bb1);
    MD5_FF(ret, b,c,d,a,group[11],22,0x895cd7be);
    MD5_FF(ret, a,b,c,d,group[12],7,0x6b901122);
    MD5_FF(ret, d,a,b,c,group[13],12,0xfd987193);
    MD5_FF(ret, c,d,a,b,group[14],17,0xa679438e);
    MD5_FF(ret, b,c,d,a,group[15],22,0x49b40821);
    
    // round 2
    MD5_GG(ret, a,b,c,d,group[1],5,0xf61e2562);	
    MD5_GG(ret, d,a,b,c,group[6],9,0xc040b340);	
    MD5_GG(ret, c,d,a,b,group[11],14,0x265e5a51);
    MD5_GG(ret, b,c,d,a,group[0],20,0xe9b6c7aa);
    MD5_GG(ret, a,b,c,d,group[5],5,0xd62f105d);	
    MD5_GG(ret, d,a,b,c,group[10],9,0x02441453);
    MD5_GG(ret, c,d,a,b,group[15],14,0xd8a1e681);
    MD5_GG(ret, b,c,d,a,group[4],20,0xe7d3fbc8);
    MD5_GG(ret, a,b,c,d,group[9],5,0x21e1cde6);	
    MD5_GG(ret, d,a,b,c,group[14],9,0xc33707d6);
    MD5_GG(ret, c,d,a,b,group[3],14,0xf4d50d87);
    MD5_GG(ret, b,c,d,a,group[8],20,0x455a14ed);
    MD5_GG(ret, a,b,c,d,group[13],5,0xa9e3e905);
    MD5_GG(ret, d,a,b,c,group[2],9,0xfcefa3f8);	
    MD5_GG(ret, c,d,a,b,group[7],14,0x676f02d9);
    MD5_GG(ret, b,c,d,a,group[12],20,0x8d2a4c8a);
    
    // round 3
    MD5_HH(ret, a,b,c,d,group[5],4,0xfffa3942);	
    MD5_HH(ret, d,a,b,c,group[8],11,0x8771f681);
    MD5_HH(ret, c,d,a,b,group[11],16,0x6d9d6122);
    MD5_HH(ret, b,c,d,a,group[14],23,0xfde5380c);
    MD5_HH(ret, a,b,c,d,group[1],4,0xa4beea44);	
    MD5_HH(ret, d,a,b,c,group[4],11,0x4bdecfa9);
    MD5_HH(ret, c,d,a,b,group[7],16,0xf6bb4b60);
    MD5_HH(ret, b,c,d,a,group[10],23,0xbebfbc70);
    MD5_HH(ret, a,b,c,d,group[13],4,0x289b7ec6);
    MD5_HH(ret, d,a,b,c,group[0],11,0xeaa127fa);
    MD5_HH(ret, c,d,a,b,group[3],16,0xd4ef3085);
    MD5_HH(ret, b,c,d,a,group[6],23,0x04881d05);
    MD5_HH(ret, a,b,c,d,group[9],4,0xd9d4d039);	
    MD5_HH(ret, d,a,b,c,group[12],11,0xe6db99e5);
    MD5_HH(ret, c,d,a,b,group[15],16,0x1fa27cf8);
    MD5_HH(ret, b,c,d,a,group[2],23,0xc4ac5665);
    
    // round 4
    MD5_II(ret, a,b,c,d,group[0],6,0xf4292244);	
    MD5_II(ret, d,a,b,c,group[7],10,0x432aff97);
    MD5_II(ret, c,d,a,b,group[14],15,0xab9423a7);
    MD5_II(ret, b,c,d,a,group[5],21,0xfc93a039);
    MD5_II(ret, a,b,c,d,group[12],6,0x655b59c3);
    MD5_II(ret, d,a,b,c,group[3],10,0x8f0ccc92);
    MD5_II(ret, c,d,a,b,group[10],15,0xffeff47d);
    MD5_II(ret, b,c,d,a,group[1],21,0x85845dd1);
    MD5_II(ret, a,b,c,d,group[8],6,0x6fa87e4f);	
    MD5_II(ret, d,a,b,c,group[15],10,0xfe2ce6e0);
    MD5_II(ret, c,d,a,b,group[6],15,0xa3014314);
    MD5_II(ret, b,c,d,a,group[13],21,0x4e0811a1);
    MD5_II(ret, a,b,c,d,group[4],6,0xf7537e82);	
    MD5_II(ret, d,a,b,c,group[11],10,0xbd3af235);
    MD5_II(ret, c,d,a,b,group[2],15,0x2ad7d2bb);
    MD5_II(ret, b,c,d,a,group[9],21,0xeb86d391);
    
    result[0] += a;
    result[1] += b;
    result[2] += c;
    result[3] += d;
 
    return;
}

static void MD5_Calculate(String buf, Uint32 value[4])
{
    value[0] = 0x67452301;
    value[1] = 0xefcdab89;
    value[2] = 0x98badcfe;
    value[3] = 0x10325476;
    
    int len = buf.GetLength();
    Uint8 last8[8];         // last 8 bytes for data length as Uint64 format
    for (int i = 0; i < 8; i++)
    {
        last8[i] = (len&0xFF);
        len = len>>8;
    }
    
    len = buf.GetLength();
    int data_len = 0;
    if (len % 64 < 56)
    {
        data_len = (56 - (len%64)) + len + 8;
    }
    else
    {
        data_len = (64 - (len%64)) + 64 + len;
    }
    
    Uint8* data = new Uint8[data_len];
    memcpy(data, (const char*)buf, len);
    if (data_len - len > 8)
    {
        int fill_len = data_len - len - 8;
        for (int i = 0; i < fill_len; i++)
        {
            if (0 == i)
            {
                data[len+i] = 0x80;
            }
            else
            {
                data[len+i] = 0x00;
            }
        }
        memcpy((data+len+fill_len), last8, 8);
    }
    else
    {
        memcpy((data+len), last8, 8);
    }
    
    // data prepared done, start calculating.
    Uint32 start_pos = 0;
    while (start_pos < data_len)
    {
        MD5_CalculateGroup((Uint32*)&data[start_pos], &value[0]);
        start_pos += 64;
    }
    
    delete [] data;
    return;
}

static void MD5_AdjustResult(Uint32 result[4], Uint8 md5[16])
{
    for (int i = 0; i < 4; i++)
    {
        Uint8* pStart = (Uint8*) &result[i];
        for (int j = 0; j < 4; j++)
        {
            md5[i*4+j] = pStart[j];
        }
    }
}

// Using the XOR of string as start byte, if it's 0x00 then use kingByte.
Uint8 Cipher::PrepareStrartByteByUserName(String user)
{
    Uint8 ret = 0x00;
    Uint8* pData = (Uint8*)((const char*)user);
    for (int i = 0; i < user.GetLength(); i++)
    {
        ret ^= pData[i];
    }
    
    if (0x00 == ret)
        ret = kingByte;
    return ret;
}


void Cipher::GenerateCipherTableByUserName(String user)
{
    Uint8 md5[16];
    Uint32 md5_origin[4];
    user.append("=>");
    user.append(kingString);
    MD5_Calculate(user, md5_origin);
    MD5_AdjustResult(md5_origin, md5);
    
    // divide 0x00 ~ 0xFF to 16 groups using MD5 value
    Uint8 origin_values[256];
    for (int i = 0; i < 256; i++)
        origin_values[i] = (Uint8)i;
    
    Uint8 value_groups[16][16];
    int start, step=16, backpos = 255;
    for (int i = 0; i < 16; i++)
    {
        start = ((int)md5[i])%step;
        for (int j = 0; j < 16; j++ )
        {
            value_groups[i][j] = origin_values[start + j*step];
            // move backend values to blanks
            if (step > 1 && backpos >= 16*(step-1))
            {
                if (backpos%step != start)
                    origin_values[start+j*step] = origin_values[backpos];
                else
                {
                    do
                    {
                        backpos--;
                    } while (backpos%step == start);
                    if (backpos >= 16*(step-1))
                        origin_values[start+j*step] = origin_values[backpos];
                }

                do
                {
                    backpos--;
                } while (backpos%step == start);
                if (backpos < 16*(step-1) - 1)
                    backpos = 16*(step-1) - 1;
            }
        }
        step--;
    }

    // exchange in every groups as md5 value specified.
    for (int i = 0; i < 16; i++)
    {
        ExchangeInGroup(value_groups, i, md5);
    }
 
    // merge every group, generate the final encode table
    for (int i = 0; i < 256; i++)
    {
        encodeTable[i] = value_groups[i/16][i%16];
    }
    
    // check encode table and generate final decode table.
    for (int i = 0; i < 256; i++)
        origin_values[i] = 0;
    
    for (int i = 0; i < 256; i++)
    {
        if (origin_values[encodeTable[i]] > 0)
            THROW(Invalid_Cipher_Table);
        decodeTable[encodeTable[i]] = i;
        origin_values[encodeTable[i]] = 1;
    }
    
}


void Cipher::Encode(Uint8 *buf, Uint32 len)
{
    for (int i = 0; i < len; i++)
    {
        buf[i] = encodeTable[buf[i]];
    }
}

void Cipher::Decode(Uint8* buf, Uint32 len)
{
    for (int i = 0; i < len; i++)
    {
        buf[i] = decodeTable[buf[i]];
    }
}


void Cipher::GetEncodeTableWithKey(String key, Uint8 *enTable)
{
     Uint8 md5[16];
    Uint32 md5_origin[4];
    key.append("=>");
    key.append(kingString);
    MD5_Calculate(key, md5_origin);
    MD5_AdjustResult(md5_origin, md5);
    
    // divide 0x00 ~ 0xFF to 16 groups using MD5 value
    Uint8 origin_values[256];
    for (int i = 0; i < 256; i++)
        origin_values[i] = (Uint8)i;
    
    Uint8 value_groups[16][16];
    int start, step=16, backpos = 255;
    for (int i = 0; i < 16; i++)
    {
        start = ((int)md5[i])%step;
        for (int j = 0; j < 16; j++ )
        {
            value_groups[i][j] = origin_values[start + j*step];
            // move backend values to blanks
            if (step > 1 && backpos >= 16*(step-1))
            {
                if (backpos%step != start)
                    origin_values[start+j*step] = origin_values[backpos];
                else
                {
                    do
                    {
                        backpos--;
                    } while (backpos%step == start);
                    if (backpos >= 16*(step-1))
                        origin_values[start+j*step] = origin_values[backpos];
                }

                do
                {
                    backpos--;
                } while (backpos%step == start);
                if (backpos < 16*(step-1) - 1)
                    backpos = 16*(step-1) - 1;
            }
        }
        step--;
    }
    
    // exchange in every groups as md5 value specified.
    for (int i = 0; i < 16; i++)
    {
        ExchangeInGroup(value_groups, i, md5);
    }
 
    // merge every group, generate the final encode table
    for (int i = 0; i < 256; i++)
    {
        enTable[i] = value_groups[i/16][i%16];
    }
    
    // check encode table and generate final decode table.
    for (int i = 0; i < 256; i++)
        origin_values[i] = 0;
    
    for (int i = 0; i < 256; i++)
    {
        if (origin_values[enTable[i]] > 0)
            THROW(Invalid_Cipher_Table);
        origin_values[enTable[i]] = 1;
    }
    
}

void Cipher::GetDecodeTableOfEncodeTable(Uint8 *deTable, Uint8 *enTable)
{
    int check_values[256] = {0};
    for (int i = 0; i < 256; i++)
    {
        if (check_values[enTable[i]] > 0)
            THROW(Invalid_Cipher_Table);
        deTable[enTable[i]] = i;
        check_values[enTable[i]] = 1;
    }
}

void Cipher::EncodeWithTable(Uint8 *buf, Uint32 len, Uint8 *enTable)
{
    for (int i = 0; i < len; i++)
    {
        buf[i] = enTable[buf[i]];
    }
}

void Cipher::DecodeWithTable(Uint8 *buf, Uint32 len, Uint8 *deTable)
{
    for (int i = 0; i < len; i++)
    {
        buf[i] = deTable[buf[i]];
    }
}
