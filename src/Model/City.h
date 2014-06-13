#ifndef CITY_H_HEADER_INCLUDED_AC6D72EC
#define CITY_H_HEADER_INCLUDED_AC6D72EC

#include "../Common/types.h"
#include "../Common/List.h"
#include "Army.h"

//##ModelId=5227412400F1
class City
{
  public:
    //##ModelId=5276163C0354
    Dimension GetCityDimension();

    //##ModelId=527D977402AF
    Uint32 get_agriculture() const;

    //##ModelId=527D977402E6
    void set_agriculture(Uint32 left);

    //##ModelId=527D97740368
    List<Uint32> get_armyIdList() const;

    //##ModelId=527D977403A4
    void set_armyIdList(List<Uint32> left);

    //##ModelId=527D97750047
    Uint32 get_business() const;

    //##ModelId=527D97750086
    void set_business(Uint32 left);

    //##ModelId=527D97750118
    Dimension get_cityDimension() const;

    //##ModelId=527D9775015A
    void set_cityDimension(Dimension left);

    //##ModelId=527D977501F6
    Army get_defenseArmy() const;

    //##ModelId=527D9775023C
    void set_defenseArmy(Army left);

    //##ModelId=527D977502DE
    Uint32 get_horse() const;

    //##ModelId=527D97750327
    void set_horse(Uint32 left);

    //##ModelId=527D977503D5
    Uint32 get_id() const;

    //##ModelId=527D9776003A
    void set_id(Uint32 left);

    //##ModelId=527D977600EF
    Uint32 get_level() const;

    //##ModelId=527D97760140
    void set_level(Uint32 left);

    //##ModelId=527D977601FD
    Point get_location() const;

    //##ModelId=527D97760251
    void set_location(Point left);

    //##ModelId=527D97760317
    String get_name() const;

    //##ModelId=527D97760373
    void set_name(String left);

    //##ModelId=527D97770059
    List<Uint32> get_neighborCityIdList() const;

    //##ModelId=527D977700B6
    void set_neighborCityIdList(List<Uint32> left);

    //##ModelId=527D9777018D
    Uint32 get_officerId() const;

    //##ModelId=527D977701EC
    void set_officerId(Uint32 left);

    //##ModelId=527D977702CB
    List<Uint32> get_roadIdList() const;

    //##ModelId=527D9777032F
    void set_roadIdList(List<Uint32> left);

    //##ModelId=527D97780031
    Uint32 get_security() const;

    //##ModelId=527D97780099
    void set_security(Uint32 left);

    //##ModelId=527D9778018C
    Uint32 get_soldier() const;

    //##ModelId=527D977801F9
    void set_soldier(Uint32 left);

    //##ModelId=527D977802F3
    Uint32 get_spear() const;

    //##ModelId=527D97780363
    void set_spear(Uint32 left);

    //##ModelId=527D9779007F
    StrategyType get_strategy() const;

    //##ModelId=527D977900F4
    void set_strategy(StrategyType left);

    //##ModelId=527D977901FC
    Uint32 get_sword() const;

    //##ModelId=527D97790271
    void set_sword(Uint32 left);

  private:
    //##ModelId=5228A57000B4
    Uint32 id;
    //##ModelId=5228A57A029F
    Uint32 officerId;
    //##ModelId=5228A5AE0206
    Uint32 agriculture;
    //##ModelId=5228A5D9025E
    Uint32 business;
    //##ModelId=5228A5E7027D
    Uint32 security;
    //##ModelId=5228A60101F4
    Uint32 soldier;
    //##ModelId=5228A61602F1
    Uint32 sword;
    //##ModelId=5228A626007E
    Uint32 spear;
    //##ModelId=5228A6370269
    Uint32 horse;
    //##ModelId=5228A64902C5
    Uint32 level;
    //##ModelId=5228A87701ED
    StrategyType strategy;
    /** List<Uint32> */
    //##ModelId=5228A8890309
    List<Uint32> neighborCityIdList;
    //##ModelId=522B279903AB
    String name;
    /** List<Uint32> */
    //##ModelId=5228A8DC0118
    List<Uint32> roadIdList;
    /** List<Uint32> */
    //##ModelId=5228A916008A
    List<Uint32> armyIdList;
    //##ModelId=5228A94C02AD
    Army defenseArmy;
    //##ModelId=527247AC03A8
    Point location;
    //##ModelId=5276162E004F
    Dimension cityDimension;
};



#endif /* CITY_H_HEADER_INCLUDED_AC6D72EC */
