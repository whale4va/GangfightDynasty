#ifndef TABVIEW_H_HEADER_INCLUDED_AD80B46E
#define TABVIEW_H_HEADER_INCLUDED_AD80B46E
#include "CommonButton.h"
#include "TextView.h"
#include "ViewFrame.h"
#include "PictureView.h"

using cocos2d::CCLayer;
using cocos2d::CCNode;
using cocos2d::CCTouch;
using cocos2d::CCSet;
using cocos2d::CCEvent;
using cocos2d::CCSprite;

//##ModelId=522B3FDC03DE
class TabView : public ViewFrame
{
public:
	TabView(CCNode* n) : ViewFrame(n), _title("Blank Title") {}
	TabView(CCNode* n, String title) : ViewFrame(n), _title(title){}

	virtual ~TabView()
	{
		Destory();	// Destroy cocos2d resources
	}

	inline String GetTitle() { return _title; }
	inline void SetTitle(String str) { _title = str; }

	void Display();
	void Dismiss();
	void Destory();

	// touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

  protected:
    //##ModelId=522B40460321
    String _title;

  private:
    TabView();
};


#endif /* TABVIEW_H_HEADER_INCLUDED_AD80B46E */
