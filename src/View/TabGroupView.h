#ifndef TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3
#define TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3
#include "TabView.h"

//##ModelId=522C76D50103
class TabGroupView : public ViewFrame, public CCLayerColor
{

public:

	TabGroupView(CCNode* n):ViewFrame(n), _selectedIndex(0), _titleList(true),
	_titleSpriteList(true), _dismissButton(this, "tabview_dismiss_normal.png"),
	_background(this, tabviewBackground), isModal(false)
	{
		_dismissButton._id = BTN_TAB_GROUP_DISMISS;
		_dismissButton.parentView = this;
		_background.parentView = this;
        initWithColor(ToColor4B(TabGroupView::tabviewLayerColor));
	}
    
    // can assign the dismiss button picture. for other usage.
 	TabGroupView(CCNode* n, String btnPicName, Uint32 btnId):
    ViewFrame(n), _selectedIndex(0),
    _titleList(true), _titleSpriteList(true),
    _dismissButton(this, btnPicName),
	_background(this, tabviewBackground), isModal(false)
	{
		_dismissButton._id = btnId;
		_dismissButton.parentView = this;
		_background.parentView = this;
        initWithColor(ToColor4B(TabGroupView::tabviewLayerColor));
	}
    
    inline void SetIsModal(bool modal) { isModal = modal; }

	virtual ~TabGroupView() {Destory();}

	virtual bool init();
	virtual void onExit();

	void Display();
	void Dismiss();
	void Destory();

	// touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual bool OnButton();

	inline void AddTab(TabView* pTab) throw (ExceptionId)
	{
		assert(pTab);
		if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
			throw (Invalid_Dimension);	// tab view group not set dimension yet.

		pTab->SetDimension(mkDimension(dimension.w, dimension.h-tabviewTitleHeight));
		pTab->SetPoint(mkPoint(position.x, position.y-tabviewTitleHeight/2, position.z));
		//_tabList.Add(pTab);
		subview.Add(pTab);
		pTab->SetParentView(this);
	}

	inline bool GetSelectedOrNot(TabView* pTab) throw(ExceptionId)
	{
		assert(pTab);
		//return (_tabList[_selectedIndex] == pTab);
		return (subview[_selectedIndex] == pTab);
	}

	inline Dimension GetTitleDimension(int index) throw(ExceptionId)
	{
		//String title = _tabList[index]->GetTitle();
		String title = ((TabView*)subview[index])->GetTitle();
		Dimension titleDimension;
		titleDimension.h = tabviewTitleHeight;
		titleDimension.w = titleDimension.h*title.CharNumber();
		if (subview.GetLength() < 4)
		{
			if (titleDimension.w < dimension.w/4)
				titleDimension.w = dimension.w/4; // 1 or 2 or 3 tab, title width = width /4.
		}
		return titleDimension;
	}

	inline Point GetTitlePoint(int index) throw(ExceptionId)
	{
		Point pos = position;
		if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
			throw (Invalid_Dimension);

		pos.x = position.x - dimension.w/2;
		pos.y = position.y + dimension.h/2 - tabviewTitleHeight/2;
		Dimension titleDimension;
		for (int i = 0; i < index; i++)
		{
			titleDimension = GetTitleDimension(i);
			pos.x += titleDimension.w;
		}
		titleDimension = GetTitleDimension(index);
		pos.x += titleDimension.w/2;

		return pos;
	}

	inline String GetTitle(int index) throw (ExceptionId)
	{
		TabView* pTab = (TabView*)subview[index];
		return pTab->GetTitle();
	}

	// constant resource name
	static const char* tabviewBackground;
	static const char* tabviewTitlePictureNormal;
	static const char* tabviewTitlePictureSelected;
	static const float tabviewTitleHeight;
    static const Uint32 tabviewLayerColor;
//	static const float tabviewTitleWidth;	// width = height * title.length

protected:
    //##ModelId=52668E51035F
    // tab view group tab views list
    //List<TabView*> _tabList;		// use ViewFrame::subview to substitude

    // indicate which tab is selected in the group
    int _selectedIndex;
    Uint64 ccEventProcessed;        //记录子tab是否需要处理事件，是则透传事件（对于模块对话框）使用
    bool isModal;                   //是否以模态的方式显示

    //##ModelId=522B405602FE
    CommonButton _dismissButton;
    List<TextView*> _titleList;
    List<CCSprite*> _titleSpriteList;

    // cocos2d-x resources. Title text view & dismiss button & background picture & title background picture.
    PictureView _background;

};



#endif /* TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3 */
