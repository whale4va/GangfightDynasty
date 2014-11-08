#include "ListView.h"
#include "ViewFrame.h"

//##ModelId=526529FC0399
void ListViewTab::RedrawWithOrder(List<Uint32> order)
{
    if (curSpecialIndex != -1)
        HideSpecialButton();
    sortOrder = order;
    Dismiss();
    Display();
}

//##ModelId=526D103003E6
void ListViewTab::ShowSpecialButton()
{
    if (curSpecialIndex == -1)
        return;
    
    Point viewPoint = position;
    viewPoint.z += 2.0;     // upper than content views even buttom view
    viewPoint.y += dimension.h/2 - rowHeight + curShowOffset - rowHeight/2;
    viewPoint.y -= rowHeight*(curSpecialIndex - curShowIndex);
    viewPoint.y -= rowHeight;       // the next row after special row.
    specialButtons.SetPoint(viewPoint);
    Dimension dim = dimension;
    dim.h = rowHeight;
    specialButtons.SetDimension(dim);
    
    if (curSpecialIndex == curShowIndex + curShowLength -1)
    {
        // last row, change its z order and let them cover buttom row
        for (int j = 0; j < columnNumber; j++)
        {
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->position.z += 2.0;
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->Dismiss();
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->Display();
        }
    }
    
    specialButtons.Display();
    /**** No need to move, just show special buttons and cover next row
    if (curSpecialIndex != curShowIndex + curShowLength - 1)
    {
        // last row is dismissed if special row is not last row
    }
    else
    {
        // last row is the special row, move up previews rows to make show offset = 0
        // make the first showing row as dismissed.
    }
     ****/
}

void ListViewTab::HideSpecialButton()
{
    
    /**** No need to move, just show special buttons and cover next row
    if (curSpecialIndex != curShowIndex + curShowLength - 1)
    {   // last row is re-displayed.
    }
    else
    {   // first row is still not needed re-displayed. just dismiss special buttons.
    }
     ***/
    specialButtons.Dismiss();
    
    if (curSpecialIndex == curShowIndex + curShowLength -1)
    {
        // last row, restore its z order to normal and let it be covered by buttom
        for (int j = 0; j < columnNumber; j++)
        {
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->position.z = position.z;
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->Dismiss();
            contentViews[sortOrder[curSpecialIndex]*columnNumber+j]->Display();
        }
    }
    
    curSpecialIndex = -1;
}

void ListViewTab::PrepareSubviewsDimension()
{
    if (columnWidthPercentages.GetLength() != columnNumber)
        THROW(Invalid_ColumnWidthPercentage);
    Uint8 total = 0;
    for (int i = 0; i < columnWidthPercentages.GetLength(); i++)
    {
        total += columnWidthPercentages[i];
    }
    if (total != 100)
        THROW(Invalid_ColumnWidthPercentage);
    
    for (int i = 0; i < columnNumber; i++)
    {
        Dimension dim;
        dim.w = dimension.w * columnWidthPercentages[i] / 100;
        dim.h = rowHeight;
        titleViews[i]->SetDimension(dim);
        for (int j = i; j < contentViews.GetLength(); j+=columnNumber)
        {
            contentViews[j]->SetDimension(dim);
        }
    }
    
    // set buttom view dimension
    Dimension dim = dimension;
    dim.h = rowHeight;
    buttomView.SetDimension(dim);
}

void ListViewTab::Display()
{
    if (!dimension.IsValid())
    {
        THROW(Invalid_Dimension);
    }
    
    if (dimension.h < rowHeight*4)
    {
        THROW(Invalid_Dimension);
    }
    
    // The first row is "Title" & the last row is "Bottom"
    curShowLength = ceil((dimension.h - 2*rowHeight)/rowHeight);
    
    if (sortOrder.GetLength() == 0)
    {
        for (int i = 0; i < contentViews.GetLength()/columnNumber; i++)
        {
            sortOrder.Add(i);
        }
    }
    
    // prepare dimension of sub views if needed.
    if (!titleViews[0]->dimension.IsValid())
        PrepareSubviewsDimension();
    
    // show title row first
    Point viewPoint = position;
    viewPoint.z += 1.0;     // upper than content
    viewPoint.x -= dimension.w/2;
    viewPoint.y += dimension.h/2 - rowHeight/2;
    for (int i = 0; i < columnNumber; i++)
    {
        viewPoint.x += titleViews[i]->dimension.w/2;
        titleViews[i]->SetPoint(viewPoint);
        titleViews[i]->Display();
        viewPoint.x += titleViews[i]->dimension.w/2;
    }
    
    // show buttom row second
    viewPoint = position;
    viewPoint.y -= dimension.h/2;
    viewPoint.y += rowHeight/2;
    viewPoint.z += 1.0;     // upper than content
    buttomView.SetPoint(viewPoint);
    buttomView.Display();
    
    // show content rows
    viewPoint = position;
    viewPoint.x -= dimension.w/2;
    viewPoint.y += dimension.h/2 - rowHeight;
    viewPoint.y += curShowOffset - rowHeight/2;
    
    Point highLightPt = position;
    highLightPt.z += 2.0;
    highLightPt.y += dimension.h/2 - rowHeight;
    highLightPt.y += curShowOffset - rowHeight/2;
    for (int i = curShowIndex; i < curShowIndex+curShowLength; i++)
    {
        // show this row high light view first if needed.
        int existedIndex = selectedItem.Find(sortOrder[i]);
        if ( existedIndex != selectedItem.invalidIndex)
        {
            highLightViews[existedIndex]->SetPoint(highLightPt);
            highLightViews[existedIndex]->Display();
        }
        highLightPt.y -= rowHeight;
        
        // show every  columns in this row.
        viewPoint.x = position.x - dimension.w/2;
        for (int j = 0; j < columnNumber; j++)
        {
            viewPoint.x += titleViews[j]->dimension.w/2;
            contentViews[sortOrder[i]*columnNumber + j]->SetPoint(viewPoint);
            contentViews[sortOrder[i]*columnNumber + j]->Display();
            viewPoint.x += titleViews[j]->dimension.w/2;
        }
        viewPoint.y -= rowHeight;
    }
    
}

void ListViewTab::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
        if (_needEvent)
        {
            if (rowHeight < FLOAT_MINOR_LIMIT)
                THROW(Invalid_ListRowHeight);
            float totalOffset = curShowIndex*rowHeight + curShowOffset;
            float deltaY = pTouch->getLocation().y - _touchCurPt.y;
            if (deltaY < FLOAT_MINOR_LIMIT)
            {
                _touchCurPt = pTouch->getLocation();
                return;
            }
            // The first line is the title line,
            // In view content, the first row and last row are title and bottom bar
            float maxOffset = (contentViews.GetLength()/columnNumber)* rowHeight - (dimension.h - 2*rowHeight);
            isMoved = true;
            if (totalOffset < FLOAT_MINOR_LIMIT && deltaY < 0.0)
                isMoved = false;
            if (totalOffset >= (maxOffset - FLOAT_MINOR_LIMIT) && deltaY > 0.0)
                isMoved = false;
            
            totalOffset += deltaY;
            if (totalOffset < 0)
                totalOffset = 0.0;
            if (totalOffset > maxOffset)
                totalOffset = maxOffset;
            
            curShowIndex = floor(totalOffset/rowHeight);
            curShowOffset = totalOffset - curShowIndex*rowHeight;
            assert(curShowOffset > -FLOAT_MINOR_LIMIT);
            
            _touchCurPt = pTouch->getLocation();
            
            if (isMoved)
            {
                this->Dismiss();
                this->Display();
            }
            return;
        }
}

bool ListViewTab::IsTouchedButtom(cocos2d::CCTouch *pTouch)
{
    if (!dimension.IsValid())
        THROW(Invalid_Dimension);
    
    float lbx = position.x - dimension.w/2;
    float lby = position.y - dimension.h/2;
    float rtx = lbx + dimension.w;
    float rty = lby + rowHeight;
    
    CCPoint pos = pTouch->getLocation();
    if ( pos.x >= lbx && pos.x <= rtx
        && pos.y >= lby && pos.y <= rty)
        return true;

    return false;
}

int ListViewTab::GetIndexOfTouchedTitle(cocos2d::CCTouch *pTouch)
{
     if (!dimension.IsValid())
        THROW(Invalid_Dimension);
    
    float lbx = position.x - dimension.w/2;
    float rty = position.y + dimension.h/2;
    float rtx = lbx + dimension.w;
    float lby = rty - rowHeight;
    
    CCPoint pos = pTouch->getLocation();
    if ( pos.x >= lbx && pos.x <= rtx
        && pos.y >= lby && pos.y <= rty)
    {
        Uint8 total = 0;
        for (int i =0; i < columnWidthPercentages.GetLength(); i++)
            total += columnWidthPercentages[i];
        if (total != 100)
            THROW(Invalid_ColumnWidthPercentage);
        
        float percentage = (pos.x - lbx)/dimension.w;
        if (percentage < 0.0)
            percentage = FLOAT_MINOR_LIMIT;
        
        total = 0;
        for (int i = 0; i < columnWidthPercentages.GetLength(); i++)
        {
            total += columnWidthPercentages[i];
            if (percentage < (float)total)
                return i;
        }
    }
    
    return -1;
}

bool ListViewTab::IsTouchedSpecialRow(cocos2d::CCTouch *pTouch)
{
    if (triggleSpecialButton)
    {
        if (curSpecialIndex != -1)
        {
            float ty = position.y + dimension.h/2 - rowHeight -
                ((curSpecialIndex - curShowIndex)*rowHeight + (rowHeight - curShowOffset));
            float by = ty - rowHeight;
            float lx = position.x - dimension.w/2;
            float rx = lx + dimension.w;
            cocos2d::CCPoint pos = pTouch->getLocation();
            if (pos.x >= lx && pos.x <= rx
                && pos.y >= by && pos.y <= ty)
                return true;
        }
    }
    return  false;
}

void ListViewTab::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
        if (_needEvent)
        {
            if (rowHeight < FLOAT_MINOR_LIMIT)
                THROW(Invalid_ListRowHeight);
            float totalOffset = curShowIndex*rowHeight + curShowOffset;
            float deltaY = pTouch->getLocation().y - _touchCurPt.y;
            
            _touchEndPt = pTouch->getLocation();
            _needEvent = false;
            if (deltaY > FLOAT_MINOR_LIMIT)
            {   // react as touch move
                totalOffset += deltaY;
                float maxOffset = (contentViews.GetLength()/columnNumber)* rowHeight - (dimension.h - 2*rowHeight);
                
                bool needRedraw = true;
                if (totalOffset < FLOAT_MINOR_LIMIT && deltaY < 0.0)
                    needRedraw = false;
                if (totalOffset >= (maxOffset - FLOAT_MINOR_LIMIT) && deltaY > 0.0)
                    needRedraw = false;
                
                if (totalOffset < 0)
                    totalOffset = 0.0;
                if (totalOffset > maxOffset)
                    totalOffset = maxOffset;
                
                curShowIndex = floor(totalOffset/rowHeight);
                curShowOffset = totalOffset - curShowIndex*rowHeight;
                if (needRedraw)
                {
                    this->Dismiss();
                    this->Display();
                }
            }
            else
            {   // react this touch as normal touch, not move.
                if (!isMoved)
                {
                    // Check is touched at title & buttom
                    if (IsTouchedButtom(pTouch))
                        return;         // touched at buttom, just return, no further action
                    int columnIndex =GetIndexOfTouchedTitle(pTouch);
                    if ( columnIndex != -1)
                    {   // touched at title, sort rows as column
                        if (parentView != NULL)
                            parentView->OnSortListByColumn(columnIndex);
                        return;
                    }
                    if (IsTouchedSpecialRow(pTouch))
                        return;        // touched at special buttoms row, not on button, just return.
                    
                // Not touched at title & bottom, check selected item(row) and show special buttons if needed.
                    float offset = position.y + dimension.h/2 - rowHeight - _touchEndPt.y - curShowOffset;
                    Uint32 newShowIndex = 0;
                    if (offset <= 0.0)
                        newShowIndex = curShowIndex;
                    else
                        newShowIndex = curShowIndex + ceil(offset/rowHeight);
                    
                    if (triggleSpecialButton)
                    {
                        
                        if (curSpecialIndex == -1)
                        {
                            curSpecialIndex = newShowIndex;
                            this->ShowSpecialButton();
                        }
                        else if (curSpecialIndex != newShowIndex)
                        {
                            // de-select current selected item(row) and notify parent view
//                            if (!multiSelectable)
//                            {
//                                int existedIndex = selectedItem.Find(sortOrder[curSpecialIndex]);
//                                if ( existedIndex != selectedItem.invalidIndex)
//                                    selectedItem.Remove(existedIndex);
//                                if (parentView != NULL)
//                                    parentView->OnListItemUnselected(sortOrder[curSpecialIndex]);
//                            }
                            
                            
                            // hide & show special buttons.
                            this->HideSpecialButton();
                            if (newShowIndex > curSpecialIndex)
                                newShowIndex--;     // because special buttons occupy one row
                            curSpecialIndex = newShowIndex;
                            this->ShowSpecialButton();
                        }
                        else if (curSpecialIndex == newShowIndex)
                        {
                            this->HideSpecialButton();
                                                        
                            // de-select current selected item(row) and notify parent view
//                            int existedIndex = selectedItem.Find(sortOrder[curSpecialIndex]);
//                            if ( existedIndex != selectedItem.invalidIndex)
//                                selectedItem.Remove(existedIndex);
//                            if (parentView != NULL)
//                                parentView->OnListItemUnselected(sortOrder[curSpecialIndex]);
                            curSpecialIndex = -1;
                        }
                    }
                    
                    // record the row which is selected and notify parent view.
                    int existedIndex = selectedItem.Find(sortOrder[newShowIndex]);
                    if (existedIndex != selectedItem.invalidIndex)
                    {
                        selectedItem.Remove(existedIndex);
                        if (parentView != NULL)
                            parentView->OnListItemUnselected(sortOrder[newShowIndex]);
                        
                        highLightViews[existedIndex]->Dismiss();
                        delete highLightViews[existedIndex];
                        highLightViews.Remove(existedIndex);
                    }
                    else
                    {
                        if (!multiSelectable)
                        {
                            // de-select already selected list items
                            for (int i = 0; i < selectedItem.GetLength(); i++)
                            {
                                if (parentView != NULL)
                                    parentView->OnListItemUnselected(selectedItem[i]);
                            }
                            selectedItem.Release();
                            highLightViews.Release();
                        }
                        selectedItem.Add(sortOrder[newShowIndex]);  // convert showing index to data index.
                       
                        // add & show high light picture view
                        cocos2d::CCSpriteBatchNode* pBatchNode = CCSpriteBatchNodeManager::GetSpriteBatchNodeByName(ResourceUri::listViewHighLightPictureName);
                        
                        PictureView* pPic = new PictureView(
                                                _node,
                                                pBatchNode->getTexture());
                        Dimension dim = dimension;
                        dim.h = rowHeight;
                        pPic->SetDimension(dim);
                        Point pt = position;
                        pt.z += 2.0;
                        pt.y += dimension.h/2 - rowHeight;
                        pt.y += curShowOffset - rowHeight/2;
                        pt.y -= (newShowIndex - curShowOffset)*rowHeight;
                        pPic->SetPoint(pt);
                        pPic->Display();
                        
                        highLightViews.Add(pPic);
                        
                        if (parentView != NULL)
                            parentView->OnListItemSelected(sortOrder[newShowIndex]);
                    }
                }
            }
            return;
        }
}

