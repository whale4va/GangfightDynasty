#ifndef ARMYVIEW_H_HEADER_INCLUDED_AD80E5A6
#define ARMYVIEW_H_HEADER_INCLUDED_AD80E5A6
#include "CommonButton.h"
#include "PictureView.h"
#include "TextView.h"

//##ModelId=522B419900A8
class ArmyView : public CommonButton
{
    //##ModelId=522B499500EC
    PictureView leaderHeader;
    //##ModelId=522B49A603BE
    TextView leaderName;
    //##ModelId=522B49B800DA
    TextView soldierNumber;
    //##ModelId=522B49EE0118
    Uint32 armyId;
};



#endif /* ARMYVIEW_H_HEADER_INCLUDED_AD80E5A6 */
