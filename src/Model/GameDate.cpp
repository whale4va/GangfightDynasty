#include "GameDate.h"

int GameDate::upgradeNeedDays = 30;

GameDate::GameDate()
{
    month = 1;
    day = 1;
    year = 100;
}

GameDate GameDate::GetCurrentDate()
{
    GameDate gd;
    return gd;
}

GameDate::GameDate(int days)
{
    GameDate gd;
    
    return gd.ForwardDays(days);
}

void GameDate::ForwardDays(int days)
{
    if (days <= 30 - day) {
        day += days;
        return;
    }
    
    days -= (30 - day);
    int addDays = days % 30;
    int addMonth = days / 30;
    if (addMonth <= 12 - month) {
        day = addDays;
        month += addMonth;
        return;
    }
    
    days -= (12-month)*30;
    addDays = days % 30;
    addMonth = days % (12*30);
    int addYear = days / (12*30);
    day = addDays;
    month = addMonth;
    year += addYear;
    return;
}

GameDate::GameDate(const GameDate& gd)
{
    month = gd.month;
    day = gd.day;
    year = gd.year;
}

GameDate& GameDate::operator=(const GameDate &gd)
{
    if (this == &gd)
        return *this;
    day = gd.day;
    month = gd.month;
    year = gd.year;
    return *this;
}
