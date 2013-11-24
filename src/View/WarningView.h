#ifndef WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#define WARNINGVIEW_H_HEADER_INCLUDED_AD809A66
#include "CommonButton.h"
#include "TabView.h"

//##ModelId=522C730D006A
class WarningView : public TabView
{
  public:
    //##ModelId=522F2CF7036B
    InitWithString();

    //##ModelId=522F2E360215
    SetRichTextView();

    //##ModelId=524ED4D50189
    void SetIsOk(bool isOk);

    //##ModelId=524ED4F00340
    bool GetIsOk();

  private:
    //##ModelId=522C732A0082
    RichTextView warningText;
    //##ModelId=522C73370282
    CommonButton okButton;
    //##ModelId=524ED33F0361
    bool isOk;
};



#endif /* WARNINGVIEW_H_HEADER_INCLUDED_AD809A66 */
