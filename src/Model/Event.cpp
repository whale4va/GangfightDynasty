#include "Event.h"

void Event::SetType(EventType t)
{
    type = t;
}

EventType Event::GetType()
{
    return type;
}

void Event::SetArmies(List<Army *> armies)
{
    executeArmies = armies;
}

List<Army*> Event::GetArmies()
{
    return executeArmies;
}

void Event::SetTargetCityId(Uint32 id)
{
    targetCityId = id;
}

Uint32 Event::GetTargetCityId()
{
    return targetCityId;
}

void Event::SetExecuteLeaders(List<Leader *> leaders)
{
    executeLeaders = leaders;
}

List<Leader*> Event::GetExecuteLeaders()
{
    return executeLeaders;
}

void Event::SetUpgradeResult(Uint32 result)
{
    upgradeResult = result;
}

Uint32 Event::GetUpgradeResult()
{
    return upgradeResult;
}

void Event::SetDeadLine(GameDate date)
{
    deadLine = date;
}

GameDate Event::GetDeadLine()
{
    return deadLine;
}
