#ifndef ROAD_H_HEADER_INCLUDED_AC6D09D5
#define ROAD_H_HEADER_INCLUDED_AC6D09D5

#include "../Common/List.h"
#include "../Common/types.h"

//##ModelId=522741390034
class Road
{
    //##ModelId=522742650170
    Uint32 id;
    //##ModelId=5228906E017F
    Uint32 linkedCityId[2];
    //##ModelId=522890C50363
    Point dividePoint;
    /** List<Point> */
    //##ModelId=522890ED01EE
    List<Point> keyPointList;
};



#endif /* ROAD_H_HEADER_INCLUDED_AC6D09D5 */
