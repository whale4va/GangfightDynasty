#ifndef WARFAREVIEW_H_HEADER_INCLUDED_AD80EBB3
#define WARFAREVIEW_H_HEADER_INCLUDED_AD80EBB3
#include "PictureView.h"

//##ModelId=522C6EC70231
class WarfareView
{
  public:
    /** @brief set user tapped army in warfare view into selected army list,
    can be consider as <Retreat Army> or <Adjust Army> subject.
    @param[in] pArmy the pointer of selected army. */
    //##ModelId=526D34480026
    void SetSelectedArmy(Army* pArmy);

    /** @brief clear selected armies when needed as user tap on blank position */
    //##ModelId=526D35320171
    void ClearSelectedArmy();

    /** @brief show army can move to positions arrow to indicate user to tap &
    engage <Adjust Army> user case when needed */
    //##ModelId=526D353A034C
    void ShowCandidatePosition();

    /** @brief show retreat information warning view & get confirm from user,
    if yes, run <Retreat Army> user case, add army to executer manager and remove
    it from warfare */
    //##ModelId=526D35AF009F
    void EngageRetreatArmy(Army* pArmy);

    /** @brief run <Adjust Army> user case when user tap candidata attacking
    positions in warfare view, engage warfare class internal move army method
    properly.
    @param[in] pArmy pointer to army that will be adjusted
    @param[in[ pt position that the army will move to */
    //##ModelId=526D35C2039C
    void EngageAdjustArmy(Army* pArmy, Point pt);

    /** @brief display refresh method, update warfare view & animination as
    wanted. */
    //##ModelId=526D394D03D4
    void Refresh();

  private:
    //##ModelId=522C6F5102B0
    PictureView areaElementView;
    //##ModelId=522C6F750356
    PictureView attackArrowView;
    //##ModelId=522C6F9D03CA
    Warfare* warfare;
    //##ModelId=526D34940330
    Army* selectedArmy;
};



#endif /* WARFAREVIEW_H_HEADER_INCLUDED_AD80EBB3 */
