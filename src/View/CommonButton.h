#ifndef COMMONBUTTON_H_HEADER_INCLUDED_AD80E474
#define COMMONBUTTON_H_HEADER_INCLUDED_AD80E474
#include "PictureView.h"
#include "ViewFrame.h"

using cocos2d::CCMenuItemImage;
using cocos2d::SEL_MenuHandler;
using cocos2d::CCMenu;
using cocos2d::CCNode;


//##ModelId=522B30BB0317
//class CommonButton : public ViewFrame, public PictureView
class CommonButton : public PictureView, public cocos2d::CCObject
{
  public:
    //##ModelId=522F2443033C
    Uint32 GetId();

    //##ModelId=522F266301A2
    void SetEnable(bool en);

    //##ModelId=522F266F035D
    void SetVisible(bool vi);
    
    inline CommonButton(CCNode* n) : PictureView(n), pButton(NULL), enabled(true), visible(true),
    pButtonContainer(NULL), framesFileName(ResourceUri::buttonPictureAtlas), inGroup(false){}
    inline CommonButton(CCNode* n, String picName) : PictureView(n, picName), inGroup(false), enabled(true),
    visible(true), pButton(NULL), pButtonContainer(NULL), framesFileName(ResourceUri::buttonPictureAtlas) {}
    
    inline void SetFramesFileName(String& fn) { framesFileName = fn; }
    
    void Display();
    inline void Destory()
    {
        if (pButtonContainer && pButtonContainer->getParent())
            Dismiss();
        if (pButton)
        {
            delete pButton;
            pButton = NULL;
        }
        if (!inGroup && pButtonContainer)
        {
            delete pButtonContainer;
            pButtonContainer = NULL;
        }
    }
    
    inline void Dismiss()
    {
        if (pButtonContainer->getParent())
            _node->removeChild(pButtonContainer);
    }
    
    inline ~CommonButton()
    {
        Destory();
    }
    
    /**
     * transfer CCLayer event to internal CCMenu
     **/
    inline virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
    {
        if (pButtonContainer)
        {
            return pButtonContainer->ccTouchBegan(pTouch, pEvent);
        }
        return false;
    }

    inline virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (pButtonContainer)
        {
            pButtonContainer->ccTouchMoved(pTouch, pEvent);
        }
    }
    
	inline virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (pButtonContainer)
        {
            pButtonContainer->ccTouchEnded(pTouch, pEvent);
        }
    }
	inline virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (pButtonContainer)
        {
            pButtonContainer->ccTouchCancelled(pTouch, pEvent);
        }
    }
    
    /**
     @brief button event (tap) handler function
     */
    void MenuHandler(cocos2d::CCObject* pSender);
    
    inline void SetButtonContainer(cocos2d::CCMenu* pM)
    {
        assert(pM);
        if (pButtonContainer && pButton)
        {
            pButtonContainer->removeChild(pButton, true);
        }
        pButtonContainer = pM;
        if (pButton)
            pButtonContainer->addChild(pButton);
    }
    inline void SetInGroup(bool ig) { inGroup = ig; }
    
    CommonButton(const CommonButton& cb);    
    CommonButton& operator=(const CommonButton& cb);

  private:
    CommonButton();

    //##ModelId=522B317B0146
    bool enabled;
    //##ModelId=522B31820205
    bool visible;
    
    /** @brief indicate the button is in a group or not */
    bool inGroup;
    
    /** cocos2d-X specific objects */
    CCMenuItemImage* pButton;
    CCMenu* pButtonContainer;
    String framesFileName;
    String normalPic, selectedPic, disabledPic;
    
    /**
     @brief deduce button pictures name, include: normal, selected, disabled
     according to resource name of superceded from PictureView.
     */
    void DeducePictureName() throw(ExceptionId);
    
};



#endif /* COMMONBUTTON_H_HEADER_INCLUDED_AD80E474 */
