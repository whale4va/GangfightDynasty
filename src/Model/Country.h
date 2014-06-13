#ifndef COUNTRY_H_HEADER_INCLUDED_AC6D39C6
#define COUNTRY_H_HEADER_INCLUDED_AC6D39C6

#include "../Common/types.h"
#include "../Common/List.h"
#include "../Common/String.h"

//##ModelId=522C781C0055
class Country
{
  public:
    //##ModelId=522C7CC5030F
    List<Uint32> EnumerateLeaders();

    //##ModelId=522F32AF03D8
    void SetGold(Uint32 num);

    //##ModelId=522F32C30000
    Uint32 GetGold();

    //##ModelId=5241891403E5
    void SetMoney(Uint32 num);

    //##ModelId=5241891B01E0
    Uint32 GetMoney();

    //##ModelId=5263ED780303
    List<Uint32> GetCityList();

  private:
    //##ModelId=522C7971003B
    List<Uint32> cityIdList;
    //##ModelId=522C79E700D3
    String name;
    //##ModelId=522C7BD50008
    Uint32 id;
    //##ModelId=522C7BE0037A
    List<Uint32> LeaderIdList;
    //##ModelId=522C7C580040
    Uint32 money;
    //##ModelId=522C7C610074
    Uint32 food;
    //##ModelId=522C7C6E0348
    Uint32 gold;
    //##ModelId=522C7C79039A
    List<Uint32> armyIdList;
    //##ModelId=522C7CAE0028
    String flag;
};



#endif /* COUNTRY_H_HEADER_INCLUDED_AC6D39C6 */
