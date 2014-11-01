#ifndef PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E
#define PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E
#include "ViewFrame.h"

using cocos2d::CCSprite;
using cocos2d::CCTexture2D;

//##ModelId=522B2DB4025F
class PictureView : public ViewFrame
{
public:
    PictureView(CCNode* n) : ViewFrame(n), pSprite(NULL), pTexture(NULL) {}
    PictureView(CCNode* n, String picName) : ViewFrame(n), pSprite(NULL),
            resourceName(picName), pTexture(NULL) {}
    PictureView(const PictureView& orig) : ViewFrame(orig),
            pSprite(NULL), pTexture(NULL), resourceName(orig.resourceName) {}
    PictureView(CCNode* n, CCTexture2D* pT) : ViewFrame(n), pSprite(NULL),
            pTexture(pT) {}
    
    PictureView& operator=(const PictureView& orig)
    {
        if (this != &orig)
        {
            *((ViewFrame*)this) = orig;
            if (pSprite)
            {
                delete pSprite;
                pSprite = NULL;
            }
            resourceName = orig.resourceName;
            pTexture = orig.pTexture;
        }
        return *this;
    }
    
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
    CCTexture2D* pTexture;
    
private:
    PictureView();
    CCSprite* pSprite;
};



#endif /* PICTUREVIEW_H_HEADER_INCLUDED_AD80A68E */
