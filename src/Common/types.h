//
//  types.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 13-11-10.
//
//

#ifndef GangfightDynasty_types_h
#define GangfightDynasty_types_h

#include <assert.h>
#include <string.h>
//#include "ccTypes.h"
#include "cocos2d.h"
#include "ids.h"
#include "ResourceUri.h"

// global macros
#define GAME_FONT "BiauKai"     // BiauKai.ttf - Info.plst - Font provided by application
#define FLOAT_MINOR_LIMIT 0.00001	// lower than this value defined as float 0.0

// global types
typedef bool Boolean;
typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;
typedef unsigned long long Uint64;

/**
 @brief game point define
 */
typedef struct _Point
{
    float x, y, z;
    _Point():x(0.0),y(0.0),z(0.0) {}
    
    _Point(const _Point& orig):x(orig.x),y(orig.y),z(orig.z) {}
}Point;

inline Point mkPoint(float x, float y, float z = 0)
{
    Point pt;
    pt.x = x;
    pt.y = y;
    pt.z = z;
    return pt;
}

inline cocos2d::CCPoint ToCCPoint(Point pt)
{
    cocos2d::CCPoint p;
    p.x = pt.x;
    p.y = pt.y;
    return p;
}

/**
 @brief game dimension define
 */
typedef struct _Dimension
{
    float w, h;
    _Dimension():w(0.0),h(0.0){}
    
    _Dimension(const _Dimension& orig):w(orig.w),h(orig.h) {}
    
    bool IsValid()
    {
        if (w > FLOAT_MINOR_LIMIT && h > FLOAT_MINOR_LIMIT)
            return true;
        else
            return false;
    }
}Dimension;

inline Dimension mkDimension(float w, float h)
{
    Dimension dim;
    dim.w = w;
    dim.h = h;
    return dim;
}

inline cocos2d::CCSize ToCCSize(Dimension di)
{
    cocos2d::CCSize si;
    si.width = di.w;
    si.height = di.h;
    return si;
}

/**
 @brief convert internal Uint32 to 3 bytes color
 Uint32 is in format R-G-B-A
 */
inline cocos2d::ccColor3B ToColor3B(Uint32 src)
{
    cocos2d::ccColor3B color;
    color.r = (src & 0xFF000000) >> 24;
    color.g = (src & 0x00FF0000) >> 16;
    color.b = (src & 0x0000FF00) >> 8;
    return color;
}

/**
 @brief coner internal Uint32 to 4 bytes color
 Uint32 is in format R-G-B-A
 */
inline cocos2d::ccColor4B ToColor4B(Uint32 src)
{
    cocos2d::ccColor4B color;
    color.r = (src & 0xFF000000) >> 24;
    color.g = (src & 0x00FF0000) >> 16;
    color.b = (src & 0x0000FF00) >> 8;
    color.a = (src & 0x000000FF);
    return color;
}

/**
 @brief convert color to 4 float color
 */
inline cocos2d::ccColor4F ToColor4F(Uint32 src)
{
    cocos2d::ccColor4F color;
    float element = 0.0;
    element = (float)((src & 0xFF000000) >> 24);
    color.r = element/255.00;
    element = (float)((src & 0x00FF0000) >> 16);
    color.g = element/255.00;
    element = (float)((src & 0x0000FF00) >> 8);
    color.b = element/255.00;
    element = (float)((src & 0x000000FF));
    color.a = element/255.00;
    return color;
}

/**
 @brief cocos2d-X context used for display views in cocos2d-X environment
 */
typedef struct _CCContext
{
//    cocos2d::CCScene* scene;
    cocos2d::CCLayer* layer;
    
    _CCContext(const _CCContext& orig):layer(orig.layer) {}
}CCContext;

/**
 @brief exception ID define enumeration
 */
typedef enum _ExceptionId
{
    Memory_Allocate_Failed = 1,     // Failed to allocate memory.
    Invalid_Index,                  // Invalid (illegal) index of array.
    Invalid_ResourceName,           // Invalid (illegal) resource (picture) name.
    Invalid_Dimension,				// Invalid (illegal) dimension defined.
    Invalid_RichTextFormat,			// Invalid (illegal) rich text format string.
    Invalid_RichTextElement,		// Invalid (illegal) rich text element not match.
    Invalid_ListRowHeight,          // Invalid (illegal) list view row height in pixel.
    Invalid_ColumnWidthPercentage,  // Invalid (illegal) column widhth in percentage.
    Format_Parsing_Error,			// format string parsing error.
    String_Not_UTF8,				// string is not in UTF-8 encoding.
    Method_Not_Support,				// This method not support in the object.
    Tab_Not_In_Group				// this tab view not put into a group yet.
}ExceptionId;


/*****************************************
 * @brief Enumerate values in this section
 * 定义所有的枚举值的节
 *****************************************/

/**
 * Weapon Type definition
 **/
#ifndef WEAPONTYPE_H_HEADER_INCLUDED_AC6D6C2F
#define WEAPONTYPE_H_HEADER_INCLUDED_AC6D6C2F
//##ModelId=5228843003C4
typedef enum _WeaponType
{
    Weapon_Sword = 1,               // 步兵/剑兵
    Weapon_Spear,                   // 枪兵
    Weapon_Horse,                   // 骑兵
    Weapon_Arrow                    // 弓箭兵
}WeaponType;
#endif /* WEAPONTYPE_H_HEADER_INCLUDED_AC6D6C2F */

/**
 * Upgrade Type definition
 **/
#ifndef UPGRADETYPE_H_HEADER_INCLUDED_AC6D24A1
#define UPGRADETYPE_H_HEADER_INCLUDED_AC6D24A1
//##ModelId=522C85F300D0
typedef enum _UpgradeType
{
    Upgrade_Agriculture = 1,       //升级农业
    Upgrade_Business,             //升级商业
    Upgrade_Security,               //升级治安
    Upgrade_City,                   //升级城市
    Upgrade_Soldier,                //招募(升级)士兵
    Upgrade_Sword,                  //生产(升级)剑
    Upgrade_Spear,                  //生产枪
    Upgrade_Horse,                  //生产马匹
    Upgrade_Arrow                   //生产弓箭
}UpgradeType;
#endif /* UPGRADETYPE_H_HEADER_INCLUDED_AC6D24A1 */

/**
 * Strategy Type definition
 **/
#ifndef STRATEGYTYPE_H_HEADER_INCLUDED_AC6D35D6
#define STRATEGYTYPE_H_HEADER_INCLUDED_AC6D35D6
//##ModelId=5228A7340024
typedef enum _StrategyType
{
    Strategy_Upgrade = 1,       //生产(升级)优先的方针
    Strategy_Attack             //进攻优先的方针
}StrategyType;
#endif /* STRATEGYTYPE_H_HEADER_INCLUDED_AC6D35D6 */



/**
 * Event Type definition
 **/
#ifndef EVENTTYPE_H_HEADER_INCLUDED_AC6D220D
#define EVENTTYPE_H_HEADER_INCLUDED_AC6D220D
//##ModelId=522B25AB0361
typedef enum _EventType
{
    Event_Upgrade_Done = 1,     //升级完成
    Event_Warfare_Start,        //战争开始
    Event_Army_Active           //战斗中，部队激活
}EventType;
#endif /* EVENTTYPE_H_HEADER_INCLUDED_AC6D220D */


/*****************************************
 * @brief Macros in this section
 * 定义所有的宏的节
 *****************************************/


/**
 * @brief define self throw macro, print more information about throw point
 */
#define THROW(_EID_) \
{\
    CCLOG("throw exception %d from %s:%d\n", _EID_, __FILE__, __LINE__); \
    throw (_EID_); \
}

#define SET_U64_BIT(_U64_,_POS_) _U64_ |= ((Uint64)0x01) << _POS_ )
#define ISSET_U64_BIT(_U64_,_POS_) (_U64_ & ((Uint64)0x01 << _POS_))
#define CLEAR_U64_BIT(_U64_,_POS_) _U64_ &= (~((Uint64)0x01 << _POS_))

#endif
