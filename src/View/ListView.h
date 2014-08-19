#ifndef LISTVIEW_H_HEADER_INCLUDED_AD808747
#define LISTVIEW_H_HEADER_INCLUDED_AD808747
#include "CommonButton.h"
#include "TabView.h"
#include "TabGroupView.h"
class ViewFrame;
using cocos2d::CCPoint;

//##ModelId=522B32CA02D2
class ListViewTab : public TabView
{
  public:
    //##ModelId=522B4CAE0320
    inline List<Uint32> RetrieveSelectedItem()
    {
        return selectedItem;
    }

    /** @brief set list view items order */
    //##ModelId=5265391B0223
    inline void SetSortOrder(List<Uint32> order)
    {
        sortOrder = order;
    }
    
    // set the percentages of every column width in total row width
    inline void SetColumnWidthPercentages(List<Uint8> percentages)
    {
        if (percentages.GetLength() != columnNumber)
            THROW(Invalid_ColumnWidthPercentage);
        Uint8 total = 0;
        for (int i = 0; i < percentages.GetLength(); i++)
            total += percentages[i];
        if (total != 100)
            THROW(Invalid_ColumnWidthPercentage);
        columnWidthPercentages = percentages;
    }
    
    /** Redraw list with specific index, used in sorting case. List actual
    model data is managed/owned by father view/object.
    @param[in] order index array for each element in content veiws array and
    indicate each element/row index. */
    //##ModelId=526529FC0399
    void RedrawWithOrder(List<Uint32> order);
    
    //##ModelId=526D103003E6
    void ShowSpecialButton();
    void HideSpecialButton();
    
    inline void AddSpecialButton(CommonButton* pButton)
    {
        assert(pButton != NULL);
        specialButtons.Add(pButton);
        this->subview.Add(pButton);
        pButton->SetParentView(this);
        pButton->SetCCNode(_node);
    }
    
    inline void AddContentView(ViewFrame* pView)
    {
        if (!dimension.IsValid())
            THROW(Invalid_Dimension);
        assert(pView != NULL);
        Dimension dim = dimension;
        dim.w /= columnNumber;
        dim.h = rowHeight;
        pView->SetDimension(dim);
        contentViews.Add(pView);
        this->subview.Add(pView);
        pView->SetParentView(this);
        pView->SetCCNode(_node);
    }
    
    inline void AddTitleView(ViewFrame* pView)
    {
        if (!dimension.IsValid())
            THROW(Invalid_Dimension);
        assert(pView != NULL);
        Dimension dim = dimension;
        dim.w /= columnNumber;
        dim.h = rowHeight;
        pView->SetDimension(dim);
        titleViews.Add(pView);
        this->subview.Add(pView);
        pView->SetParentView(this);
        pView->SetCCNode(_node);
    }
    
    //// construstors
    ListViewTab(CCNode* node, String title, Uint8 colNumber, bool multiSelect,
                bool triggleSpecial, Uint8 rowH) :
                TabView(node, title), columnNumber(colNumber),
                multiSelectable(multiSelect), triggleSpecialButton(triggleSpecial),
                curShowIndex(0), curShowOffset(0), curShowLength(0), isMoved(false),
//                okButton(node, ResourceUri::okButtonPictureName),
                titleViews(true), specialButtons(true), contentViews(true),
                rowHeight(rowH), curSpecialIndex(-1),
                buttomView(node, ResourceUri::tabviewBackgroundPictureName)
    {
        assert(columnNumber > 0);
        assert(rowHeight > 0);
//        okButton.SetParentView(this);
//        this->subview.Add(&okButton);
//        okButton.SetId(BTN_OK);
    }
    
    inline void SetRowHeight(Uint8 rowH)
    {
        if (rowH == 0)
            return;
        rowHeight = rowH;
    }
    
    // touch event handlers
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
    {
        _needEvent = this->IsContainCCPoint(pTouch->getLocation());
        if (_needEvent)
        {
            _touchStartPt = pTouch->getLocation();
            _touchCurPt = _touchStartPt;
            isMoved = false;
        }
        return _needEvent;
    }
    
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
    {
        if (_needEvent)
        {
            _needEvent = false;
        }
    }
    
    // compute the touched title index (column index) if touched at title row
    // return -1, if not touched at title row
    int GetIndexOfTouchedTitle(CCTouch *pTouch);
    
    // Judge the touched point is in buttom row.
    bool IsTouchedButtom(CCTouch *pTouch);
    
    // Judge touched point is in the special buttons row or not
    bool IsTouchedSpecialRow(CCTouch *pTouch);
    
    // compute and update sub views dimension;
    void PrepareSubviewsDimension();
    
    // Display & Dismiss & Destory
    virtual void Display();
    virtual void Dismiss()
    {
        if (-1 != curSpecialIndex)
            HideSpecialButton();
        for (int i = curShowIndex*columnNumber; i < (curShowIndex+curShowLength)*columnNumber; i++)
        {
            contentViews[i]->Dismiss();
        }
        buttomView.Dismiss();
    }
    
    virtual void Destory()
    {
        Dismiss();
        for (int i  = 0; i< specialButtons.GetLength(); ++i)
        {
            specialButtons[i]->Destory();
        }
        for (int i = 0; i< contentViews.GetLength(); ++i)
        {
            contentViews[i]->Destory();
        }
        buttomView.Destory();
    }
    
private:
    //##ModelId=522B4B6300A7
    Uint8 columnNumber;
    //##ModelId=522B4BC902BC
    List<Uint32> selectedItem;
    //##ModelId=522B4BDE034A
    bool multiSelectable;
    //##ModelId=522B4BEC022F
//    Uint32 selectedItemNumber;
    //##ModelId=522B4BF9014E
//    CommonButton okButton;
    //##ModelId=522B4C6302DF
    List<CommonButton*> specialButtons;
    //##ModelId=522B4C8100F3
    bool triggleSpecialButton;
    //##ModelId=522B4C98031D
//    Uint32 specialButtonNumber;
    //##ModelId=522C617001A1
    List<ViewFrame*> contentViews;
    // Title views, seprated from content views
    List<ViewFrame*> titleViews;
    // Column width in percentage
    List<Uint8> columnWidthPercentages;
    /** order of items in content views. */
    //##ModelId=526531910060
    List<Uint32> sortOrder;
    
    // buttom picture view
    PictureView buttomView;
    
    // current showing list items start index (as row)
    Uint32 curShowIndex;
    // current showing first item offset as pixel
    Uint8 curShowOffset;
    // current showing list items length (as row)
    Uint8 curShowLength;
    // current showing special buttons list item index (as row), -1 is nothing special
    int curSpecialIndex;
    
    // The item row height as pixel
    Uint8 rowHeight;
    
    // touch pionts record
    cocos2d::CCPoint _touchStartPt, _touchEndPt, _touchCurPt;
    
    // set the touch mode is moved or not
    bool isMoved;
    
};

class ListView : public TabGroupView
{
public:
    ListView(CCNode* node) : TabGroupView(node) {
        this->SetIsModal(true);
    }
    
};

#endif /* LISTVIEW_H_HEADER_INCLUDED_AD808747 */
