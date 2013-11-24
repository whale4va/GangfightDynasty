#ifndef NUMBERSLIPVIEW_H_HEADER_INCLUDED_AD80DAEE
#define NUMBERSLIPVIEW_H_HEADER_INCLUDED_AD80DAEE
#include "CommonButton.h"
#include "PictureView.h"
#include "TabView.h"
#include "TextView.h"

//##ModelId=522C735D0233
class NumberSlipView : public TabView
{
  public:
    //##ModelId=524055760212
    void InitWithValues(Uint32 min, Uint32 max, Uint32 decide);

    //##ModelId=524058B30363
    Uint32 GetDecideValue();

    //##ModelId=5240BCAC00A7
    void ResetValues(Uint32 min, Uint32 max, Uint32 decide);

    /** @brief set buttons used to control the default value. */
    //##ModelId=526CC3780025
    void SetDefaultValueButtons(List<CommonButton*> buttons);

  private:
    //##ModelId=522C73DB00F5
    CommonButton okButton;
    //##ModelId=522C73F60000
    Uint32 minValue;
    //##ModelId=522C73FF03A2
    Uint32 maxValue;
    //##ModelId=522C741602B7
    Uint8 percentage;
    //##ModelId=522C743603C1
    Uint32 decideValue;
    //##ModelId=526D0BE800CC
    Uint32 defaultValue;
    //##ModelId=522C74440279
    TextView valueLabel;
    //##ModelId=522C745101E5
    CommonButton upperButton;
    //##ModelId=522C745E02A5
    CommonButton lowerButton;
    //##ModelId=522C747402D0
    Uint32 stepValue;
    //##ModelId=522C74AA0330
    CommonButton changeDefaultValueButtons[];
    //##ModelId=522C74D30029
    Uint32 barColor;
    //##ModelId=526D0CE00059
    Uint32 exceedBarColor;
    //##ModelId=522C74E6003E
    CommonButton slipButton;
    //##ModelId=522C74F60356
    PictureView slipBar;
};



#endif /* NUMBERSLIPVIEW_H_HEADER_INCLUDED_AD80DAEE */
