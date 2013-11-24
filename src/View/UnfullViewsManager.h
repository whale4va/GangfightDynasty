#ifndef UNFULLVIEWSMANAGER_H_HEADER_INCLUDED_AD80C516
#define UNFULLVIEWSMANAGER_H_HEADER_INCLUDED_AD80C516
class ViewFrame;

/** It's a selegon object for every Scense. Maintain any pointer/reference to
un-full views in the screen. It's used in dismissing view operation. Any tap
responding will query whether upmost views will be dismissed because of not be
tapped. */
//##ModelId=5246E6C300DC
class UnfullViewsManager
{
  public:
    /** @param view - any new view need to be showed.
    Judge this view is full or not. If not, add it to list. Un-full view means the
    view that can be dismissed by tapping on area that is not belong to the view.
    Every new created view frame must be passed to this method.This method is
    invoked by ViewFrame::SetFull(true); */
    //##ModelId=5246EC9D01CB
    void AddView(ViewFrame* view);

    //##ModelId=5246ECCD0251
    void SortViewsByZ();

    /** @param view - the view that was tapped.
    @return - the view that need to be dismissed. */
    //##ModelId=5246ED3B01BF
    ViewFrame* GetDismissView(ViewFrame* view);

  private:
    /** Can be used to sort views by Z (depth) corrdination. */
    //##ModelId=5246EB5D037B
    List<ViewFrame*> unfullViewList;
};



#endif /* UNFULLVIEWSMANAGER_H_HEADER_INCLUDED_AD80C516 */
