#include "ButtonGroupPopupView.h"

Uint8 const ButtonGroupPopupView::dividerRatioW = 4;	// divider width = button width/4
Uint8 const ButtonGroupPopupView::dividerRatioH = 2;	// divider height = button height/2

//##ModelId=526930CE038D
void ButtonGroupPopupView::InitWithRowColumn(Uint32 row, Uint32 column)
{
    assert(row>0 && column>0);
    _row = row;
    _column = column;
    for (int i = 0; i < _row*_column - buttonList.GetLength(); i++)
    {
        buttonList.Add((CommonButton*)NULL);
    }
}

//##ModelId=5269367A0307
void ButtonGroupPopupView::SetCommonButtonAt(CommonButton* button, Uint32 row, Uint32 column)
{
    assert(row>=0 && row<_row);
    assert(column>=0 && column<_column);
    
    buttonList[(row*_column+column)] = button;
}

void ButtonGroupPopupView::AddCommonButtonAt(Uint32 row, Uint32 column, String picName, String framesName)
{
    assert(!picName.empty());
    assert(row < _row);
    assert(column < _column);
    if (framesName.empty())
    {
        framesName = "Buttons/buttons.plist";   // default sprite frame texture packer file
    }
    
    if (pButtonContainer == NULL)
    {
        pButtonContainer = new cocos2d::CCMenu;
        assert(pButtonContainer);
        pButtonContainer->init();
    }
    
    
}

void ButtonGroupPopupView::ComputeDividerDimension()
{
    if (dimension.w == 0 || dimension.h == 0)
    {
        dividerH = dividerW = 0;
        buttonH = buttonW = 0;
        return;
    }
    
    dividerH = dimension.h/(_row*dividerRatioW + _row+1);    // divider height = button height/2
    dividerW = dimension.w/(_column*dividerRatioH + _column+1);  // divider width = button width/4

    buttonH = dividerH*dividerRatioH;
    buttonW = dividerW*dividerRatioW;
    
    return;
}
