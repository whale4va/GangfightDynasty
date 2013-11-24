#ifndef VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7
#define VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7

#include "../Common/types.h"
#include "../Common/String.h"
#include "../Common/List.h"

using cocos2d::CCNode;
using cocos2d::CCLayer;

//##ModelId=523F011C0076
class ViewEventResponder
{
private:
    ViewEventResponder();
    
  public:
    //##ModelId=523F025402A1
    bool OnListItemSelected();

    //##ModelId=523F0258027F
    bool OnButton();

    //##ModelId=523F025C0237
    bool OnTap();

    //##ModelId=523F040402A4
    bool OnSortListByColumn();

    //##ModelId=523F10C500AC
    bool OnTapMove();

    //##ModelId=5240BDA70041
    bool OnSlipSpecialButton();

    //##ModelId=5240BEA10063
    bool OnListSpecialButton();

    //##ModelId=5240C9B40082
    bool OnFinish();

    /** @brief handle on event that sub tab view title was tapped/clicked. Or
    tap move was performed to start change tab view showing. */
    //##ModelId=52668FCB03B8
    bool OnTabTitleTap();
    
    
    /**
     @brief id to indicate who is the event sender
     */
    Uint32 _senderId;
    inline void SetSenderId(Uint32 i) { _senderId = i; }
    
    
    /** @brief cocos2d-x context of cocos2d-x display environment */
    //CCContext context;
//    cocos2d::CCLayer* _layer;
//    ViewEventResponder(cocos2d::CCLayer* l) : _layer(l) {}
    cocos2d::CCNode* _node;     // parent node that this view frame need to be added to
    ViewEventResponder(cocos2d::CCNode* n) : _node(n), _senderId(GAME_INVALID_ID) {}
};


#endif /* VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7 */
