#include "PureColorBar.h"

void PureColorBar::Display()
{
    if (dimension.w == 0 || dimension.h == 0)
        return;     // no geometry for object, don't display anything
    else
    {
        if (pTexture == NULL)
        {
            pTexture = new cocos2d::CCRenderTexture;
            assert(pTexture);
            pTexture->initWithWidthAndHeight(dimension.w, dimension.h, cocos2d::kCCTexture2DPixelFormat_RGBA8888);
        }
        
        Point lpt, rpt, lept, rept;
        lpt.x = lpt.y = 0.0;
        lept.x = dimension.w*percentage/100;
        lept.y = dimension.h;
        rpt.x = lept.x;
        rpt.y = 0;
        rept.x = dimension.w;
        rept.y = dimension.h;
        
        pTexture->beginWithClear(0.0, 0.0, 0.0, 1.0);
        //glDisable(GL_BLEND);
        cocos2d::ccDrawSolidRect(ToCCPoint(lpt), ToCCPoint(lept), ToColor4F(leftColor));
        cocos2d::ccDrawSolidRect(ToCCPoint(rpt), ToCCPoint(rept), ToColor4F(rightColor));
        //glEnable(GL_BLEND);
        pTexture->end();
        
        pTexture->setPosition(ToCCPoint(position));
        if (pTexture->getParent() == NULL)
            _node->addChild(pTexture, position.z);
    }
    
    return;
}

void PureColorBar::SetLeftColor(Uint32 lc)
{
    leftColor = lc;
    Display();
    return;
}

void PureColorBar::SetRightColor(Uint32 rc)
{
    rightColor = rc;
    Display();
    return;
}

void PureColorBar::SetPercentage(Uint8 val)
{
    percentage = val;
    Display();
    return;
}
