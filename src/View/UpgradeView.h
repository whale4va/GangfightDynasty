#ifndef UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A
#define UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A

#include "../Model/Event.h"
#include "CommonButton.h"
#include "TabView.h"
#include "RichTextView.h"
#include "ListView.h"


//##ModelId=522C3A4900B0
class UpgradeView : public TabView
{
  public:
    //##ModelId=522C6CF80198
    void ShowCandidateLeaderList();

    //##ModelId=522C6D0C01C2
    void RefreshResultView();

    //##ModelId=526919130240
    void InitWithUpgradeType(UpgradeType type);

    //##ModelId=52691B08002A
    Event* GenerateEvent();
    
    
    virtual bool OnButton();
    
    virtual void Display();
    virtual void Dismiss();
    virtual void Destory();

  private:
    //##ModelId=522C65B70046
    List<Leader*> executors;
    //##ModelId=522C65DE000A
    CommonButton addLeaderButton;
    //##ModelId=522C65EF0016
    Uint32 expectedResult;
    //##ModelId=522C6C270177
    CommonButton okButton;
    //##ModelId=522C6C850276
    Uint32 expense;
    //##ModelId=522C6C97025B
    ListViewTab executorsList;
    //##ModelId=522C6CCC017F
    RichTextView resultView;
    //##ModelId=522C6CD90144
//    CommonButton addGoldButton;
    /** indicate which type data need to be upgraded. */
    //##ModelId=5267D90302F4
    UpgradeType type;
};



#endif /* UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A */
