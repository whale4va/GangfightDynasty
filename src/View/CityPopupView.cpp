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
    
    
    // set every subviews' point
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


/////////////////////////////////////////
// CityPopupView
/////////////////////////////////////////
Uint8 CityPopupView::armyListRowHeight = 16;

void CityPopupView::SetDimension(Dimension dim)
{
    if (!dim.IsValid()) {
        THROW(Invalid_Dimension);
    }
    
    //// add city popup tab
    CityPopupViewTab* pCityTab = new CityPopupViewTab(
        _node, pCity->get_name(), pCity);
    this->AddTab(pCityTab);
    
    //// add army list tab
    ListViewTab* pArmyTab = new ListViewTab(_node, "部队列表", 4, true,
                                            false, armyListRowHeight, 0);
    this->AddTab(pArmyTab);
    // add title views.
    TextView* pTitleText = new TextView(_node, "名称", true);
    pArmyTab->AddTitleView(pTitleText);
    pTitleText = new TextView(_node, "士兵", true);
    pArmyTab->AddTitleView(pTitleText);
    pTitleText = new TextView(_node, "兵种", true);
    pArmyTab->AddTitleView(pTitleText);
//pTitleText = new TextView(_node, "攻击力", true);
//pArmyTab->AddTitleView(pTitleText);
    
    // add army list content views.
    List<Uint32> armyIds = pCity->get_armyIdList();
    List<Uint32> armySortOrder;
    for (int i = 0; i < armyIds.GetLength(); ++i)
    {
        Army army = Army::GetArmyById(armyIds[i]);
        TextView* pRowText = new TextView(_node, army.GetName(), true);
        pArmyTab->AddContentView(pRowText);
        pRowText = new TextView(_node, army.GetSoldier(), true);
        pArmyTab->AddContentView(pRowText);
        PictureView* pRowPic = new PictureView(_node, ResourceUri::WeaponTypePictureName[army.GetWeaponType()]);
        pArmyTab->AddContentView(pRowPic);
        
        armySortOrder.Add(i);
    }
    pArmyTab->SetSortOrder(armySortOrder);

}

bool CityPopupView::OnButton()
{
    CCLOG("CityPopupView button clicked on %d(0x%X).\n", _senderId, _senderId);
	bool ret = false;
	switch (_senderId)
	{
	case BTN_ENTER_CITY:
		Dismiss();
        // 切换场景，进入城市视图
        
        ret = true;
		break;
	default:
		break;
	}
    return false;
}

bool CityPopupView::OnListItemSelected(int rowIndex)
{//CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
	Uint32 armyId = pCity->get_armyIdList()[rowIndex];
	ArmyReadyView::GetArmyReadyView(_node)->AddSelectedArmy(armyId);
    return true;
}

bool CityPopupView::OnListItemUnselected(int rowIndex)
{
 	Uint32 armyId = pCity->get_armyIdList()[rowIndex];
	ArmyReadyView::GetArmyReadyView(_node)->RemoveSelectedArmy(armyId);
    return true;
}
