#ifndef LISTVIEW_H_HEADER_INCLUDED_AD808747
#define LISTVIEW_H_HEADER_INCLUDED_AD808747
#include "CommonButton.h"
#include "TabView.h"
class ViewFrame;

//##ModelId=522B32CA02D2
class ListView : public TabView
{
  public:
    //##ModelId=522B4CAE0320
    RetrieveSelectedItem();

    /** Redraw list with specific index, used in sorting case. List actual
    model data is managed/owned by father view/object.
    @param[in] order index array for each element in content veiws array and
    indicate each element/row index. */
    //##ModelId=526529FC0399
    void RedrawWithOrder(List<Uint32> order);

    /** @brief set list view items order */
    //##ModelId=5265391B0223
    void SetSortOrder(List<Uint32> order);

    /** @brief get selecte item index of the list view
    @return list of indexes of select items. */
    //##ModelId=5269C704039B
    List<Uint32> GetSelectItem();

    //##ModelId=526D103003E6
    void ShowSpecialButton();

  private:
    //##ModelId=522B4B6300A7
    Uint32 columnNumber;
    //##ModelId=522B4BC902BC
    Uint32 selectedItem[];
    //##ModelId=522B4BDE034A
    bool multiSelectable;
    //##ModelId=522B4BEC022F
    Uint32 selectedItemNumber;
    //##ModelId=522B4BF9014E
    CommonButton okButton;
    //##ModelId=522B4C6302DF
    CommonButton specialButtons[];
    //##ModelId=522B4C8100F3
    bool triggleSpecialButton;
    //##ModelId=522B4C98031D
    Uint32 specialButtonNumber;
    //##ModelId=522C617001A1
    ViewFrame* contentViews[][];
    /** order of items in content views. */
    //##ModelId=526531910060
    List<Uint32> sortOrder;
};



#endif /* LISTVIEW_H_HEADER_INCLUDED_AD808747 */
