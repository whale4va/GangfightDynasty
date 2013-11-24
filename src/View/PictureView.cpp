#include "PictureView.h"

void PictureView::Display()
{
    if (pSprite == NULL && !resourceName.empty())
    {
        pSprite = new CCSprite();
        pSprite->initWithFile(resourceName);
    }
    
    if (pSprite)
    {
        if (dimension.w != 0 && dimension.h != 0)
        {
            cocos2d::CCSize picSize = pSprite->getContentSize();
            float scaleX = (float)dimension.w/picSize.width;
            float scaleY = (float)dimension.h/picSize.height;
            pSprite->setScaleX(scaleX);
            pSprite->setScaleY(scaleY);
            //CCLOG("Picture content size = (%f, %f)\n", picSize.width, picSize.height);
            //pSprite->setTextureRect(GetCCRect()); // only cut outdedicate area
        }
        
        pSprite->setPosition(ToCCPoint(position));
        if (pSprite->getParent() == NULL)
            _node->addChild(pSprite, position.z);
    }
    
    return;
}
