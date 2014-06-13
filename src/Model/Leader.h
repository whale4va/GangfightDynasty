#ifndef LEADER_H_HEADER_INCLUDED_AC6D68C0
#define LEADER_H_HEADER_INCLUDED_AC6D68C0

#include "../Common/types.h"
#include "Army.h"
//#include "Event.h"
class Event;

//##ModelId=522B1F0102F1
class Leader
{
    //##ModelId=522B215F002E
    Uint32 id;
    //##ModelId=522B21E600E9
    String name;
    //##ModelId=522B2214005C
    Uint32 smart;
    //##ModelId=522B222203C8
    Uint32 power;
    //##ModelId=522B22480066
    Event* assignedTask;
    //##ModelId=522B24B2013B
    Uint32 managedCityId;
    //##ModelId=522B250202A1
    Uint32 belongCountryId;
    //##ModelId=522B253802EF
    Uint32 expense;
    /** leader's header picture file name. */
    //##ModelId=522B255502AE
    String header;
    //##ModelId=522B25730009
    Army* manageArmy;
};



#endif /* LEADER_H_HEADER_INCLUDED_AC6D68C0 */
