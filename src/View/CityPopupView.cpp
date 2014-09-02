#include "CityPopupView.h"

Uint32 CityPopupViewTab::fontColor = 0xFFFF00FF;
Uint8 CityPopupViewTab::dividerHeightProportion = 3;
Uint8 CityPopupViewTab::rowHeightProportion = 13;

void CityPopupViewTab::Display()
{
    if (!dimension.IsValid())
        THROW(Invalid_Dimension);
    
    float dividerHeight = dimension.h * dividerHeightProportion/100;
    float rowHeight = dimension.h * rowHeightProportion/100;
    
    if (!officerStrategyView.dimension.IsValid())
    {   // haven't initial dimension yet.
        float rowWidth = dimension.w - dividerHeight*2;
        
        Dimension dim = dimension;
        dim.w = rowWidth;
        dim.h = rowHeight;
        
        officerStrategyView.SetDimension(dim);
        agricultureView.SetDimension(dim);
        businessView.SetDimension(dim);
        securityView.SetDimension(dim);
        soldierSwordView.SetDimension(dim);
        spearHorseView.SetDimension(dim);
    }
    
    
    // set every subvies' point
    Point pt = position;
    pt.z += 1.0;
    pt.y += dimension.h/2;
    
    pt.y -= (rowHeight/2 + dividerHeight);
    officerStrategyView.SetPoint(pt);
    pt.y -= rowHeight/2;
    
    pt.y -= (rowHeight/2 + dividerHeight);
    agricultureView.SetPoint(pt);
    pt.y -= rowHeight/2;
   
    pt.y -= (rowHeight/2 + dividerHeight);
    businessView.SetPoint(pt);
    pt.y -= rowHeight/2;
    
    pt.y -= (rowHeight/2 + dividerHeight);
    securityView.SetPoint(pt);
    pt.y -= rowHeight/2;
    
    pt.y -= (rowHeight/2 + dividerHeight);
    soldierSwordView.SetPoint(pt);
    pt.y -= rowHeight/2;
    
    pt.y -= (rowHeight/2 + dividerHeight);
    spearHorseView.SetPoint(pt);
    pt.y -= rowHeight/2;
    
    officerStrategyView.Display();
    agricultureView.Display();
    businessView.Display();
    securityView.Display();
    soldierSwordView.Display();
    spearHorseView.Display();

}

void CityPopupViewTab::Dismiss()
{
    officerStrategyView.Dismiss();
    agricultureView.Dismiss();
    businessView.Dismiss();
    securityView.Dismiss();
    soldierSwordView.Dismiss();
    spearHorseView.Dismiss();
}

void CityPopupViewTab::Destory()
{
    officerStrategyView.Destory();
    agricultureView.Destory();
    businessView.Destory();
    securityView.Destory();
    soldierSwordView.Destory();
    spearHorseView.Destory();
}

