#include "ViewEventResponder.h"

//##ModelId=523F025402A1
bool ViewEventResponder::OnListItemSelected(int rowIndex)
{
    return false;
}

bool ViewEventResponder::OnListItemUnselected(int rowIndex)
{
    return false;
}

//##ModelId=523F0258027F
bool ViewEventResponder::OnButton()
{
    return false;
}

//##ModelId=523F025C0237
bool ViewEventResponder::OnTap()
{
    return false;
}

//##ModelId=523F040402A4
bool ViewEventResponder::OnSortListByColumn(int columnIndex)
{
    return false;
}

//##ModelId=523F10C500AC
bool ViewEventResponder::OnTapMove()
{
    return false;
}

//##ModelId=5240BDA70041
bool ViewEventResponder::OnSlipSpecialButton()
{
    return false;
}

//##ModelId=5240BEA10063
bool ViewEventResponder::OnListSpecialButton()
{
    return false;
}

//##ModelId=5240C9B40082
bool ViewEventResponder::OnFinish()
{
    return false;
}

//##ModelId=52668FCB03B8
bool ViewEventResponder::OnTabTitleTap()
{
    return false;
}

bool ViewEventResponder::ccTouchBegan(CCTouch* pTouch, cocos2d::CCEvent *pEvent)
{
    return false;
}

void ViewEventResponder::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* pEvent)
{
    return;
}

void ViewEventResponder::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    return;
}

void ViewEventResponder::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
    return;
}
