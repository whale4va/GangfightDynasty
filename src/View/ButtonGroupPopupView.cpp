#include "ButtonGroupPopupView.h"

Uint8 const ButtonGroupPopupView::dividerRatioW = 10;	// divider width = button width/8
Uint8 const ButtonGroupPopupView::dividerRatioH = 8;	// divider height = button height/4

//##ModelId=526930CE038D
void ButtonGroupPopupView::InitWithRowColumn(Uint32 row, Uint32 column)
{
    assert(row>0 && column>0);
    _row = row;
    _column = column;
    int addedNumber = _row*_column - buttonList.GetLength();
    for (int i = 0; i < addedNumber; i++)
    {
        buttonList.Add((CommonButton*)NULL);
    }
    addedNumber = _row - menuList.GetLength();
    for (int i = 0; i < _row; i++)
    	menuList.Add((CCMenu*)NULL);
}

//##ModelId=5269367A0307
void ButtonGroupPopupView::SetCommonButtonAt(CommonButton* button, Uint32 row, Uint32 column)
{
    assert(row>=0 && row<_row);
    assert(column>=0 && column<_column);
    
    if (buttonList[(row*_column+column)])
    	delete buttonList[(row*_column+column)];
    buttonList[(row*_column+column)] = button;
}

void ButtonGroupPopupView::AddCommonButtonAt(Uint32 row, Uint32 column, String picName, String framesName) throw (ExceptionId)
{
    assert(!picName.empty());
    assert(row < _row);
    assert(column < _column);
    if (framesName.empty())
    {
        framesName = "Buttons/buttons.plist";   // default sprite frame texture packer file
    }
    
    ComputeDividerDimension();
    if (buttonH == 0 || buttonW == 0)
    	THROW(Invalid_Dimension);

    CCMenu* pButtonContainer = menuList[row];
    if (pButtonContainer == NULL)
    {
        pButtonContainer = new cocos2d::CCMenu;
        assert(pButtonContainer);
        pButtonContainer->init();
        menuList[row] = pButtonContainer;
    }

    CommonButton* pButton = buttonList[row*_column + column];
    if (pButton)
    {
    	delete pButton;
    }
    pButton = new CommonButton(_node, picName);
    assert(pButton);
    pButton->SetFramesFileName(framesName);
    pButton->SetButtonContainer(pButtonContainer);
    pButton->SetDimension(mkDimension(buttonW, buttonH));
    buttonList[row*_column + column] = pButton;

    // compute this menu (button container) position
    // In Common Button, its position just become the menu position.
    Point pt = position;
    if (_row > 1)
    {
        pt.y += dimension.h/2;
        pt.y -= (row*(dividerH+buttonH)+(dividerH + buttonH/2));
    }
    pButton->SetPoint(pt);
}

void ButtonGroupPopupView::ComputeDividerDimension()
{
    if (dimension.w == 0 || dimension.h == 0)
    {
        dividerH = dividerW = 0;
        buttonH = buttonW = 0;
        return;
    }
    
    if (dividerH !=0 && dividerW != 0 && buttonH != 0 && buttonW != 0)
    	return;

    dividerH = dimension.h/(_row*dividerRatioH + _row+1);    // divider height = button height/2
    dividerW = dimension.w/(_column*dividerRatioW + _column+1);  // divider width = button width/4

    buttonH = dividerH*dividerRatioH;
    buttonW = dividerW*dividerRatioW;
    
//    CCLOG("w=%f, h=%f, dH=%f, dW=%f, bH=%f, bW=%f\n",
//    		dimension.w, dimension.h, dividerH, dividerW, buttonH, buttonW);
    return;
}

void ButtonGroupPopupView::Display()
{
	if (!resourceName.empty())
	{
		if (pBackGround == NULL)
		{
			pBackGround = new cocos2d::CCSprite;
			pBackGround->initWithFile(resourceName);
		}

		if (dimension.w != 0 && dimension.h != 0)
		{
			cocos2d::CCSize picSize = pBackGround->getContentSize();
			float scaleX = (float)dimension.w/picSize.width;
			float scaleY = (float)dimension.h/picSize.height;
			pBackGround->setScaleX(scaleX);
			pBackGround->setScaleY(scaleY);
		}

		pBackGround->setPosition(ToCCPoint(position));
		if (pBackGround->getParent() == NULL)
			_node->addChild(pBackGround, position.z-1);	// back one z order as background
	}

	for (int i = 0; i < buttonList.GetLength(); i++)
	{
		if (buttonList[i] != NULL)
			buttonList[i]->Display();
	}

	for (int i = 0; i < menuList.GetLength(); i++)
	{
		if (menuList[i] != NULL)
			menuList[i]->alignItemsHorizontallyWithPadding((float)dividerW);
	}
}

void ButtonGroupPopupView::Dismiss()
{
	for (int i = 0; i < menuList.GetLength(); i++)
	{
		if (menuList[i] != NULL && menuList[i]->getParent())
		{
			_node->removeChild(menuList[i]);
		}
	}
	if (pBackGround)
	{
		if (pBackGround->getParent())
		{
			_node->removeChild(pBackGround);
		}
	}
}

void ButtonGroupPopupView::Destory()
{
	Dismiss();
	for (int i = 0; i < buttonList.GetLength(); i++)
	{
		if (buttonList[i])
		{
			delete buttonList[i];
			buttonList[i] = NULL;
		}
	}

	for (int i = 0; i < menuList.GetLength(); i++)
	{
		if (menuList[i])
		{
			delete menuList[i];
			menuList[i] = NULL;
		}
	}

	if (pBackGround)
	{
		delete pBackGround;
		pBackGround = NULL;
	}
}

ButtonGroupPopupView::~ButtonGroupPopupView()
{
	Destory();
}
