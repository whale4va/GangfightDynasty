#ifndef GOLDMAPVIEW_H_HEADER_INCLUDED_AD80DB94
#define GOLDMAPVIEW_H_HEADER_INCLUDED_AD80DB94
#include "CommonButton.h"
//#include "TabView.h"
#include "ListView.h"
#include "TextView.h"

//##ModelId=522C81F20244
class GoldMapView : public TabView
{
    //##ModelId=522C828D02BA
    TextView enableMapText;
    //##ModelId=522C82AD02B1
    TextView buyGoldText;
    //##ModelId=522C82C6035F
    CommonButton gold2MoneyButton;
    //##ModelId=522C82DC0244
    CommonButton mapItems[2];
    //##ModelId=522C82ED019E
    ListView buyGoldList;
};



#endif /* GOLDMAPVIEW_H_HEADER_INCLUDED_AD80DB94 */
