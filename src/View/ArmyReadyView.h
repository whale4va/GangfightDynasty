#ifndef ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11
#define ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11
#include "CommonButton.h"
class PictureView;

using cocos2d::CCNode;

/** @brief remember & display selected army from same city, if new added army
comes from other city, then previous selected armies are cleared first.

ArmyReadyView should be a singleton mode

 */
//##ModelId=522C6D9D014D
class ArmyReadyView
{
  public:
    /** @brief add selected army in army popup list view into army ready view,
    army small icon will be created internally.
    @param[in] id the id of the selected army. */
    //##ModelId=526D27EA0381
    void AddSelectedArmy(Uint32 id);

    /** @brief clear all selected armies in the army ready view in case user
    tapped 'dismiss/cancel' on the army ready view. */
    //##ModelId=526D29390019
    void ClearSelectedArmy();

    /**
     * @brief remove specific army from army ready view
     * @param id[IN] the id of army that is specified.
     */
    void RemoveSelectedArmy(Uint32 id);

    static ArmyReadyView* GetArmyReadyView(CCNode* node)
    {
      if (NULL == pInstance)
      {
    	  assert(NULL != node);
    	  pInstance = new ArmyReadyView(node);
      }
      return pInstance;
    }

  private:

    ArmyReadyView();
    ArmyReadyView(CCNode* node);

    //##ModelId=522C6E2300BD
    CommonButton cancelButton;
    //##ModelId=522C6E860080
    List<PictureView*> armyIcons;
    //##ModelId=522C6EA203CD
    List<Uint32> armyIdList;

    // number text view to show soldier number of army.
    List<TextView*> soldierNumbers;
    // army ready view instance pointer
    static ArmyReadyView* pInstance;
};



#endif /* ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11 */
