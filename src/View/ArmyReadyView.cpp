#include "ArmyReadyView.h"
#include "PictureView.h"

ArmyReadyView* ArmyReadyView::pInstance = NULL;
Uint8 ArmyReadyView::widthProportion = 68;      // percentage
float ArmyReadyView::dividerProportion = 2.0;      // percentage in width. 12%
Uint8 ArmyReadyView::iconsOneRow = 5;           // number of icons in one row. 88%
float ArmyReadyView::maxWidth = 0.0;
float ArmyReadyView::iconSize = 0.0;
float ArmyReadyView::dividerSize = 0.0;
Uint8 ArmyReadyView::iconPictureProportion = 75;    // 75% icon in height.

ArmyReadyView::ArmyReadyView(CCNode* node) :
        ViewFrame(node), bgPicture(node, ResourceUri::armyReadyBackgroundPictureName),
		cancelButton(node, ResourceUri::armyReadyViewCancelButtonPictureName),
		armyIcons(true), soldierNumbers(true), armyIdList(false)
{
    cancelButton.SetId(BTN_CANCEL);
    cancelButton.SetParentView(this);
}

//##ModelId=526D27EA0381
void ArmyReadyView::AddSelectedArmy(Uint32 id)
{
    Army army = Army::GetArmyById(id);
    armyIdList.Add(id);
    
    PictureView* pPic = NULL;
    switch (army.GetWeaponType())
    {
        case Weapon_Arrow:
            pPic = new PictureView(_node,
                                   ResourceUri::WeaponTypePictureName[Weapon_Arrow]);
            break;
        case Weapon_Horse:
            pPic = new PictureView(_node,
                                   ResourceUri::WeaponTypePictureName[Weapon_Horse]);
            break;
        case Weapon_Spear:
            pPic = new PictureView(_node,
                                   ResourceUri::WeaponTypePictureName[Weapon_Spear]);
            break;
        case Weapon_Sword:
            pPic = new PictureView(_node,
                                   ResourceUri::WeaponTypePictureName[Weapon_Sword]);
            break;
        default:
            THROW(Invalid_Weapon_Type);
            break;
    }
    
    TextView* pNum = new TextView(_node, army.GetSoldier(), true);
    
    // update picture and text view coordinates
    CalculateIconCoordinates(armyIdList.GetLength()-1,
                             pPic, pNum);
    
    armyIcons.Add(pPic);
    soldierNumbers.Add(pNum);
    pPic->Display();
    pNum->Display();
    
    // update background picture coordinates.
    Dimension dim;
    dim.h = (armyIdList.GetLength()/iconsOneRow + 1)*
            (iconSize + dividerSize) + dividerSize;
    dim.w = armyIdList.GetLength() >= iconsOneRow ?
            iconsOneRow*(iconSize + dividerSize) + dividerSize :
            armyIdList.GetLength()*(iconSize + dividerSize) + dividerSize;
    bgPicture.SetDimension(dim);
    bgPicture.Dismiss();
    bgPicture.Display();
    
    CCSize winSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    Point pt;
    pt.z = position.z;
    pt.x = winSize.width - dim.w/2;
    pt.y = winSize.height - iconSize - dim.h/2;
    bgPicture.SetPoint(pt);
    
    // update cancel button coordinates.
    pt.x = winSize.width - dim.w - iconSize/4;
    pt.y = winSize.height - iconSize - iconSize/4;
    cancelButton.SetPoint(pt);
    if (!cancelButton.dimension.IsValid()) {
        dim.h = iconSize/2;
        dim.w = iconSize/2;
        cancelButton.SetDimension(dim);
    }
    cancelButton.Dismiss();
    cancelButton.Display();
}

// 计算军队图标的坐标，根据军队在列表中的索引
void ArmyReadyView::CalculateIconCoordinates(Uint32 index,
                                          ViewFrame* pPic, ViewFrame* pNum)
{
    Point pt;
    pt.z = position.z + 1;
    CCSize winSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    pt.x = winSize.width - iconSize/2 - dividerSize;
    pt.y = winSize.height - 1.5*iconSize - dividerSize;
    
    // switch to icon position of specific index
    int row = index/iconsOneRow;
    int column = index % iconsOneRow;
    pt.x -= (column)*(iconSize+dividerSize);
    pt.y -= (row)*(iconSize+dividerSize);
    
    // change to picture position and number text position
    pt.y += iconSize/2;
    pt.y -= (iconSize*iconPictureProportion/200);
    pPic->SetPoint(pt);
    Dimension dim;
    dim.w = iconSize;
    dim.h = iconSize*iconPictureProportion/100;
    pPic->SetDimension(dim);
    
    dim.h = iconSize*(100-iconPictureProportion)/100;
    pt.y -= iconSize*iconPictureProportion/200;
    pt.y -= iconSize*(100-iconPictureProportion)/200;
    pNum->SetDimension(dim);
    pNum->SetPoint(pt);
    
}

//##ModelId=526D29390019
void ArmyReadyView::ClearSelectedArmy()
{
    this->Destory();
}

void ArmyReadyView::RemoveSelectedArmy(Uint32 id)
{
    int index = armyIdList.Find(id);
    int last = armyIdList.GetLength()-1;
    if (index != last)
    {
        // exchange coordinates and ids
        armyIcons[last]->SetPoint(armyIcons[index]->position);
        soldierNumbers[last]->SetPoint(soldierNumbers[index]->position);
        armyIcons[last]->SetDimension(armyIcons[index]->dimension);
        soldierNumbers[last]->SetDimension(soldierNumbers[index]->dimension);
        
        // dismiss at last
        armyIcons[last]->Dismiss();
        soldierNumbers[last]->Dismiss();
        
        // dismiss & destory selected army at index
        armyIcons[index]->Destory();
        soldierNumbers[index]->Destory();
        delete armyIcons[index];
        delete soldierNumbers[index];
        
        // put the list last to specific index
        armyIcons[index] = armyIcons[last];
        soldierNumbers[index] = soldierNumbers[last];
        armyIdList[index] = armyIdList[last];
        
        // redraw last at index
        armyIcons[index]->Display();
        soldierNumbers[index]->Display();
        
        // remove from list
        armyIcons.Remove(last);
        soldierNumbers.Remove(last);
        armyIdList.Remove(last);
    }
    else
    {
        // dismiss at last
        armyIcons[index]->Destory();
        soldierNumbers[index]->Destory();
        delete armyIcons[index];
        delete soldierNumbers[index];
        
        // remove from list at last
        armyIcons.Remove(index);
        soldierNumbers.Remove(index);
        armyIdList.Remove(index);
    }
}


void ArmyReadyView::Display()
{
    if (!bgPicture.dimension.IsValid())
        THROW(Invalid_Dimension);

    bgPicture.Display();
    
    if (!cancelButton.dimension.IsValid())
        THROW(Invalid_Dimension);
    
    cancelButton.Display();
    
    for (int i = 0; i < armyIcons.GetLength(); i++)
    {
        armyIcons[i]->Display();
    }
    
    for (int i = 0; i < soldierNumbers.GetLength(); i++)
    {
        soldierNumbers[i]->Display();
    }
}

void ArmyReadyView::Dismiss()
{
    cancelButton.Dismiss();
    bgPicture.Dismiss();
    for (int i = 0; i < armyIcons.GetLength(); i++)
    {
        armyIcons[i]->Dismiss();
        soldierNumbers[i]->Dismiss();
    }
}

void ArmyReadyView::Destory()
{
    this->Dismiss();
    for (int i = 0; i < armyIcons.GetLength(); i++)
    {
        armyIcons[i]->Destory();
        delete armyIcons[i];
        soldierNumbers[i]->Destory();
        delete soldierNumbers[i];
    }
    cancelButton.Destory();
    bgPicture.Destory();
}
