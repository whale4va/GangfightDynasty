#ifndef UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A
#define UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A

#include "../Model/EventQueue.h"
#include "CommonButton.h"
#include "TabView.h"
#include "RichTextView.h"
#include "ListView.h"
#include "../Common/ResourceUri.h"


//##ModelId=522C3A4900B0
class UpgradeViewTab : public TabView
{
  public:
   
    virtual bool OnButton();
    virtual bool OnListItemSelected(int rowIndex);
    virtual bool OnListItemUnselected(int rowIndex);
    
    // fill in executors list view sub views
    void FillInListViews();
    
    inline virtual void Display()
    {
        okButton.Display();
        executorsList.Display();
        resultView.Display();
        executorText.Display();
    }
    
    inline virtual void Dismiss()
    {
        okButton.Dismiss();
        executorsList.Dismiss();
        resultView.Dismiss();
        executorText.Dismiss();
    }
    
    inline virtual void Destory()
    {
        Dismiss();
        okButton.Destory();
        executorsList.Destory();
        resultView.Destory();
        executorText.Destory();
    }

    UpgradeViewTab(CCNode* node, UpgradeType t, Uint32 Id, Uint8 rowH) :
        TabView(node), type(t), executors(true),
        okButton(node, ResourceUri::okButtonPictureName),
        executorText(node, "执行将领"), expense(0), expectedResult(0),
        resultView(node), usedLeaders(true), targetId(Id),
        executorsList(node, "升级将领列表", 4, false, false, rowH, 0)
    {
        
        okButton.SetParentView(this);
        okButton.SetId(BTN_OK);
        executorText.SetParentView(this);
        executorsList.SetParentView(this);
        resultView.SetParentView(this);
        
        String upgradeTitle;
        String upgradeResultFormat;
        
        switch (type)
        {
            case Upgrade_Agriculture:
                upgradeTitle = "升级农业";
                upgradeResultFormat = "预期效果：农业 {T} 金钱 {T}";
                break;
            case Upgrade_Business:
                upgradeTitle = "升级商业";
                upgradeResultFormat = "预期效果：商业 {T} 金钱 {T}";
                break;
            case Upgrade_Security:
                upgradeTitle = "整顿治安";
                upgradeResultFormat = "预期效果：治安 {T} 金钱 {T}";
                break;
            case Upgrade_Soldier:
                upgradeTitle = "招募士兵";
                upgradeResultFormat = "预期效果：士兵 {T} 金钱 {T}";
                break;
            case Upgrade_Arrow:
                upgradeTitle = "生产弓箭";
                upgradeResultFormat = "预期效果：弓箭 {T} 金钱 {T}";
                break;
            case Upgrade_Sword:
                upgradeTitle = "生产刀剑";
                upgradeResultFormat = "预期效果：刀剑 {T} 金钱 {T}";
                break;
            case Upgrade_Spear:
                upgradeTitle = "生产长枪";
                upgradeResultFormat = "预期效果：长枪 {T} 金钱 {T}";
                break;
            case Upgrade_Horse:
                upgradeTitle = "饲养马匹";
                upgradeResultFormat = "预期效果：马匹 {T} 金钱 {T}";
                break;
            case Upgrade_City:
                upgradeTitle = "扩建城市";
                upgradeResultFormat = "预期效果：城市等级 {T} 金钱 {T}";
                break;
            default:
                THROW(Invalid_Upgrade_Type);
//                upgradeTitle = "升级农业";
//                upgradeResultFormat = "预期效果：农业{T} 金钱{T}";
//                break;
        }
        
        this->SetTitle(upgradeTitle);
        resultView.SetFormatContent(upgradeResultFormat);
        
        RichTextElement* pResult = new RichTextElement(
                        ResourceUri::bitmapFontFileName,
                        "+0", expectedResultColor);
        RichTextElement* pCost = new RichTextElement(
                         ResourceUri::bitmapFontFileName,
                         "-0", expenseColor);
        resultView.AddRichTextElement(pResult);
        resultView.AddRichTextElement(pCost);
    }
    
    void SetDimension(Dimension dim);

  private:
    //##ModelId=522C65B70046
    List<Leader*> executors;
    
    // 使用的将领列表
    List<Leader*> usedLeaders;
    
    //##ModelId=522C65DE000A
    //CommonButton addLeaderButton;
    
    // 执行将领 文本
    TextView executorText;
    
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
    
    Uint32 targetId;
    
    
    // relative dimension proportion of sub views in this view
    static float executorTextXp, executorTextYp, executorTextWp, executorTextHp;
    static float executorListXp, executorListYp, executorListWp, executorListHp;
    static float resultViewXp, resultViewYp, resultViewWp, resultViewHp;
    static float okButtonXp, okButtonYp, okButtonWp, okButtonHp;
    
    static Uint32 expectedResultColor, expenseColor;
    
    //##ModelId=52691B08002A
    Event* GenerateEvent();
};

class UpgradeView : public TabGroupView
{
    
public:
    UpgradeView(CCNode* node) : TabGroupView(node) {
        this->SetIsModal(true);
    }
    
    //##ModelId=522C6CF80198
    void ShowCandidateLeaderList();

    //##ModelId=522C6D0C01C2
    void RefreshResultView();

    //##ModelId=526919130240
    void InitWithUpgradeType(UpgradeType type);

    
    
    virtual bool OnButton();
    
    
};



#endif /* UPGRADEVIEW_H_HEADER_INCLUDED_AD80A41A */
