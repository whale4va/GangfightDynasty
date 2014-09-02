//
//  NumberTabView.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-8-24.
//
//

#ifndef GangfightDynasty_NumberTabView_h
#define GangfightDynasty_NumberTabView_h

#include "ButtonGroupPopupView.h"
#include "TabGroupView.h"

using cocos2d::CCNode;

class NumberTab : public TabView
{
public:
    NumberTab(CCNode* node, String title, Uint32 max) : TabView(node, title),
                numberButtons(node, 4, 4), numberText(node, "0", true),
                warningText(node, "", true),
                finalValue(0), maxValue(max)
    {
        subview.Add(&numberButtons);
        subview.Add(&numberText);
        subview.Add(&warningText);
        
        numberButtons.SetParentView(this);
        numberText.SetParentView(this);
        warningText.SetParentView(this);
        char buf[32] = {'\0'};
        sprintf(buf, "%u", maxValue);
        String str("合理的最大值是：");
        str.append(buf);
        CCLOG("warning text of NumberTab is: %s\n", (const char*)str);
        warningText.SetContent(str);
    }
    
    virtual bool OnButton();
    
    virtual void Display();
    virtual void Dismiss()
    {
        numberButtons.Dismiss();
        numberText.Dismiss();
        warningText.Dismiss();
    }
    
    virtual void Destory()
    {
        Dismiss();
        numberText.Destory();
        numberButtons.Destory();
        warningText.Destory();
    }
    
    inline Uint32 GetFinalValue()
    {
        return finalValue;
    }
    inline bool GetIsOk()
    {
        return isOk;
    }
    
    void ShowWarningText();
    
    inline void HideWarningText()
    {
        warningText.Dismiss();
    }
    
private:
    // showing buttons, for touching
    ButtonGroupPopupView numberButtons;
    
    // showing text for number showing
    TextView numberText;
    
    // showing warning taxt for invalid input
    TextView warningText;
    
    // number tab choosed final value.
    Uint32 finalValue;
    
    // acceptable maximum value
    Uint32 maxValue;
    
    // is ok clicked
    bool isOk;
    
    // dimension proportion of sub views in this view frame
    static Uint8 widthProportion;
    static Uint8 buttonsHeightProportion;
    static Uint8 textHeightProportion;
    static Uint8 warningHeightProportion;
    static Uint8 borderProportion;
    
};

class NumberTabView : public TabGroupView
{
    
public:
    NumberTabView(CCNode* node):TabGroupView(node) {
        this->SetIsModal(true);
    }
    
    inline bool GetIsOK()
    {
        if (subview.GetLength() == 0)
            return false;
        else
        {
            return ((NumberTab*)subview[0])->GetIsOk();
        }
        return false;
    }
};

#endif
