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
class TabView : public ViewFrame, public CCLayer
{
public:
	TabView(CCNode* n) : ViewFrame(n), _title(this, "TabView", true), _owner(NULL), _selectedIndex(0),
	_dismissButton(this, "tabview_dismiss_normal.png"), _tabList(true), _isOwner(false),
	_background(this, tabviewBackground), _titleBGSprite(NULL) {}
	TabView(CCNode* n, String title) : ViewFrame(n), _title(this, title, true), _owner(NULL), _selectedIndex(0),
			_dismissButton(this, "tabview_dismiss_normal.png"), _tabList(true), _isOwner(true),
			_background(this, tabviewBackground), _titleBGSprite(NULL){}
	TabView(CCNode* n, String title, bool own) : ViewFrame(n), _title(this, title, true),
			_dismissButton(this, "tabview_dismiss_normal.png"), _tabList(true), _isOwner(own),
			_owner(NULL), _selectedIndex(0), _background(this, tabviewBackground), _titleBGSprite(NULL)
	{
		if (_isOwner)
		{
			_tabList.Add(this);	// the first tab view defined as the owner.
			_owner = this;
		}
	}

	inline void AddTab(TabView* pTab) throw (ExceptionId)
	{
		assert(pTab && pTab != this);
		assert(pTab->_isOwner == false);
		if (_isOwner)
		{
			_tabList.Add(pTab);
			pTab->_owner = this;
		}
		else
			throw (Method_Not_Support);
	}

	~TabView()
	{
		Destory();	// Destroy cocos2d resources
		if (_isOwner)
		{
			if (!_tabList.Empty())
				_tabList.Release();
		}
	}

	inline Dimension GetTitleDimension()
	{
		Dimension titleDimension;
		titleDimension.h = tabviewTitleHeight;
		titleDimension.w = titleDimension.h*_title.GetContentLength();
		return titleDimension;
	}

	inline Point GetTitlePoint(TabView* pTab) throw(ExceptionId)
	{
		Point pos = position;
		if (_isOwner)
		{
			if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
				throw (Invalid_Dimension);

			pos.x = position.x - dimension.w/2;
			pos.y = position.y + dimension.h/2;
			Dimension titleDimension;
			bool found = false;
			for (int i = 0; i < _tabList.GetLength(); i++)
			{
				titleDimension = _tabList[i]->GetTitleDimension();
				if (pTab != _tabList[i])
					pos.x += titleDimension.w;
				else
				{
					found = true;
					pos.x += titleDimension.w/2;
					break;
				}
			}

			if (found)
				return pos;
			else
				throw (Tab_Not_In_Group);
		}
		else
			throw (Method_Not_Support);

		return pos;
	}

	inline bool GetSelectedOrNot(TabView* pTab) throw(ExceptionId)
	{
		assert(pTab);
		if (_isOwner)
			return (_tabList[_selectedIndex] == pTab);
		else
			throw (Method_Not_Support);
	}

	inline TabView* GetOwner() { return _owner; }
	inline void SetOwner(TabView* pTab) { _owner = pTab; }

	void Display();
	void Dismiss();
	void Destory();

	virtual bool init();
	virtual void onExit();

	// touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// constant resource name
	static const char* tabviewBackground;
	static const char* tabviewTitlePictureNormal;
	static const char* tabviewTitlePictureSelected;
	static const float tabviewTitleHeight;
//	static const float tabviewTitleWidth;	// width = height * title.length

  protected:
    //##ModelId=522B40460321
    TextView _title;
    //##ModelId=522B405602FE
    CommonButton _dismissButton;


    // indicate the tab view owning other tab views or not
    bool _isOwner;
    // pointer to the owner tab view of this tab
    TabView* _owner;

    // cocos2d-x resources. Title text view & dismiss button & background picture & title background picture.
    PictureView _background;
    CCSprite* _titleBGSprite;
	// resource of sprint frames used for every tab view as title background.
	static cocos2d::CCSpriteFrame *titleNormalFrame, *titleSelectedFrame;

  private:
    TabView();
};


#endif /* TABVIEW_H_HEADER_INCLUDED_AD80B46E */
