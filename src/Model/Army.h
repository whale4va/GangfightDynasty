#ifndef ARMY_H_HEADER_INCLUDED_AC6D116A
#define ARMY_H_HEADER_INCLUDED_AC6D116A

#include "../Common/types.h"
#include "../Common/List.h"
#include "../Common/String.h"

//##ModelId=5228831201E8
class Army
{
  public:
    /** @brief init army object with creation moment information
    @param[in] num soldier number of the army
    @param[in] type weapon type
    @param[in] weapn the number of weapon in the army
 */
    //##ModelId=526CC82D00D8
    void InitWithCreation();

    /** @brief get army id
    @return the id of army */
    //##ModelId=526CC94301F0
    Uint32 GetId();

    //##ModelId=526CC99302C0
    void SetLeaderId(Uint32 id);
    
    inline String GetName() { return name; }
    inline WeaponType GetWeaponType() { return weaponCategory; }
    inline Uint32 GetSoldier() { return soldier; }
    
    // get army object by its id.
    static Army GetArmyById(Uint32 id);

  private:
    //##ModelId=5228836F0087
    Uint32 id;
    //##ModelId=522883B0015F
    Uint32 soldier;
    //##ModelId=522883C20248
    WeaponType weaponCategory;
    //##ModelId=5228846502F6
    Uint32 weapon;
    //##ModelId=5228850E01B3
    Uint32 leaderId;
    //##ModelId=522885980306
    String name;
    //##ModelId=52288770019C
    Point location;
    //##ModelId=522887860141
    Uint32 resideCityId;
    //##ModelId=522888AC0238
    bool selected;
    //##ModelId=522888D8014C
    Uint32 speed;
    //##ModelId=522888F5039D
    Uint32 roadId;
    //##ModelId=522889820270
    Dimension dimension;
    //##ModelId=5228899500E3
    Uint32 countryId;
};



#endif /* ARMY_H_HEADER_INCLUDED_AC6D116A */
