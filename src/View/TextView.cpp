#include "TextView.h"

/**
 @brief show text content in CCLabelTTF object
 */
void TextView::Display()
{
    if (plabel == NULL)
    {
        plabel = new cocos2d::CCLabelTTF;
        assert(plabel);
        plabel->initWithString((const char*)content, (const char *)fontName, (float)size);
    }
    else
    {
        plabel->setString((const char*)content);
        plabel->setFontSize(size);
        plabel->setFontName((const char*)fontName);
    }
    plabel->setFontFillColor(ToColor3B(color), true);
    
    plabel->setPosition(ccp(position.x, position.y));
    if (dimension.w != 0 && dimension.h != 0)
    {
        plabel->setDimensions(ToCCSize(dimension));
        //plabel->setHorizontalAlignment(cocos2d::kCCTextAlignmentCenter);
        //plabel->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentCenter);
        plabel->setHorizontalAlignment(cocos2d::kCCTextAlignmentLeft);
        plabel->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentTop);
    }
    if (plabel->getParent() == NULL)
        _node->addChild(plabel, position.z);
}

/**
 @brief dismiss CCLableTTF that is showing text content
 */
void TextView::Dismiss()
{
    if (plabel->getParent())
        _node->removeChild(plabel);
}

/**
 @brief destory cocos2d-X resources if needed
 */
void TextView::Destory()
{
    if (plabel)
    {
        Dismiss();
        delete plabel;
        plabel = NULL;
    }
}

