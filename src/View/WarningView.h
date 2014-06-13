#ifndef WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#define WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#include "CommonButton.h"
#include "TabGroupView.h"
#include "RichTextView.h"

using cocos2d::CCNode;

//##ModelId=522C730D006A
class WarningView : public TabView
{
  public:
    //##ModelId=522F2CF7036B
    void InitWithString();

    //##ModelId=522F2E360215
    inline void SetRichTextView(const RichTextView& rtv)
    {
        warningText = rtv;
    }

    //##ModelId=524ED4D50189
    inline void SetIsOk(bool ok) {isOk = ok;}

    //##ModelId=524ED4F00340
    inline bool GetIsOk() {return isOk;}
    
    void Display();
    void Dismiss();
    void Destory();

    ////////
    // constructors & deconstructors
    ////////
    WarningView(CCNode* node):TabView(node), warningText(node),
        okButton(node, ResourceUri::okButtonPictureName), pHolder(NULL)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    WarningView(CCNode* node, String title):TabView(node, title), warningText(node),
        okButton(node, ResourceUri::okButtonPictureName), pHolder(NULL)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    WarningView(CCNode* node, String title, const RichTextView& rtv):TabView(node, title), warningText(rtv),
        okButton(node, ResourceUri::okButtonPictureName), pHolder(NULL)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    
    
    WarningView(const WarningView& orig):TabView(orig), warningText(orig.warningText), isOk(orig.isOk), pHolder(NULL),
        okButton(orig._node, ResourceUri::okButtonPictureName)
    {
        this->subview.Add(&warningText);
        this->subview.Add(&okButton);
        warningText.SetParentView(this);
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
    }
    
    WarningView& operator=(const WarningView& orig)
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
    
    TabGroupView* pHolder;      //承载显示的group view
};



#endif /* WARNINGVIEW_H_HEADER_INCLUDED_AD809A66 */
