#include "TabGroupView.h"

const char* TabGroupView::tabviewBackground = "Backgrounds/TabViewBackground.png";
const char* TabGroupView::tabviewTitlePictureNormal = "TabViewTitleNormal.png";
const char* TabGroupView::tabviewTitlePictureSelected = "TabViewTitleSelected.png";
const float TabGroupView::tabviewTitleHeight = 24.0;

void TabGroupView::Display()
{
	if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
		return;		// dimension is not set yet.

	if (subview.Empty())
		return;		// no tab view added yet.

	_background.SetDimension(mkDimension(dimension.w, dimension.h-tabviewTitleHeight));
	_background.SetPoint(mkPoint(position.x, position.y-tabviewTitleHeight/2, position.z));
	_background.Display();

	_dismissButton.SetDimension(mkDimension(tabviewTitleHeight, tabviewTitleHeight));
	Point dismissPosition = position;
	dismissPosition.x = position.x + dimension.w/2 - tabviewTitleHeight/2;
	dismissPosition.y = position.y + dimension.h/2 - tabviewTitleHeight/2;
	_dismissButton.SetPoint(dismissPosition);
	_dismissButton.Display();

	// title background picture
	if (_titleSpriteList.Empty())
	{
        if (!CCSpriteFrameLoader::loaded)
        	CCSpriteFrameLoader::Load();

        for (int i = 0; i < subview.GetLength(); i++)
        {
        	// title back ground
        	CCSprite* pSprite = new CCSprite();
        	assert(pSprite);
        	if (i == _selectedIndex)
        		pSprite->initWithSpriteFrameName(tabviewTitlePictureSelected);
        	else
        		pSprite->initWithSpriteFrameName(tabviewTitlePictureNormal);
        	_titleSpriteList.Add(pSprite);

        	// title text
        	TextView* pText = new TextView(this, (const char*)GetTitle(i), true);
        	_titleList.Add(pText);
        }
	}

	// normally display
	for (int i = 0; i < subview.GetLength(); i++)
	{
		// title back ground
		CCSprite* pSprite = _titleSpriteList[i];
		Point titlePoint = GetTitlePoint(i);
    	pSprite->setPosition(ToCCPoint(titlePoint));
        cocos2d::CCSize picSize = pSprite->getContentSize();
        Dimension titleDimension = GetTitleDimension(i);
        float scaleX = (float)titleDimension.w/picSize.width;
        float scaleY = (float)titleDimension.h/picSize.height;
        pSprite->setScaleX(scaleX);
        pSprite->setScaleY(scaleY);
        if (pSprite->getParent() == NULL)
        	this->addChild(pSprite, position.z);

        // title text
        titlePoint.z += 1.0;	// increase z order for text label
        TextView* pText = _titleList[i];
        pText->SetDimension(titleDimension);
        pText->SetPoint(titlePoint);
        pText->SetSize((Uint32)tabviewTitleHeight-3);	// font size -3 than title height for beautiful
        pText->Display();
	}

	// enumerate all owned tab views and display them.
	if (subview.GetLength() > 1)
	{
		for (int i = 0; i < subview.GetLength(); i++)
			subview[i]->Display();
	}

	if (this->getParent() == NULL)
	{
		_node->addChild(this, position.z);
		this->setTouchMode(cocos2d::kCCTouchesOneByOne);	// targeted.
		this->setTouchEnabled(true);
	}
}

void TabGroupView::Dismiss()
{
	if (this->getParent())
	{
		this->setTouchEnabled(false);
		_node->removeChild(this);
	}
	_background.Dismiss();
	_dismissButton.Dismiss();

	assert(_titleSpriteList.GetLength() == _titleList.GetLength());
	for (int i = 0; i < _titleSpriteList.GetLength(); i++)
	{
		// title dismiss
		_titleList[i]->Dismiss();
		// title background dismiss
		this->removeChild(_titleSpriteList[i]);
	}

	for (int i = 0; i < subview.GetLength(); i++)
		subview[i]->Dismiss();
}

void TabGroupView::Destory()
{
	Dismiss();

	_background.Destory();
	_dismissButton.Destory();

	for (int i = 0; i < subview.GetLength(); i++)
	{
		subview[i]->Destory();
	}

	_titleList.Release();
	_titleSpriteList.Release();
}

bool TabGroupView::init()
{
	if (!CCLayer::init())
		return false;

	return true;
}

void TabGroupView::onExit()
{
}

/**
 * Touch event handler
 */
bool TabGroupView::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	_touchStartPt = pTouch->getLocation();
	if (AreaContainCCPoint(_touchStartPt, position, dimension))
		return true;
	else
		return false;
}

void TabGroupView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TabGroupView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	_touchEndPt = pTouch->getLocation();
	if (_touchEndPt.y >= position.y + dimension.h/2 - tabviewTitleHeight &&
			_touchEndPt.y <= position.y + dimension.h/2)
	{	// touched at title row
		int index = -1;
		for (int i = 0; i < subview.GetLength(); i++)
		{
			if (AreaContainCCPoint(_touchEndPt, GetTitlePoint(i), GetTitleDimension(i)))
			{
				index = i;
				break;
			}
		}
		if (index == -1 || index == _selectedIndex)
		{
			return;		// not touch on title item. OR. touch on already selected title.
		}
		else
		{	// switch selected tab view
			((TabView*)subview[_selectedIndex])->Dismiss();
			_titleSpriteList[_selectedIndex]->setDisplayFrame(
					cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->
					                                      spriteFrameByName(tabviewTitlePictureNormal));
			_selectedIndex = index;
			_titleSpriteList[_selectedIndex]->setDisplayFrame(
					cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->
					                                      spriteFrameByName(tabviewTitlePictureSelected));
			subview[_selectedIndex]->Display();
		}
	}
	else
	{	// touched at tab view area, pass to sub tab view.
		((TabView*)subview[_selectedIndex])->ccTouchEnded(pTouch, pEvent);
	}
}

void TabGroupView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

bool TabGroupView::OnButton()
{
	CCLOG("TabGroupView button clicked on %d(0x%X).\n", _senderId, _senderId);
	bool ret = false;
	switch (_senderId)
	{
	case BTN_TAB_GROUP_DISMISS:
		Dismiss();
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

