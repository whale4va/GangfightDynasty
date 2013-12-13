#ifndef PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E
#define PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E
#include "ViewFrame.h"

using cocos2d::CCSprite;

//##ModelId=522B2DB4025F
class PictureView : public ViewFrame
{
public:
    PictureView(CCNode* n) : ViewFrame(n), pSprite(NULL) {}
    PictureView(CCNode* n, String picName) : ViewFrame(n), pSprite(NULL), resourceName(picName) {}
    
    void Display();
    inline void Dismiss()
    {
        if (pSprite->getParent())
            _node->removeChild(pSprite);
    }
    
    inline void Destory()
    {
        if (pSprite)
        {
            Dismiss();
            delete pSprite;
            pSprite = NULL;
        }
    }
    
    virtual inline ~PictureView()
    {
        Destory();
    }
    
    inline Dimension GetPictureDimension()
    {
        if (pSprite)
        {
            cocos2d::CCSize sz = pSprite->getContentSize();
            return mkDimension(sz.width, sz.height);
        }
        else
        {
            return mkDimension(0, 0);
        }
    }
    
    inline String GetResourceName() {return resourceName; }
    inline void SetResourceName(String picName) { resourceName = picName; }
    
protected:
    /** picture file name. */
    //##ModelId=522B3087037F
    String resourceName;
    
private:
    PictureView();
    CCSprite* pSprite;
};



#endif /* PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E */
