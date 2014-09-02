//
//  NumberTabView.cpp
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-8-24.
//
//

#include "NumberTabView.h"

Uint8 NumberTab::widthProportion = 94;
Uint8 NumberTab::buttonsHeightProportion = 78;
Uint8 NumberTab::textHeightProportion = 10;
Uint8 NumberTab::warningHeightProportion = 6;
Uint8 NumberTab::borderProportion = 3;

bool NumberTab::OnButton()
{
    bool ret = false;
    // deal with button pressed.
    Uint32 oldValue = finalValue;
    switch (_senderId)
    {
        case BTN_BACK_SPACE:
            finalValue /= 10;
            ret = true;
            break;
        case BTN_CLEAR:
            finalValue = 0;
            ret = true;
            break;
        case BTN_MAX:
            finalValue = maxValue;
            ret = true;
            break;
        case BTN_NUM_0:
            finalValue *= 10;
            ret = true;
            break;
        case BTN_NUM_00:
            finalValue *= 100;
            ret = true;
            break;
        case BTN_NUM_000:
            finalValue *= 1000;
            ret = true;
            break;
        case BTN_NUM_1:
            finalValue *= 10;
            finalValue += 1;
            ret = true;
            break;
        case BTN_NUM_2:
            finalValue *= 10;
            finalValue += 2;
            ret = true;
            break;
        case BTN_NUM_3:
            finalValue *= 10;
            finalValue += 3;
            ret = true;
            break;
        case BTN_NUM_4:
            finalValue *= 10;
            finalValue += 4;
            ret = true;
            break;
        case BTN_NUM_5:
            finalValue *= 10;
            finalValue += 5;
            ret = true;
            break;
        case BTN_NUM_6:
            finalValue *= 10;
            finalValue += 6;
            ret = true;
            break;
        case BTN_NUM_7:
            finalValue *= 10;
            finalValue += 7;
            ret = true;
            break;
        case BTN_NUM_8:
            finalValue *= 10;
            finalValue += 8;
            ret = true;
            break;
        case BTN_NUM_9:
            finalValue *= 10;
            finalValue += 9;
            ret = true;
            break;
        case BTN_OK:
            isOk = true;
            ret = true;
            Dismiss();
            break;
        case BTN_TAB_GROUP_DISMISS:
            isOk = false;
            ret = true;
            Dismiss();
            break;
        default:
            CCLOG("NumberTab::Onbutton get invalid id=%d\n", _senderId);
            break;
    }
    
    if (oldValue != finalValue)
    {   // redraw number text
        numberText.Dismiss();
        char buf[32] = {'\0'};
        sprintf(buf, "%d", finalValue);
        numberText.SetContent(buf);
        numberText.Display();
    }
    
    if (false == ret && NULL != parentView)
    {
        parentView->SetSenderId(_id);
        ret = parentView->OnButton();
    }
    return ret;
}

void NumberTab::Display()
{
    if (!dimension.IsValid())
        THROW(Invalid_Dimension);
    
    if (!numberButtons.dimension.IsValid())
    {   // not initialized yet, set buttons
        Dimension dim = dimension;
        dim.w = dim.w * widthProportion/100;
        dim.h = dim.h * buttonsHeightProportion / 100;
        numberButtons.SetDimension(dim);
        
        // not set background, using transparent, using tab background
        numberButtons.AddCommonButtonAt(0, 0, ResourceUri::button1PictureName);
        numberButtons.AddCommonButtonAt(0, 1, ResourceUri::button2PictureName);
        numberButtons.AddCommonButtonAt(0, 2, ResourceUri::button3PictureName);
        numberButtons.AddCommonButtonAt(0, 3, ResourceUri::backspaceButtonPictureName);
        
        numberButtons.AddCommonButtonAt(1, 0, ResourceUri::button4PictureName);
        numberButtons.AddCommonButtonAt(1, 1, ResourceUri::button5PictureName);
        numberButtons.AddCommonButtonAt(1, 2, ResourceUri::button6PictureName);
        numberButtons.AddCommonButtonAt(1, 3, ResourceUri::maxButtonPictureName);
        
        numberButtons.AddCommonButtonAt(2, 0, ResourceUri::button7PictureName);
        numberButtons.AddCommonButtonAt(2, 1, ResourceUri::button8PictureName);
        numberButtons.AddCommonButtonAt(2, 2, ResourceUri::button9PictureName);
        numberButtons.AddCommonButtonAt(2, 3, ResourceUri::clearButtonPictureName);
        
        numberButtons.AddCommonButtonAt(3, 0, ResourceUri::button0PictureName);
        numberButtons.AddCommonButtonAt(3, 1, ResourceUri::button00PictureName);
        numberButtons.AddCommonButtonAt(3, 2, ResourceUri::button000PictureName);
        numberButtons.AddCommonButtonAt(3, 3, ResourceUri::okButtonPictureName);
       
        // set buttons' ids
        numberButtons.SetButtonIdAd(0, 0, BTN_NUM_1);
        numberButtons.SetButtonIdAd(0, 1, BTN_NUM_2);
        numberButtons.SetButtonIdAd(0, 2, BTN_NUM_3);
        numberButtons.SetButtonIdAd(0, 3, BTN_BACK_SPACE);
        
        numberButtons.SetButtonIdAd(1, 0, BTN_NUM_4);
        numberButtons.SetButtonIdAd(1, 1, BTN_NUM_5);
        numberButtons.SetButtonIdAd(1, 2, BTN_NUM_6);
        numberButtons.SetButtonIdAd(1, 3, BTN_MAX);
        
        numberButtons.SetButtonIdAd(2, 0, BTN_NUM_7);
        numberButtons.SetButtonIdAd(2, 1, BTN_NUM_8);
        numberButtons.SetButtonIdAd(2, 2, BTN_NUM_9);
        numberButtons.SetButtonIdAd(2, 3, BTN_CLEAR);
        
        numberButtons.SetButtonIdAd(3, 0, BTN_NUM_0);
        numberButtons.SetButtonIdAd(3, 1, BTN_NUM_00);
        numberButtons.SetButtonIdAd(3, 2, BTN_NUM_000);
        numberButtons.SetButtonIdAd(3, 3, BTN_OK);
    }
    
    if (!numberText.dimension.IsValid())
    {   // initilize number text view
        Dimension dim = dimension;
        dim.w = dim.w * widthProportion/100;
        dim.h = dim.h * textHeightProportion/100;
        numberText.SetDimension(dim);
    }
   
    // set positions and display
    Point pt = position;
    pt.z += 1.0;
    
    pt.y += dimension.h/2;
    float minusH = dimension.h*borderProportion/100;    // border height
    minusH += dimension.h*warningHeightProportion/100;  // warning text height
    
    minusH += dimension.h*textHeightProportion/200;     // number text height/2
    pt.y -= minusH;
    numberText.SetPoint(pt);
    numberText.Display();
    minusH += dimension.h*textHeightProportion/200;     // number text height/2
    
    minusH += dimension.h*buttonsHeightProportion/200;  // buttons height/2
    pt.y = position.y + dimension.h/2 - minusH;
    numberButtons.SetPoint(pt);
    numberButtons.Display();
    
}

void NumberTab::ShowWarningText()
{
    if (!warningText.dimension.IsValid())
    {
        Dimension dim = dimension;
        dim.w = dim.w * widthProportion/100;
        dim.h = dim.h * warningHeightProportion/100;
        numberText.SetDimension(dim);
    }
    
    float borderH = dimension.h*borderProportion/100;
    float warningH = dimension.h*warningHeightProportion/100;
    Point pos = position;
    pos.y += dimension.h/2;
    pos.y -= (borderH + warningH/2);
    pos.z += 1.0;
    
    warningText.SetPoint(pos);
    warningText.Display();
}

