#include "ArmyReadyView.h"
#include "PictureView.h"

ArmyReadyView* ArmyReadyView::pInstance = NULL;

ArmyReadyView::ArmyReadyView(CCNode* node) :
		cancelButton(node, ResourceUri::armyReadyViewCancelButtonPictureName),
		armyIcons(true), soldierNumbers(true), armyIdList(false)
{

}

//##ModelId=526D27EA0381
void ArmyReadyView::AddSelectedArmy(Uint32 id)
{
}

//##ModelId=526D29390019
void ArmyReadyView::ClearSelectedArmy()
{
}

void ArmyReadyView::RemoveSelectedArmy(Uint32 id)
{

}
