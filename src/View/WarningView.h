#ifndef WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#define WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#include "CommonButton.h"
#include "TabGroupView.h"
#include "RichTextView.h"

using cocos2d::CCNode;

class WarningViewTab : public TabView
{
    
public:
    
    //##ModelId=522F2E360215
    inline void SetRichTextView(const RichTextView& rtv)
    {
        warningText = rtv;
    }

    //##ModelId=524ED4D50189
    inline void SetIsOk(bool ok) {isOk = ok;}

    //##ModelId=524ED4F00340
    inline bool GetIsOk() {return isOk;}
    
    virtual bool OnButton()
    {
        CCLOG("WarningViewTab button clicked on %d(0x%X).\n", _senderId, _senderId);
        bool ret = false;
        switch (_senderId)
        {
            case BTN_OK:
                isOk = true;
                ret = true;
                parentView->Dismiss();
                break;
            case BTN_CANCEL:
                ret = true;
                parentView->Dismiss();
                break;
            default:
                break;
        }
        return ret;
    }
    
    virtual void Display();
    virtual void Dismiss()
    {
        okButton.Dismiss();
        warningText.Dismiss();
    }
    
    virtual void Destory()
    {
        Dismiss();
        okButton.Destory();
        warningText.Destory();
    }
    
    // touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
    {
        _needEvent = okButton.ccTouchBegan(pTouch, pEvent);
        return _needEvent;
    }
    
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (_needEvent)
            okButton.ccTouchMoved(pTouch, pEvent);
    }
    
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (_needEvent) {
            okButton.ccTouchEnded(pTouch, pEvent);
            _needEvent = false;
        }
    }
    
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
        if (_needEvent) {
            okButton.ccTouchCancelled(pTouch, pEvent);
            _needEvent = false;
        }
    }

    ////////
    // constructors & deconstructors
    ////////
    WarningViewTab(CCNode* node):TabView(node), warningText(node),
        okButton(node, ResourceUri::okButtonPictureName), isOk(false)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    WarningViewTab(CCNode* node, String title):TabView(node, title), warningText(node),
        okButton(node, ResourceUri::okButtonPictureName), isOk(false)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    WarningViewTab(CCNode* node, String title, const RichTextView& rtv):TabView(node, title), warningText(rtv),
        okButton(node, ResourceUri::okButtonPictureName), isOk(false)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    
    
    WarningViewTab(const WarningViewTab& orig):TabView(orig), warningText(orig.warningText), isOk(orig.isOk),
        okButton(orig._node, ResourceUri::okButtonPictureName)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    
    WarningViewTab& operator=(const WarningViewTab& orig)
    {
        if (this != &orig)
        {
            *((TabView*)this) = (TabView)orig;
            warningText = orig.warningText;
            isOk = orig.isOk;
            subview.Release();
            this->subview.Add(&warningText);
            this->subview.Add(&okButton);
            warningText.SetParentView(NULL);
            okButton.SetParentView(NULL);
        }
        return *this;
    }
    
private:
    //##ModelId=522C732A0082
    RichTextView warningText;
    //##ModelId=522C73370282
    CommonButton okButton;
    //##ModelId=524ED33F0361
    bool isOk;
    
    static int borderSize;
};

//##ModelId=522C730D006A
class WarningView : public TabGroupView
{
  public:
    WarningView(CCNode* node):TabGroupView(node) {
        this->SetIsModal(true);
    }
    
    inline bool GetIsOK()
    {
        if (subview.GetLength() == 0)
            return false;
        else
        {
            return ((WarningViewTab*)subview[0])->GetIsOk();
        }
        return false;
    }
};



#endif /* WARNINGVIEW_H_HEADER_INCLUDED_AD809A66 */
