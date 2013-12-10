#include "TabView.h"

const char* TabView::tabviewBackground = "Backgrounds/TabViewBackground.png";
const char* TabView::tabviewTitlePictureNormal = "Backgrounds/TabViewTitleNormal.png";
const char* TabView::tabviewTitlePictureSelected = "Backgrounds/TabViewTitleSelected.png";
const float TabView::tabviewTitleHeight = 24.0;
cocos2d::CCSpriteFrame* TabView::titleNormalFrame = NULL;
cocos2d::CCSpriteFrame* TabView::titleSelectedFrame = NULL;

void TabView::Display()
{
	if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
		return;		// dimension is not set yet.
	if (_title.GetContentLength() == 0)
		return;		// no title defined.

	if (this->getParent() == NULL)
		_node->addChild(this, (int)position.z);

	if (_isOwner)
	{
		_background.SetDimension(dimension);
		_background.SetPoint(position);
		_background.Display();

		_dismissButton.SetDimension(mkDimension(tabviewTitleHeight, tabviewTitleHeight));
		Point dismissPosition = position;
		dismissPosition.x = position.x + dimension.w/2 - tabviewTitleHeight/2;
		dismissPosition.y = position.y + dimension.h/2 + tabviewTitleHeight/2;
		_dismissButton.SetPoint(dismissPosition);
		_dismissButton.Display();
	}

	// title text view
	assert(_owner);
	Dimension titleDimension = _owner->GetTitleDimension();
	_title.SetSize((Uint32)tabviewTitleHeight);	// used as scale
	Point titlePosition = _owner->GetTitlePoint(this);
	titlePosition.z += 1.0;
	_title.SetDimension(titleDimension);
	_title.SetPoint(titlePosition);
	_title.Display();

	// title background picture
	if (_titleBGSprite == NULL)
	{
		_titleBGSprite = new CCSprite;
	}

	/**
	 * Display this tab view specific content, should be put in sub-classes.
	 */

	if (_isOwner)
	{
		// enumerate all owned tab views and display them.
		if (_tabList.GetLength() > 1)
		{
			for (int i = 1; i < _tabList.GetLength(); i++)
			{
				_tabList[i]->SetDimension(dimension);
				_tabList[i]->SetPoint(position);
				_tabList[i]->Display();
			}
		}
		this->setTouchMode(cocos2d::kCCTouchesOneByOne);	// targeted.
		this->setTouchEnabled(true);
	}
}

void TabView::Dismiss()
{
	if (_isOwner)
	{
		this->setTouchEnabled(false);
		_background.Dismiss();
		_dismissButton.Dismiss();

		_title.Dismiss();
	}


	/**
	 * Dismiss this tab view specific content, should be put in sub-classes.
	 */
}

void TabView::Destory()
{
	Dismiss();

	if (_isOwner)
	{
		_background.Destory();
		_dismissButton.Destory();
	}

	_title.Destory();
}

bool TabView::init()
{
	if (!CCLayer::init())
		return false;

	return true;
}

void TabView::onExit()
{
}
