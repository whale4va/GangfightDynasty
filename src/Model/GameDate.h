#ifndef GAMEDATE_H_HEADER_INCLUDED_AC6D6F9B
#define GAMEDATE_H_HEADER_INCLUDED_AC6D6F9B

#include "../Common/types.h"

//##ModelId=522B29890213
struct GameDate
{
    //##ModelId=522B2A0D0000
    Uint8 month;
    //##ModelId=522B2A4C010D
    Uint8 day;
    //##ModelId=522B2A6201F9
    Uint32 year;
    
public:
    static GameDate GetCurrentDate();
    
    // init with current date.
    GameDate();
    // init with current date + days (as move of calendar)
    GameDate(int days);
    
    GameDate(const GameDate& gd);
    
    GameDate& operator=(const GameDate& gd);
    
    void ForwardDays(int days);

    // 升级需要的天数
    static int upgradeNeedDays;
};



#endif /* GAMEDATE_H_HEADER_INCLUDED_AC6D6F9B */
