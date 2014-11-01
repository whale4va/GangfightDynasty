#ifndef ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11
#define ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11
#include "CommonButton.h"
#include "TextView.h"
#include "PictureView.h"

#include "../Model/Army.h"

using cocos2d::CCNode;
using cocos2d::CCLayerColor;
using cocos2d::CCSize;

/** @brief remember & display selected army from same city, if new added army
comes from other city, then previous selected armies are cleared first.

ArmyReadyView should be a singleton mode

 */
//##ModelId=522C6D9D014D
class ArmyReadyView : public ViewFrame
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
          
          // initial this object position and dimension
          CCSize winSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
          maxWidth = winSize.width * widthProportion / 100;
          dividerSize = maxWidth * dividerProportion / 100;
          iconSize = (maxWidth - (iconsOneRow+1)*dividerSize)/iconsOneRow;
          
          Dimension dim;
          dim.h = iconSize + 2*dividerSize;
          dim.w = iconSize + 2*dividerSize;
          pInstance->SetDimension(dim);
          
          Point pt;
          pt.z = 2.0;
          pt.x = winSize.width - maxWidth/2;
          pt.y = winSize.height - 1.5*dim.h;
          pInstance->SetPoint(pt);
      }
      return pInstance;
    }
    
    static void FreeArmyReadyView()
    {
        if (NULL != pInstance)
        {
            pInstance->Destory();
            delete pInstance;
            pInstance = NULL;
        }
    }
    
    virtual void Display();
    virtual void Dismiss();
    virtual void Destory();
    
    inline virtual bool OnButton()
    {
        CCLOG("ArmyReadyView cancel button clicked on %d(0x%X).\n", _senderId, _senderId);
        bool ret = false;
        switch (_senderId)
        {
        case BTN_CANCEL:
            this->ClearSelectedArmy();
            ret = true;
            break;
        default:
            break;
        }
        return ret;
    }

  private:
    
    void CalculateIconCoordinates(Uint32 index,
                               ViewFrame* pPic, ViewFrame* pNum);

    ArmyReadyView();
    ArmyReadyView(CCNode* node);

    //##ModelId=522C6E2300BD
    CommonButton cancelButton;
    //##ModelId=522C6E860080
    List<PictureView*> armyIcons;
    //##ModelId=522C6EA203CD
    List<Uint32> armyIdList;
    
    // back ground picture
    PictureView bgPicture;

    // number text view to show soldier number of army.
    List<TextView*> soldierNumbers;
    // army ready view instance pointer
    static ArmyReadyView* pInstance;
    
    
    // showing parameters
    static Uint8 widthProportion;       // army ready view width proportion
    static float dividerProportion;     // divider width and height in percentage.
    static Uint8 iconsOneRow;          // how many icons in one row.
    static float maxWidth;             // maximum width of dimension.
    static float iconSize;             // icon width
    static float dividerSize;           // divider size(width/height)
    static Uint8 iconPictureProportion; // icon picture height proportion.
};



#endif /* ARMYREADYVIEW_H_HEADER_INCLUDED_AD808A11 */
