#ifndef PURECOLORBAR_H_HEADER_INCLUDED_AD80CE3E
#define PURECOLORBAR_H_HEADER_INCLUDED_AD80CE3E

#include "ViewFrame.h"

using cocos2d::CCRenderTexture;

//##ModelId=522C70E80173
class PureColorBar : public ViewFrame
{
public:
    PureColorBar(cocos2d::CCNode* n) : ViewFrame(n), leftColor(0x000000FF),
    rightColor(0xFFFFFFFF), percentage(50), pTexture(NULL){}
    PureColorBar(cocos2d::CCNode* n, Uint32 lc, Uint32 rc) : ViewFrame(n),
    leftColor(lc), rightColor(rc), percentage(50), pTexture(NULL) {}
    
    // 注意：拷贝构造 & 赋值的时候 cocos2d-x里面的资源指针，链表指针，均赋值为NULL，避免多个对象操作同一个cocos2d-x资源冲突
    PureColorBar(const PureColorBar& orig) : ViewFrame(orig), leftColor(orig.leftColor),
    rightColor(orig.rightColor), percentage(orig.percentage), pTexture(NULL) {}
    
    PureColorBar& operator=(const PureColorBar& orig)
    {
       if (this != &orig)
       {
           *((ViewFrame*)this) = orig;
           leftColor = orig.leftColor;
           rightColor = orig.rightColor;
           percentage = orig.percentage;
           if (pTexture)
           {
               delete pTexture;
               pTexture = NULL;
           }
       }
        return *this;
    }
    
    void SetLeftColor(Uint32 lc);
    Uint32 GetLeftColor() { return leftColor; }
    
    void SetRightColor(Uint32 rc);
    Uint32 GetRightColor() { return rightColor; }
    
    void SetPercentage(Uint8 val);
    Uint8 GetPercentage() { return percentage; }
    
    void Display();
    inline void Dismiss()
    {
        if (pTexture)
        {
            _node->removeChild(pTexture);
        }
    }
    
    inline void Destory()
    {
        if (pTexture->getParent())
            Dismiss();
        if (pTexture)
        {
            delete pTexture;
            pTexture = NULL;
        }
    }
    
    inline ~PureColorBar()
    {
        Destory();
    }
    
private:
    PureColorBar();
    
    //##ModelId=522C718C01BF
    Uint32 leftColor;
    //##ModelId=522C71980104
    Uint32 rightColor;
    //##ModelId=522C71C90235
    Uint8 percentage;
    
    /**
     @brief cocos2d-x specific objects
     */
    cocos2d::CCRenderTexture* pTexture;

};


#endif /* PURECOLORBAR_H_HEADER_INCLUDED_AD80CE3E */
