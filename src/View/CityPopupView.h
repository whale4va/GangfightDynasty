#ifndef CITYPOPUPVIEW_H_HEADER_INCLUDED_AD80C380
#define CITYPOPUPVIEW_H_HEADER_INCLUDED_AD80C380
#include "TabView.h"
#include "RichTextView.h"
#include "TabGroupView.h"
#include "ListView.h"
#include "ArmyReadyView.h"
#include "../Model/Leader.h"
#include "../Model/City.h"
#include "../Common/SceneScheduler.h"

//##ModelId=522B40B9029E
class CityPopupViewTab : public TabView
{
public:
    CityPopupViewTab(CCNode* node, String title, City* pC) :
            TabView(node, title),
            officerStrategyView(node, "太守 {T}    策略 {T}"),
            agricultureView(node, "农业 {T}"),
            businessView(node, "商业 {T}"),
            securityView(node, "治安 {T}"),
            soldierSwordView(node, "士兵 {T}    刀剑 {T}"),
            spearHorseView(node, "长枪 {T}    战马{T}"),
            pCity(pC)
    {
        Leader officer = Leader::GetLeaderById(pCity->get_officerId());
        RichTextElement* rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                                   officer.GetName(), fontColor);
        officerStrategyView.AddRichTextElement(rte);
        
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  ResourceUri::StrategyName[pCity->get_strategy()], fontColor);
        officerStrategyView.AddRichTextElement(rte);
        
        char buf[32] = {'\0'};
        
        // agriculture
        sprintf(buf, "%d/%d", pCity->get_agriculture(),
                pCity->get_level()*City::levelQuota);
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        agricultureView.AddRichTextElement(rte);
        
        // business
        memset(buf, 0x00, 32);
        sprintf(buf, "%d/%d", pCity->get_business(),
                pCity->get_level()*City::levelQuota);
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        businessView.AddRichTextElement(rte);
        
        // security
        memset(buf, 0x00, 32);
        sprintf(buf, "%d/%d", pCity->get_security(), 100);
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        securityView.AddRichTextElement(rte);
        
        // soldier & sword
        memset(buf, 0x00, 32);
        sprintf(buf, "%d", pCity->get_soldier());
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        soldierSwordView.AddRichTextElement(rte);
        memset(buf, 0x00, 32);
        sprintf(buf, "%d", pCity->get_sword());
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        soldierSwordView.AddRichTextElement(rte);
        
        // spear & horse
        memset(buf, 0x00, 32);
        sprintf(buf, "%d", pCity->get_spear());
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        spearHorseView.AddRichTextElement(rte);
        memset(buf, 0x00, 32);
        sprintf(buf, "%d", pCity->get_horse());
        rte = new RichTextElement(ResourceUri::bitmapFontFileName,
                                  buf, fontColor);
        spearHorseView.AddRichTextElement(rte);
        
    }
    
    virtual void Display();
    virtual void Dismiss();
    virtual void Destory();
    
private:
    
    RichTextView officerStrategyView;
    RichTextView agricultureView;
    RichTextView businessView;
    RichTextView securityView;
    RichTextView soldierSwordView;
    RichTextView spearHorseView;
    
    City* pCity;
    static Uint32 fontColor;                    //color of richtext element.
    static Uint8 dividerHeightProportion;       //percentage of divider height.
    static Uint8 rowHeightProportion;           //percentage of each row height.
};

class CityPopupView : public TabGroupView
{
private:
    City* pCity;
    static Uint8 armyListRowHeight;
    
public:
    CityPopupView(CCNode* node, City* pC) :
        TabGroupView(node, ResourceUri::enterCityButtonPictureName,
                     BTN_ENTER_CITY),
        pCity(pC)
    {
        SetIsModal(false);
    }
    
    void SetDimension(Dimension dim);       // 覆盖父类的方法，可以在此加入tabview
    
    virtual bool OnButton();                          // 重载方法，实现进入城市页面按钮操作
    virtual bool OnListItemSelected(int rowIndex);    // 重载方法，实现列表选项被选择
    virtual bool OnListItemUnselected(int rowIndex);  // 重载方法，实现列表选项的取消选择
};

#endif /* CITYPOPUPVIEW_H_HEADER_INCLUDED_AD80C380 */
