#ifndef TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3
#define TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3
#include "ViewFrame.h"

//##ModelId=522C76D50103
class TabGroupView : public ViewFrame
{
    //##ModelId=52668E51035F
    // tab view group tab views list
    List<TabView*> _tabList;

    // indicate which tab is selected in the group
    int _selectedIndex;
};



#endif /* TABGROUPVIEW_H_HEADER_INCLUDED_AD808BD3 */
