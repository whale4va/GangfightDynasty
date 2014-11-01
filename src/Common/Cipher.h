//
//  Cipher.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-9-11.
//  Implement encrypt and decrypt algorithm
//

/**
 * 最初的算法设想是：利用  "用户名 + 定死的字符串" => 原始串
 * 用户的信息就是：用户账号名 和 用户的id + 密码
 *     MD5(原始串) =>  分组串 (128bit = 16*8 bit)
 *     分组串每字节为分组索引，从8bit表示的0 ~ 255中，求余出16个数作为一组
 *     
 *     每个分组索引字节，对应一个16字节的分组数
 *     每组利用索引字节的LFSR随机序列交换顺序
 *     合并打乱顺序的各组获得 加、解密 矩阵
 **/

/**
 * 新算法【取消】，直接利用LSFR生成够长周期的序列，不断交换两个随机索引的位置
 *      最初的原始值为 “用户名+定死的字符串” => 原始串 按字节 XOR | OR 操作得到的字节
 *      1个字节的循环，最长周期到255，足够使用。
 *      输出位b8，反馈位 b5 (偶数位，没有公因数)。 备选: b3, b5, b7, b8
 *      
 *      不能仅仅使用LFSR序列，因为序列顺序都一样，只是起始的位置随着起始字节变了
 *      意味着仅仅有256个密码表，太少了，不安全。
 **/

#ifndef GangfightDynasty_Cipher_h
#define GangfightDynasty_Cipher_h

#include "types.h"
#include "String.h"

class Cipher
{
private:
    static const String kingString;          //定死字符串
    static const Uint8 kingByte;
    
    static Uint8 encodeTable[];
    static Uint8 decodeTable[];
    
public:
    // static methods for cipher
    // generate next LSFR value for current byte
    // use only last 4 bits, for 16 radom numbers
    // use bit3 & bit4 to feedback.
    inline static Uint8 NextLSFRvalue(Uint8 val)
    {
        if ( 0x00 == val)  // if the start value = 0, than changed to 0x0F(15 = 1005).
            val = 0x0F;
        else
            val &= 0x0F;
        Uint8 bit = ((val>>1)^(val)) & 1;
        val = (bit << 3) | (val >> 1);
        return val;
    }
    
    // prepare start byte from user's name
    Uint8 PrepareStrartByteByUserName(String user);
    
    // generate cipher tables with user name
    static void GenerateCipherTableByUserName(String user);
    
    // encode with cipher table.
    static void Encode(Uint8* buf, Uint32 len);
    // decode with ciphser talbe.
    static void Decode(Uint8* buf, Uint32 len);
    
    // get encode table with specific key
    static void GetEncodeTableWithKey(String key, Uint8* enTable);
    
    // get decode table with encode table
    static void GetDecodeTableOfEncodeTable(Uint8* deTable, Uint8* enTable);
    
    // encoding with speicif table
    static void EncodeWithTable(Uint8* buf, Uint32 len, Uint8* enTable);
    // decoding with specific table
    static void DecodeWithTable(Uint8* buf, Uint32 len, Uint8* deTable);

    // 交换一个组16个字节的顺序，根据md5值的4位4位交换，最少7次。
    static void inline ExchangeInGroup(Uint8 value_groups[16][16],
                                       Uint8 row, Uint8 md5[])
    {
        Uint8 base = md5[row];
        int start = (base >> 4) & 0x0F;
        int number = base & 0x0F;
        if (number < 7)
            number = 7;
        
        for (int i = 0; i < number; i++)
        {
            int specific = md5[(start+i)%16];
            int previous = (specific >> 4) & 0x0F;
            int next = specific & 0x0F;
            Uint8 temp = value_groups[row][previous];
            value_groups[row][previous] = value_groups[row][next];
            value_groups[row][next] = temp;
        }
    }
    
    // debug, dump encode cipher table to see.
    static void inline DumpEncodeTable(Uint8* pTable)
    {
        if (NULL == pTable)
            CCLOG("====Dump internal encode table====\n");
        else
            CCLOG("====Dump external encode table====\n");
        
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (NULL != pTable)
                    CCLOG("0x%02X ", pTable[i*16+j]);
                else
                    CCLOG("0x%02X ", encodeTable[i*16+j]);
            }
            CCLOG("\n");
        }
    }
    
    
};


/**
 * 生成充值码，供客户端输入充值使用。充值码格式：
 * <订单号最后2个字节> + <用户id最后一个字节> + <物品类型编号字节> + <4个字节的Uint32的数量>
 *  总共8个字节，转换为16个字符
 *  订单号的最后2个字节，用用户名为key的密码表加密
 *  后续的6个字节用，订单号后2个字节作为key的密码表加密
 *      密码表的key都包含了 Cipher::kingString.
 *
 *  这样就保证了，每次充值，即使相同的业务也是不同的充值码，让用户无法猜测
 *  同时，端充值的流程为：
 *      1. 尝试联网充值，如果服务器能充值成功，服务器直接保留充值记录
 *      2. 无法联网，本地直接充值：
 *          若用户没有违约3次：
 *              查看本地存储的充值码是否包含正在使用图的充值码
 *                  包含，返还出错，不能重复使用
 *                  不包含，则充值成功，并记录到本地加密文件
 *          若有3次违约：
 *              告知用户因为违约次数已过，必须联网充值，输入的充值码才有效。
 *      3. 一旦联网后，同步本地的充值码充值记录到服务器，若用户在多个端使用同一个充值码
 *             则用户违约，这时，同步用户的资产值位最大的值到服务器，和端。（服务器与端对比），并记下
 *              违约记录，同时告知用户，已经违约一次，最多能违约3次，3次后必须联网充值。
 */

#endif
