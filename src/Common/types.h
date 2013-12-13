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

// global macros
#define GAME_FONT "BiauKai"     // BiauKai.ttf - Info.plst - Font provided by application
#define FLOAT_MINOR_LIMIT 0.00001	// lower than this value defined as float 0.0

// global types
typedef bool Boolean;
typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;

/**
 @brief game point define
 */
typedef struct _Point
{
    float x, y, z;
    _Point():x(0.0),y(0.0),z(0.0) {}
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
    Format_Parsing_Error,			// format string parsing error.
    String_Not_UTF8,				// string is not in UTF-8 encoding.
    Method_Not_Support,				// This method not support in the object.
    Tab_Not_In_Group				// this tab view not put into a group yet.
}ExceptionId;


/**
 * @brief define self throw macro, print more information about throw point
 */
#define THROW(_EID_) \
{\
    CCLOG("throw exception %d from %s:%d\n", _EID_, __FILE__, __LINE__); \
    throw (_EID_); \
}

#endif
