#ifndef CITYVIEW_H_HEADER_INCLUDED_AD80A9BF
#define CITYVIEW_H_HEADER_INCLUDED_AD80A9BF
#include "ListView.h"
#include "CommonButton.h"
#include "TextView.h"
#include "../Model/Army.h"

//##ModelId=522B31BB0325
class CityView : public ViewFrame
{
  public:
    /** @brief inital and show upgrade view for specific upgrade requst
    according to user tap button id. */
    //##ModelId=522B3F960141
    void ShowUpgradeView();

    /** @brief initial all subviews in city view with specific city id. */
    //##ModelId=5267134E01CE
    void InitWithCityId(Uint32 id);

    /** @brief show leader list that can be an officer, used for user case
    <Assign Officer> */
    //##ModelId=5267D4970029
    void ShowCandidateOfficerList();

    /** @brief show city strategy buttons let user to choose, used for <Assign
    Strategy> user case. */
    //##ModelId=526931940342
    void ShowStrategyButtonGroup();

    /** @brief show armies that reside in the city in a list view. */
    //##ModelId=5269C5180231
    void ShowArmyList();

    /** @brief show button group view for amry weapon types, user can choose
    new army weapon type from the group in <Create Army> user case. */
    //##ModelId=526CC18E035B
    void ShowWeaponButtonGroup();

    /** @brief show warning view about the weapon lacking information on the
    particular amry operation. */
    //##ModelId=526D09AE025B
    void ShowWeaponLackWarning();

    /** @brief show warning view to get confirm of canceling army or not in
    <Cancel Army> user case. */
    //##ModelId=526CCF260148
    void ShowCancelConfirmWarning();

    /** @brief show number slip view for army soldier adjusting, this method
    both for <Create Army> <Supply Army> <Split Army> user cases.
    @param[in] id specify the number slip view used for which case or can be
    considerd as number slip view id. */
    //##ModelId=526CD695013E
    void ShowArmySlipView(Uint32 id);

    /** @brief show candidate leader list for specific army in <Assign Leader>
    user case. */
    //##ModelId=526D124D02BF
    void ShowCandidateLeaderList();

    /** @brief cancel/delete army as user wanted
    @param[in] id id of the army that want to be canceled. */
    //##ModelId=526CCF9C01C1
    void CencelArmyAsDefined(Uint32 id);

    /** @brief create specific army according to user operations
    @return army object pointer. */
    //##ModelId=526CCD9600F0
    Army* CreateArmyAsDefined();

    /** @brief supply army as defined in <Supply army> user case. */
    //##ModelId=526CDD5D0249
    void SupplyArmyAsDefined();

    /** @brief chagne army weapon type as selected
    @param[in] id the id of army that need to be changed
    @param[in] type the weapon type that want to change to */
    //##ModelId=526D118001E8
    void ChangeArmyWeapon(Uint32 id, WeaponType type);

    /** @brief implement split army operation in <Split Army> user case
    according to user adjusted number slip view, will generate a new army in the
    city
    @param[in] id the id of army that will be splitted. */
    //##ModelId=526D13C6003A
    void SplitArmyAsDefined(Uint32 id);

    /** @brief merge armies as user wanted, only some weapon type armies can be
    merged together into one army
    @param[in] ids the id list of selected armies */
    //##ModelId=526D148D0180
    void MergeArmies(List<Uint32> ids);

  private:
    //##ModelId=522B331F0252
    ListView armyListView;
    //##ModelId=522B35AF0069
    List<CommonButton> armyManageButtons;
    //##ModelId=522B36690224
    TextView nameTextView;
    //##ModelId=522B3E6203A0
    List<CommonButton> cityOperationButtons;
    //##ModelId=522B3F2900BC
    List<TextView> cityPropertyTextViews;
    //##ModelId=522B3F540167
    PictureView backgroundView;
    //##ModelId=522B3F69025D
    PictureView cityIconView;
    //##ModelId=522B3F7903E2
    CommonButton dismissButton;
    /** retalive city id. */
    //##ModelId=5267170F0181
    Uint32 cityId;
};



#endif /* CITYVIEW_H_HEADER_INCLUDED_AD80A9BF */
