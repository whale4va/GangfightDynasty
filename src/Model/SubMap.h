#ifndef SUBMAP_H_HEADER_INCLUDED_AC6D62B2
#define SUBMAP_H_HEADER_INCLUDED_AC6D62B2

#include "../Common/List.h"
#include "../Common/String.h"

//##ModelId=522C83370107
class SubMap
{
  public:
    //##ModelId=522F2FE603B4
    void SetEnabled(bool enabled);

    //##ModelId=522F31B9001F
    inline void SetCityIdList(List<Uint32> list)
    {
        cityIdList = list;
    }

    //##ModelId=522F31CE017E
    inline void SetRoadIdList(List<Uint32> list)
    {
        divideRoadId = list;
    }

    //##ModelId=522F31E100D8
    void SetName(String name);

    //##ModelId=524ED0770371
    bool GetEnabled();

  private:
    //##ModelId=522C83E2020E
    List<Uint32> cityIdList;
    //##ModelId=522C83F5006D
    List<Uint32> divideRoadId;
    //##ModelId=522C841401C6
    bool enabled;
    //##ModelId=522C842103D0
    String name;
};



#endif /* SUBMAP_H_HEADER_INCLUDED_AC6D62B2 */
