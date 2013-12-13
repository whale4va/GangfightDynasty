#include "TabView.h"

void TabView::Display()
{
	if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
		return;		// dimension is not set yet.
	if (_title.empty())
		return;		// no title defined.

	/**
	 * Display this tab view specific content, should be put in sub-classes.
	 */
}

void TabView::Dismiss()
{
	/**
	 * Dismiss this tab view specific content, should be put in sub-classes.
	 */
}

void TabView::Destory()
{
	Dismiss();
}

bool TabView::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{

	return true;
}

void TabView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TabView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TabView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}
