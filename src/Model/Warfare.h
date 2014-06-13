#ifndef WARFARE_H_HEADER_INCLUDED_AC6D6C63
#define WARFARE_H_HEADER_INCLUDED_AC6D6C63

#include "../Common/types.h"
#include "../Common/List.h"
#include "../Common/String.h"
#include "../Model/Army.h"

//##ModelId=5228A56101DF
class Warfare
{
  public:
    //##ModelId=526D36890053
    void AddArmy(Army* pArmy);

    /** @brief compute army move path to get all attacking positions and
    retreating positions
    @param[out] aps attacking position list
    @param[out] rps retreating position list
 */
    //##ModelId=526D36A20353
    void ComputeArmyMovePath(List<Point>& aps, List<Point>& rps);

    /** @brief update army position according to <Adjust Army> user case with
    specific army's target point */
    //##ModelId=526D38880244
    void UpdateArmyPosition();

    /** @brief compute warfare area dimension, every army meet/hit this area
    just join the warfare. */
    //##ModelId=5275EFF50094
    Dimension GetWarfareDimension();

    /** @brief compute the roads that are covered by the warefare area
    (dimension),these roads will be used as judgement of tracing armies framely or
    not. If army entered any of these road, then its position are checked in every
    frame. */
    //##ModelId=52764A9A03AA
    List<Uint32> ComputeCoveredRoads();

  private:
    /** The warfare location city's name. */
    //##ModelId=5229ECC101AE
    String name;
    //##ModelId=5229F0BF024A
    Uint32 countryIdList[2];
    /** List<Uint32> */
    //##ModelId=5229F0D2030A
    List<Uint32> armyIdList;
    /** List<Uint32> */
    //##ModelId=5229FEFD0346
    List<Uint32> armyTargetIdList;
    //##ModelId=5229FE7901EF
    Point location;
    //##ModelId=5229FE990013
    Uint32 areaRow;
    //##ModelId=5229FEA5006E
    Uint32 areaColumn;
    //##ModelId=5229FEB30105
    List<Uint32> areaObjectId;
    //##ModelId=5229FECC01F8
    Dimension armyDimension;
    //##ModelId=5229FEDD004B
    Uint32 inCityId;
    //##ModelId=5229FEE30204
    Uint32 inRoadId;
    /** @brief army position list, the position is in the warfare area view
    coordinates. */
    //##ModelId=526D39CA02D5
    List<Point> armyPositionList;
    //##ModelId=5275EEDA0314
    Uint32 id;
};



#endif /* WARFARE_H_HEADER_INCLUDED_AC6D6C63 */
