#include "Leader.h"

Leader::Leader()
{
    id = LEADER_DEFAULT_ID;
    name = "百户";
    smart = power = 10;
    assignedTask = NULL;
    managedCityId = GAME_INVALID_ID;
    belongCountryId = GAME_INVALID_ID;
    expense = 0;
    header = ResourceUri::leaderDefaultPictureName;
    manageArmy = NULL;
}

Leader::Leader(const Leader& l)
{
    id = l.id;
    name = l.name;
    smart = l.smart;
    power = l.power;
    assignedTask = l.assignedTask;
    managedCityId = l.managedCityId;
    belongCountryId = l.belongCountryId;
    expense = l.expense;
    header = l.header;
    manageArmy = l.manageArmy;
}

Leader& Leader::operator=(const Leader &l)
{
    if (this == &l)
        return *this;
    
    id = l.id;
    name = l.name;
    smart = l.smart;
    power = l.power;
    assignedTask = l.assignedTask;
    managedCityId = l.managedCityId;
    belongCountryId = l.belongCountryId;
    expense = l.expense;
    header = l.header;
    manageArmy = l.manageArmy;
    
    return *this;
}

Leader Leader::GetLeaderById(Uint32 id)
{
    Leader l;
    
    return l;
}

List<Leader*> Leader::QueryAllLeaders()
{
    List<Leader*> ls(true);
    
    return ls;
}


List<Leader*> Leader::QueryAvailableLeaders(
                    sortField sort, int start, int num)
{
    List<Leader*> ls(true);
    
    return ls;
}
