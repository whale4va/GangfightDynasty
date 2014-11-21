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
    
    
public:
    
    typedef enum _sortField
    {
        SORT_BY_NAME = 0,
        SORT_BY_SMART,
        SORT_BY_POWER
    }sortField;
    
    // static method, query all leaders
    static List<Leader*> QueryAllLeaders();
    
    // query this player can used leaders.
    static List<Leader*> QueryAvailableLeaders(sortField sort=SORT_BY_SMART,
                                               int start = 0,
                                               int num = -1);
    
    // query with sort type and range(index, number)
    static List<Leader*> QueryWithSortRange(sortField sort=SORT_BY_SMART,
                                            int start = 0,
                                            int num = -1);
    
    // get leader object by its id.
    static Leader GetLeaderById(Uint32 id);
    
    
    // getter & setter
    inline String GetName() { return name; }
    inline void SetName(String n) { name = n; }

    inline Uint32 GetSmart() { return smart; }
    inline void SetSmart(Uint32 s) { smart = s; }

    inline Uint32 GetPower() { return power; }
    inline void SetPower(Uint32 p) { power = p; }
    
    inline void SetAssignTask(Event* pE) {assignedTask = pE;}
    
};


#endif /* LEADER_H_HEADER_INCLUDED_AC6D68C0 */
