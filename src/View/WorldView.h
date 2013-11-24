#ifndef WORLDVIEW_H_HEADER_INCLUDED_AD80BB78
#define WORLDVIEW_H_HEADER_INCLUDED_AD80BB78
#include "CommonButton.h"
#include "PictureView.h"
#include "RichTextView.h"

/** @brief a singleton object for the whole world including all sub maps, can
be accessed by any sub views through get singleton instance method. */
//##ModelId=522C7DEC0237
class WorldView
{
  public:
    /** @brief get self country cities, prepare all view frames in self city
    list view. Init all subviews in list view use model data from country city
    list. */
    //##ModelId=5265298A0236
    PrepareSelfCityList();

    /** @brief initial all subviews in list view of army list showing. Getting
    self country army list as data model. */
    //##ModelId=5265C25902AF
    PrepareSelfArmyList();

    /** @brief sort list by specific column.
    @return order list of city list view */
    //##ModelId=5265C5860284
    SortCityList();

    /** @brief sort list by specific column.
    @return order list of army list view */
    //##ModelId=5265C5AD0395
    SortArmyList();

    /** @brief focus screen center on specific world point, used in <Locating
    ... > user cases, <Scroll Map> following OnTabMove method.
    @param[in]  */
    //##ModelId=52668B2E0103
    void FocusAtPoint(Point center);

    /** @brief initial city view & display it, this is for <Enter City> user
    case. */
    //##ModelId=526712C30376
    PrepareCityView();

    /** @brief initial & display city popup view, this is for <Select City>
    user case */
    //##ModelId=526D24BC0380
    PrepareCityPopup();

    /** @brief initial & display army popup view, this is for <Show City
    Armies> user case. */
    //##ModelId=526D24D800E4
    PrepareArmyPopup();

    /** @brief workable only when army ready list has armies & tap on enemy
    object (city/army),after getting confirm from warning view, run <Attack Object>
    user case  */
    //##ModelId=526D2A25002C
    EngageAttackObject();

    /** @brief workable only when army ready list has armies & tap on enemy
    object (city/army),after getting confirm from warning view, run <Move Army>
    user case  */
    //##ModelId=526D2A2D03D0
    EngageMoveArmy();

    /** @brief get confirm from user about planned army action
    @param[in] id the warning view ID specified for dedicate warning view,
    including <Attack Object>yes/no, <Move Army>yes/no, <Retreat Army>
    yes/no/can't, <Army leader abort mission or not>yes(notification).  */
    //##ModelId=526D2B550203
    ShowArmyActionWarning(Uint32 id);

    /** @brief get the singleton object of this world view */
    //##ModelId=526D314D009E
    WorldView* GetInstance();

  private:
    //##ModelId=522C7E80033F
    PictureView bigBackGround;
    //##ModelId=522C7E9300F3
    CommonButton cityIcons[];
    //##ModelId=522C7EBA02AF
    RichTextView playTitleView;
    //##ModelId=522C7ECE026B
    CommonButton pushTimeButton;
    //##ModelId=522C7F0B0095
    CommonButton goldMapButton;
    //##ModelId=522C7F1A0385
    CommonButton locateObjectButton;
    //##ModelId=522C80F6020F
    List<Uint32> cityIdList;
    //##ModelId=52652E45022E
    Uint32 selfCountryId;
    /** The point that  matchs the view center, it changed as user focus target
    changed (army/city). and changed as user tap move on World View. */
    //##ModelId=52668973029C
    Point centralPoint;
};



#endif /* WORLDVIEW_H_HEADER_INCLUDED_AD80BB78 */
