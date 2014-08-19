#include "WarningView.h"

int WarningViewTab::borderSize = 3;     //边框大小

void WarningViewTab::Display()
{
    if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
		return;		// dimension is not set yet.
   
    Dimension elementDimension = dimension;
    elementDimension.w -= 2*borderSize;
    elementDimension.h -= 2*borderSize;
    elementDimension.h = elementDimension.h*2/3;
    warningText.SetDimension(elementDimension);
    
    Point elementPoint = position;
    elementPoint.y += dimension.h/2 - borderSize - (dimension.h-2*borderSize)/3;
    elementPoint.z += 1;
    warningText.SetPoint(elementPoint);
    
    elementDimension.w = (dimension.w-2*borderSize)/3;
    if (elementDimension.w > BUTTON_LENGTH_LIMIT)
        elementDimension.w = BUTTON_LENGTH_LIMIT;
    elementDimension.h = (dimension.h - 2*borderSize)/3;
    if (elementDimension.h > BUTTON_HEIGHT_LIMIT)
        elementDimension.h = BUTTON_HEIGHT_LIMIT;
    okButton.SetDimension(elementDimension);
    
    elementPoint.y = position.y + dimension.h/2 - borderSize;
    elementPoint.y -= (dimension.h-2*borderSize)*2/3;
    elementPoint.y -= elementDimension.h/2;
    okButton.SetPoint(elementPoint);
    okButton.SetPoint(elementPoint);
    
    warningText.Display();
    okButton.Display();
    
}
