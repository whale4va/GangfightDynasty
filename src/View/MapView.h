#ifndef MAPVIEW_H_HEADER_INCLUDED_AD809D76
#define MAPVIEW_H_HEADER_INCLUDED_AD809D76
#include "CommonButton.h"
#include "PictureView.h"

//##ModelId=522C7FDC00CB
class MapView
{
  public:
    //##ModelId=526688790309
    void InitWithResourceManager();

  private:
    //##ModelId=522C7FEA02D7
    PictureView backgroundMap;
    //##ModelId=522C810C01E0
    List<CommonButton*> cityIconList;
    //##ModelId=522C811C0105
    List<Uint32> cityIdList;
    //##ModelId=522C813D0290
    List<CommonButton> armyIconList;
    //##ModelId=522C81500314
    List<Uint32> armyIdList;
    //##ModelId=526712A600CF
    Point centralPoint;
};



#endif /* MAPVIEW_H_HEADER_INCLUDED_AD809D76 */
