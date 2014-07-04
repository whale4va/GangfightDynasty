#ifndef VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7
#define VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7

#include "../Common/types.h"
#include "../Common/String.h"
#include "../Common/List.h"

using cocos2d::CCNode;
using cocos2d::CCLayer;
using cocos2d::CCTouch;
using cocos2d::CCEvent;

//##ModelId=523F011C0076
class ViewEventResponder
{
private:
    ViewEventResponder();
    
  public:
    //##ModelId=523F025402A1
    virtual bool OnListItemSelected();

    //##ModelId=523F0258027F
    virtual bool OnButton();

    //##ModelId=523F025C0237
    virtual bool OnTap();

    //##ModelId=523F040402A4
    virtual bool OnSortListByColumn();

    //##ModelId=523F10C500AC
    virtual bool OnTapMove();

    //##ModelId=5240BDA70041
    virtual bool OnSlipSpecialButton();

    //##ModelId=5240BEA10063
    virtual bool OnListSpecialButton();

    //##ModelId=5240C9B40082
    virtual bool OnFinish();

    /** @brief handle on event that sub tab view title was tapped/clicked. Or
    tap move was performed to start change tab view showing. */
    //##ModelId=52668FCB03B8
    virtual bool OnTabTitleTap();
    
    // constructors
    ViewEventResponder(cocos2d::CCNode* n) : _node(n), _senderId(GAME_INVALID_ID) {}
    ViewEventResponder(const ViewEventResponder& orig):_senderId(orig._senderId),
        _node(orig._node), _touchStartPt(orig._touchStartPt), _touchEndPt(orig._touchEndPt),
        _touchCurPt(orig._touchCurPt) {}
    
    virtual ~ViewEventResponder() {}
    // assignment
    ViewEventResponder& operator=(const ViewEventResponder& orig)
    {
        if (this != &orig)
        {
            _senderId = orig._senderId;
            _node = orig._node;
            _touchCurPt = orig._touchCurPt;
            _touchStartPt = orig._touchStartPt;
            _touchEndPt = orig._touchEndPt;
        }
        return *this;
    }
    
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
    
    // Introduce CCLayer touch event handlers, easy to extend.
    // touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    inline void SetCCNode(cocos2d::CCNode* node)
    {
        _node = node;
    }
    
    inline cocos2d::CCNode* GetCCNode()
    {
        return _node;
    }

    /**
     * @brief Determine whether this viewFrame contain a point
     * @param pt[in] the point need to be judged
     * @param dim[in] the dimension information of area
     * @parm cp[in] central point of area
     * @return bool true if the area contain this point else false.
     */
    inline bool AreaContainCCPoint(cocos2d::CCPoint pt, Point cp, Dimension dim) throw(ExceptionId)
    {
    	if (dim.w < FLOAT_MINOR_LIMIT || dim.h < FLOAT_MINOR_LIMIT)
    		throw (Invalid_Dimension);
    	if (pt.x >= cp.x - dim.w/2 &&
    			pt.x <= cp.x + dim.w/2 &&
    			pt.y >= cp.y - dim.h/2 &&
    			pt.y <= cp.y + dim.h/2)
    		return true;
    	else
    		return false;
    }

    cocos2d::CCPoint _touchStartPt, _touchEndPt, _touchCurPt;
};


#endif /* VIEWEVENTRESPONDER_H_HEADER_INCLUDED_AD80BBA7 */
